import { existsSync, mkdirSync, readFileSync, writeFileSync } from 'fs';
import { exec } from 'child_process';
import { resolve } from 'path';
import { config } from 'dotenv';

config({ quiet: true });

const INCLUDE = /^(\/\/|--|#)\s*!include\s+/;
const INTERACTIVE = '_test.js';

const substitute = (s, o) => Object.entries(o).reduce((a, e) => a.replaceAll('${' + e[0] + '}', e[1]), s);

const resolveIncludes = path => readFileSync(path, 'utf8')
    .split(/\r?\n/)
    .map(x => INCLUDE.test(x) ? resolveIncludes(resolve(path, '..', x.replace(INCLUDE, ''))) : x)
    .join('\n');

const run = (x, noPipe, cb) => new Promise((res, rej) => {
    const start = Date.now();
    const proc = exec(x, { maxBuffer: Infinity });
    proc.stderr.pipe(process.stderr);
    if (!noPipe) proc.stdout.pipe(process.stdout);
    let result = '';
    proc.stdout.on('data', d => result += d);
    proc.on('close', code => code ? rej('') : res([result, Date.now() - start]));
    cb?.(proc).then(() => proc.exitCode === null && proc.kill());
});

(async () => {
    ['temp', 'inputs'].forEach(x => existsSync(x) || mkdirSync(x));

    const flags = {};
    let src;
    let interactive;
    let dir;
    const inputs = [];
    const resolveInput = p => {
        const path = resolve('inputs', src, '..', p);
        if (!existsSync(path)) {
            console.error('Unable to resolve input', p);
            process.exit();
        }
        inputs.push(path);
    };
    for (const arg of process.argv.slice(2)) {
        const m = arg.match(/^--?(.+?)(?:=(.+?))?$/);
        if (m) flags[m[1]] = m[2] || true;
        else {
            if (src) resolveInput(await dir?.getInput?.(src, arg) || arg);
            else {
                interactive = arg.endsWith(INTERACTIVE);
                src = interactive ? arg.slice(0, -INTERACTIVE.length) : arg;
                if (!existsSync('puzzles/' + src)) return console.error('Source file not found.');
                if (interactive && !existsSync('puzzles/' + arg)) return console.error('Testing file not found.');
                try {
                    dir = (await import('./dirs/' + src.split(/[\/\\]/)[0] + '.js')).default;
                    if (interactive && !dir.stdin) return console.error('Target file does not read from stdin.');
                } catch {}
            }
        }
    }
    const ext = src.split('.').at(-1);
    let [type, cmd, ...content] = readFileSync(`src/languages/${ext}.txt`, 'utf8').split(/\r?\n/);
    cmd = substitute(cmd, {
        o: 'temp/o.exe',
        src: 'temp/main.' + ext,
    });
    const toRun = type === 'comp'
        ? content[0]
            ? content.shift()
            : '.\\temp\\o.exe'
        : cmd;

    let resolved = resolveIncludes('puzzles/' + src);
    if (dir?.handleContent) resolved = dir.handleContent(resolved, ext);
    writeFileSync('temp/main.' + ext, dir?.stdin ? resolved : substitute(content.join('\n'), {
        main: dir?.mainName?.(flags) || 'result',
        content: resolved,
    }));
    if (type === 'comp') console.error('Compiled in', (await run(cmd))[1], '\bms');
    if (interactive) {
        const runTest = cb => run(toRun, flags.quiet, proc => cb(
            () => new Promise(r => proc.stdout.once('data', d => r(d.trim()))),
            d => {
                if (!flags.quiet) process.stdout.write(d);
                proc.stdin.write(d);
            },
        ));
        eval(`${runTest};(async()=>{${readFileSync('puzzles/' + src + INTERACTIVE, 'utf8')}})();`);
        return;
    }
    if (!inputs.length) {
        if (dir?.handleEmpty) (await dir.handleEmpty(src)).forEach(resolveInput);
        else if (dir?.stdin) return console.error('Input files expected.');
        else inputs.push('package.json'); // arbitrary file
    }
    let result;
    for (const i of inputs) {
        const r = await run(toRun + (dir?.stdin ? ' < ' + i : ' "' + i + '"'), flags.quiet);
        result = r[0].trim();
        if (!flags.quiet && !r[0].endsWith('\n')) console.log();
        if (flags.test) {
            const ansPath = i.replace(/\..+$/, '.ans');
            const truncated = i.slice((process.cwd() + '/inputs/').length);
            if (existsSync(ansPath)) {
                const ans = readFileSync(ansPath, 'utf8').replaceAll('\r', '').trim();
                console.log(`[${truncated}] ${result === ans
                    ? 'Success'
                    : flags.quiet
                        ? 'Wrong output'
                        : 'Expected output:\n' + ans}`);
            } else console.error(`[${truncated}] Output path not found`);
        }
        console.log('Executed in', r[1], '\bms');
    }
    dir?.handleResult?.(flags, src, result.trim());
})().catch(console.error);

const kill = () => process.platform === 'win32'
    ? exec(`taskkill /PID ${process.pid} /T /F`)
    : process.kill(process.pid);
process.on('SIGINT', kill);
process.on('SIGTERM', kill);