import { existsSync, writeFileSync, mkdirSync } from 'fs';
import { createInterface } from 'readline/promises';

const splitPath = src => {
    const r = src.split(/[\/\\]/).slice(1).map(x => parseInt(x.match(/^(\d+)/)?.[0]));
    if (!r[0] || !r[1]) throw 'Invalid AOC path.';
    return r;
};
const getPart = f => f.p || 1;

const request = (src, path, data) => fetch(`https://adventofcode.com/${splitPath(src).join('/day/')}${path}`, {
    ...data || {},
    headers: { ...data?.headers || {}, cookie: 'session=' + process.env.AOC_TOKEN },
}).then(d => d.text());

export default {
    mainName: f => 'part' + getPart(f),
    getInput: async (src, inp) => {
        const [, ex, inline] = inp.match(/^(\d+)(i?)$/) || [];
        if (!ex && inp !== 'inp') return;
        const [year, day] = splitPath(src);
        const filename = `${year}_${day}_${inp}.txt`;
        const path = 'inputs/aoc/' + filename;
        if (!existsSync('inputs/aoc')) mkdirSync('inputs/aoc');
        if (!existsSync(path)) {
            const txt = ex
                ? [...(await request(src, '')).matchAll(new RegExp((inline ? '' : '<pre>') + '<code>([\\s\\S]+?)</code>', 'g'))]
                    .at(+ex - 1)?.[1]
                    .replace(/<.+?>/g, '')
                    .replace(/&lt;/g, '<')
                    .replace(/&gt;/g, '>')
                : await request(src, '/input');
            if (!txt) return;
            writeFileSync(path, txt.trim());
        }
        return '../' + filename;
    },
    handleResult: async (f, src, out) => {
        if (!f.sub) return;
        const rl = createInterface(process.stdin, process.stdout);
        if (await rl.question(`\nAre you sure you want to submit ${out} to part ${getPart(f)}? [y/n] `) === 'y') {
            const res = (await request(src, '/answer', {
                headers: { 'content-type': 'application/x-www-form-urlencoded' },
                body: `level=${getPart(f)}&answer=${out}`,
                method: 'POST',
            })).match(/<article><p>([\s\S]+?)<\/p><\/article>/)?.[1];
            console.log(res.split('  ')[0].trim() + (res.match(/ You have .+?s left to wait./)?.[0] || ''));
        }
        rl.close();
    },
};