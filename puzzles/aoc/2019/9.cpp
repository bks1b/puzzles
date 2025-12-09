// !include ./Intcode.cpp

ll solve(std::string &inp, bool p2) {
    Intcode c(inp, { p2 + 1 });
    return c.step()[0];
}