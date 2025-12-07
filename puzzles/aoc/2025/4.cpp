// !include ../../util.cpp

auto neighbors(int x, int y, int w, int h) {
    std::vector<std::pair<int, int>> r;
    for (int dy = -!!y; dy < 2 && y + dy < h; dy++)
        for (int dx = -!!x; dx < 2 && x + dx < w; dx++)
            r.push_back({ x + dx, y + dy });
    return r;
}

int **load_counts(std::string &inp, int *w, int *h) {
    auto lines = split_string(inp, '\n');
    int **counts = new int*[*h = lines.size()];
    for (int i = 0; i < *h; i++)
        counts[i] = new int[*w = lines[i].size()]();
    for (int y = 0; y < *h; y++)
        for (int x = 0; x < *w; x++)
            if (lines[y][x] == '@')
                for (auto &[nx, ny] : neighbors(x, y, *w, *h))
                    if (lines[ny][nx] == '@')
                        counts[ny][nx]++;
    return counts;
}

int part1(std::string &inp) {
    int w, h;
    auto counts = load_counts(inp, &w, &h);
    int r = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++)
            if (counts[y][x] && counts[y][x] < 5) r++;
        delete[] counts[y];
    }
    delete[] counts;
    return r;
}

int part2(std::string &inp) {
    int w, h;
    auto counts = load_counts(inp, &w, &h);
    int sum = 0;
    int rm;
    do {
        rm = 0;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++)
                if (counts[y][x] && counts[y][x] < 5) {
                    rm++;
                    counts[y][x] = 0;
                    for (auto &[nx, ny] : neighbors(x, y, w, h))
                        if (counts[ny][nx])
                            counts[ny][nx]--;
                }
        }
        sum += rm;
    } while (rm);
    for (int y = 0; y < h; y++) delete[] counts[y];
    delete[] counts;
    return sum;
}