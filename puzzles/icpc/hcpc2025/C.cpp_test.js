const TESTS = 15;
const MAX = 10n ** 18n - 1n;

for (const n of [0n, MAX, ...Array.from(
    { length: TESTS },
    () => BigInt(Math.floor(Math.random() * (Number(MAX) + 1))),
)])
    await runTest(async (read, write) => {
        for (let i = 0; i < 75; i++) {
            const [op, x] = (await read()).split(' ');
            if (op === 'answer') return console.log(`${
                BigInt(x) === n ? '[correct] ' : `[incorrect] output: ${x}, `
            }answer: ${n}, tries: ${i}`);
            write((n + BigInt(x) + '').split('').reduce((a, b) => a + (+b), 0) + '\n');
        }
        console.log('too many queries');
    }, true);