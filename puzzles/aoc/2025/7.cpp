// !include ../../util.cpp

ll solve(std::string &inp, bool p2) {
    auto lines = split_string(inp, '\n');
    ll *beams = new ll[lines[0].size()]();
    ll result = 0;
    for (auto &line : lines) {
        if (p2) result = 0;
        ll add_next = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == 'S') beams[i]++;
            else if (line[i] == '^') {
                if (!p2) result += !!beams[i];
                if (i) beams[i - 1] += beams[i];
                std::swap(add_next, beams[i]);
            } else {
                beams[i] += add_next;
                add_next = 0;
            }
            if (p2) result += beams[i];
        }
    }
    delete[] beams;
    return result;
}