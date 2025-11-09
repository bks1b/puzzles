!include ../../util.cpp

int f(std::string &inp, bool diag) {
    std::unordered_map<std::string, int> points;
    int res = 0;
    for (auto line : split_string(inp, '\n')) {
        auto coords = match_ints(line);
        if (!diag && coords[0] != coords[2] && coords[1] != coords[3]) continue;
        while (true) {
            if (points[std::to_string(coords[0]) + "_" + std::to_string(coords[1])]++ == 1) res++;
            if (coords[0] == coords[2] && coords[1] == coords[3]) break;
            coords[0] += sgn(coords[2] - coords[0]);
            coords[1] += sgn(coords[3] - coords[1]);
        }
    }
    return res;
}

int part1(std::string &inp) {
    return f(inp, false);
}

int part2(std::string &inp) {
    return f(inp, true);
}