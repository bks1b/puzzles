import { existsSync, mkdirSync, readFileSync, writeFileSync } from 'fs';
import { exec } from 'child_process';
import { resolve } from 'path';
import { config } from 'dotenv';

config({ quiet: true });

const INCLUDE = '!include ';
const INTERACTIVE = '_test.js';

const doubleEscape = x => x.replaceAll('\\', '\\\\');
const evalWith = (str, obj) => eval(`${Object.entries(obj).map(e => `const ${e[0]}=${JSON.stringify(e[1])};`).join('')};\`${doubleEscape(str)}\`;`);

const resolveIncludes = path => readFileSync(path, 'utf8')
    .split(/\r?\n/)
    .map(x => x.startsWith(INCLUDE) ? resolveIncludes(resolve(path, '..', x.slice(INCLUDE.length).trim())) : x)
    .join('\n');

const run = (x, obj = {}) => new Promise(async (res, rej) => {
    const start = Date.now();
    const proc = exec(x);
    proc.stderr.pipe(process.stderr);
    if (!obj.noPipe) proc.stdout.pipe(process.stdout);
    if (obj.stdin) proc.stdin.end(obj.stdin + (obj.stdin.endsWith('\n') ? '' : '\n'));
    let last = '';
    proc.stdout.on('data', d => last = d.trim() || last);
    proc.on('close', code => code ? rej('') : res([last, Date.now() - start]));
    if (obj.cb) {
        await obj.cb(proc);
        if (proc.exitCode === null) proc.kill();
    }
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
    if (!inputs.length) {
        if (dir?.handleEmpty) resolveInput(await dir.handleEmpty(src));
        else inputs.push('package.json'); // arbitrary file
    }
    const ext = src.split('.').at(-1);
    const [type, cmd, ...content] = readFileSync(`src/languages/${ext}.txt`, 'utf8').split(/\r?\n/);

    const resolved = resolveIncludes('puzzles/' + src);
    writeFileSync('temp/main.' + ext, dir?.stdin ? resolved : evalWith(content.join('\n'), {
        inputs: inputs.map(doubleEscape),
        main: dir?.mainName?.(flags) || 'result',
        content: resolved,
    }));
    let toRun;
    if (type === 'comp') {
        console.error('\nCompiled in', (await run(evalWith(cmd, {
            temp: 'temp',
            o: 'temp/o.exe',
            src: 'temp/main.' + ext,
        })))[1], '\bms');
        toRun = '.\\temp\\o.exe';
    } else toRun = evalWith(cmd, {
        temp: 'temp',
        o: 'temp/o.exe',
        src: 'temp/main.' + ext,
    });
    let result;
    let time = 0;
    if (dir?.stdin)
        if (interactive) {
            const runTest = (cb, noPipe) => run(toRun, {
                noPipe,
                cb: proc => cb(
                    () => new Promise(r => proc.stdout.once('data', d => r(d.trim()))),
                    d => {
                        if (!noPipe) process.stdout.write(d);
                        proc.stdin.write(d);
                    },
                ),
            }).then(r => time += r[1]);
            console.log();
            await eval(`${runTest};(async()=>{${readFileSync('puzzles/' + src + INTERACTIVE, 'utf8')}})();`);
        } else for (const i of inputs) {
            console.log();
            const r = await run(toRun, { stdin: readFileSync(i, 'utf8') });
            result = r[0];
            time += r[1];
        }
    else [result, time] = await run(toRun);
    console.log('\nExecuted in', time, '\bms');
    if (!interactive) dir?.handleResult?.(flags, src, result);
})().catch(console.error);

const kill = () => process.platform === 'win32'
    ? exec(`taskkill /PID ${process.pid} /T /F`)
    : process.kill(process.pid);
process.on('SIGINT', kill);
process.on('SIGTERM', kill);