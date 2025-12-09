// !include ./Intcode.cpp

int part1(std::string &inp) {
    int count = 0;
    int i = 0;
    Intcode c(inp, {});
    for (int r : c.step())
        count += !(++i % 3) && r == 2;
    return count;
}

int part2(std::string &inp) {
    int score = 0;
    int paddle;
    Intcode comp(inp, {}, { { 0, 2 } });
    while (true) {
        auto res = comp.step(3);
        if (res.size() < 3) return score;
        if (res[0] == -1 && !res[1]) score = res[2];
        else if (res[2] == 3) paddle = res[0];
        else if (res[2] == 4) comp.input.push_back(sgn(res[0] - paddle));
    }
}