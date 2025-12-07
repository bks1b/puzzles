// !include ./intcode.cpp

long solve(std::string &inp, bool p2) {
    return intcode(inp, { p2 + 1 })[0];
}