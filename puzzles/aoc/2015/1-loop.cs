int f(string inp, bool p2) {
    int n = 0;
    for (int i = 0; i < inp.Length; i++) {
        if (inp[i] == '(') n++;
        else n--;
        if (p2 && n == -1) return i + 1;
    }
    return n;
}

int part1(string inp) {
    return f(inp, false);
}

int part2(string inp) {
    return f(inp, true);
}