// !include ./intcode.cpp

long part1(std::string &inp) {
    return intcode(inp, {}, { { 1, 12 }, { 2, 2 } }, true)[0];
}

long part2(std::string &inp) {
    int a = 0;
    int b = 0;
    while (true) {
        if (intcode(inp, {}, { { 1, a }, { 2, b } }, true)[0] == 19690720) return 100 * a + b;
        if (a == 0) {
            int temp = b;
            b = 0;
            a = temp + 1;
        } else {
            a--;
            b++;
        }
    }
}