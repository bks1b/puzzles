// !include ./Intcode.cpp
// !include ../chars.cpp

auto get_panels(std::string &inp, bool fst) {
    std::pair<int, int> pos = { 0, 0 };
    std::pair<int, int> dir = { 0, -1 };
    std::map<std::pair<int, int>, bool> panels;
    panels[pos] = fst;
    Intcode comp(inp, {});
    while (true) {
        comp.input.push_back(panels.contains(pos) && panels[pos]);
        auto out = comp.step(2);
        if (out.size() < 2) return panels;
        panels[pos] = out[0];
        int s = 2 * out[1] - 1;
        dir = { -s * dir.second, s * dir.first };
        pos = { pos.first + dir.first, pos.second + dir.second };
    }
}

int part1(std::string &inp) {
    return get_panels(inp, false).size();
}

std::string part2(std::string &inp) {
    auto panels = get_panels(inp, true);
    int min_x = __INT_MAX__;
    int min_y = __INT_MAX__;
    for (auto &[p, b] : panels)
        if (b) {
            min_x = std::min(min_x, p.first);
            min_y = std::min(min_y, p.second);
        }
    return get_str(8, [&panels, min_x, min_y](int x, int y) {
        return panels[{ x + min_x, y + min_y }];
    });
}