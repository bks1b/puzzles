import { existsSync, mkdirSync, readFileSync, rmSync, writeFileSync } from 'fs';
import { exec } from 'child_process';
import { resolve } from 'path';
import { config } from 'dotenv';

config({ quiet: true });

const INCLUDE = '!include ';

const doubleEscape = x => x.replaceAll('\\', '\\\\');
const evalWith = (str, obj) => eval(`${Object.entries(obj).map(e => `const ${e[0]}=${JSON.stringify(e[1])};`).join('')};\`${doubleEscape(str)}\`;`);

const resolveIncludes = path => readFileSync(path, 'utf8')
    .split(/\r?\n/)
    .map(x => x.startsWith(INCLUDE) ? resolveIncludes(resolve(path, '..', x.slice(INCLUDE.length).trim())) : x)
    .join('\n');

const run = x => new Promise((res, rej) => {
    const start = Date.now();
    const proc = exec(x);
    proc.stdout.pipe(process.stdout);
    proc.stderr.pipe(process.stderr);
    let last = '';
    proc.stdout.on('data', d => last = d.trim() || last);
    proc.on('close', code => code ? rej('') : res([last, Date.now() - start]));
});

(async () => {
    ['temp', 'inputs'].forEach(x => existsSync(x) || mkdirSync(x));

    const flags = {};
    let src;
    let dir;
    const inputs = [];
    const resolveInput = p => {
        const path = resolve('inputs', src, '..', p);
        if (!existsSync(path)) {
            console.log('Unable to resolve input', p);
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
                src = arg;
                if (!existsSync('puzzles/' + src)) return console.log('Source file not found.');
                try {
                    dir = (await import('./dirs/' + src.split(/[\/\\]/)[0] + '.js')).default;
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

    writeFileSync('temp/main.' + ext, evalWith(content.join('\n'), {
        inputs: inputs.map(doubleEscape),
        main: dir?.mainName?.(flags) || 'result',
        content: resolveIncludes('puzzles/' + src),
    }));
    let [result, time] = await run(evalWith(cmd, {
        temp: 'temp',
        o: 'temp/o.exe',
        src: 'temp/main.' + ext,
    }));
    if (type === 'comp') {
        console.log('\nCompiled in', time, '\bms');
        [result, time] = await run('.\\temp\\o.exe');
    }
    console.log('\nExecuted in', time, '\bms');
    rmSync('temp', { recursive: true });
    dir?.handleResult?.(flags, src, result);
})().catch(console.error);