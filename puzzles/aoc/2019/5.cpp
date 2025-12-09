// !include ./Intcode.cpp

int solve(std::string &inp, bool p2) {
    Intcode c(inp, { 1 + 4 * p2 });
    return c.step().back();
}