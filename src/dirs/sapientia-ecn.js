import { existsSync, mkdirSync, readdirSync, writeFileSync } from 'fs';
import StreamZIP from 'node-stream-zip';

const download = async s => {
    const name = 'InOut' + s.split('/')[1];
    const file = `inputs/${name}.zip`;
    const target = ['inputs', 'sapientia-ecn', ...s.split('.')[0].split('/').slice(1)];
    if (!existsSync(file)) writeFileSync(file, Buffer.from(
        await (await fetch(`https://ecn.ms.sapientia.ro/problems/${name}.zip`)).arrayBuffer(),
    ));
    target
        .map((_, i) => target.slice(0, i + 1).join('/'))
        .forEach(s => existsSync(s) || mkdirSync(s));
    const zip = new StreamZIP.async({ file });
    await zip.extract(name + '/' + target.at(-1), target.join('/'));
    await zip.close();
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