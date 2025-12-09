// !include ./Intcode.cpp

int part1(std::string &inp) {
    Intcode c(inp, {}, { { 1, 12 }, { 2, 2 } });
    c.step();
    return c.values[0];
}

int part2(std::string &inp) {
    int a = 0;
    int b = 0;
    while (true) {
        Intcode c(inp, {}, { { 1, a }, { 2, b } });
        c.step();
        if (c.values[0] == 19690720) return 100 * a + b;
        if (a--) b++;
        else {
            a = b + 1;
            b = 0;
        }
    }
}