const solve = (inp, p2) => [...inp].reduce((x, c, i) => !p2 || (x[0] + 1)
    ? [x[0] + 2 * (c === '(') - 1, i + 1]
    : x,
[0, 0])[+p2];