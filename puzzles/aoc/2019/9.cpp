!include ./intcode.cpp

long part1(std::string &inp) {
    return intcode(inp, { 1 })[0];
}

long part2(std::string &inp) {
    return intcode(inp, { 2 })[0];
}