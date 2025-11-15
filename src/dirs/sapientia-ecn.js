import { cpSync, existsSync, mkdirSync, readdirSync, rmSync, statSync, writeFileSync } from 'fs';
import StreamZIP from 'node-stream-zip';

const download = async s => {
    const name = 'InOut' + s.split('/')[1];
    const file = `inputs/${name}.zip`;
    const target = ['inputs', 'sapientia-ecn', ...s.split('.')[0].split('/').slice(1)];
    target[target.length - 1] = target.at(-1)[0];
    if (existsSync(target.join('/'))) return target;
    if (!existsSync(file)) writeFileSync(file, Buffer.from(
        await (await fetch(`https://ecn.ms.sapientia.ro/problems/${name}.zip`)).arrayBuffer(),
    ));
    target
        .map((_, i) => target.slice(0, i + 1).join('/'))
        .forEach(s => existsSync(s) || mkdirSync(s));
    const zip = new StreamZIP.async({ file });
    if (!await zip.extract(name + '/' + target.at(-1), target.join('/')))
        await zip.extract(target.at(-1), target.join('/'));
    await zip.close();
    for (const ent of readdirSync(target.join('/'))) {
        const src = [...target, ent].join('/');
        if (statSync(src).isDirectory()) {
            for (const t of readdirSync(src))
                cpSync(src + '/' + t, target.join('/') + '/' + ent.match(/\d+/)[0] + '.' + t.split('.').at(-1));
            rmSync(src, { recursive: true });
        }
    }
    return target;
};

export default {
    stdin: true,
    getInput: async (src, inp) => (await download(src)).at(-1) + '/' + inp + '.in',
    handleEmpty: async src => {
        const path = await download(src);
        return readdirSync(path.join('/'))
            .filter(s => s.endsWith('.in'))
            .map(s => path.at(-1) + '/' + s);
    },
};