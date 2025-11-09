// !include ./intcode.cpp

long part1(std::string &inp) {
    return intcode(inp, { 1 }).back();
}

long part2(std::string &inp) {
    return intcode(inp, { 5 })[0];
}