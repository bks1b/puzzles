// !include ../../util.cpp

const int N = 1000;

struct Point { ll x, y, z; };

int find(int *groups, int i) {
    return i == groups[i]
        ? i
        : groups[i] = find(groups, groups[i]);
}

ll solve(std::string &inp, bool p2) {
    std::vector<Point> points;
    for (auto &line : split_string(inp, '\n')) {
        auto coords = split_string(line, ',');
        points.push_back({
            std::stoll(coords[0]),
            std::stoll(coords[1]),
            std::stoll(coords[2])
        });
    }
    int *groups = new int[points.size()];
    int *counts = p2 ? nullptr : new int[points.size()];
    for (int i = 0; i < points.size(); i++) {
        groups[i] = i;
        if (!p2) counts[i] = 1;
    }
    std::vector<std::tuple<double, int, int>> pairs;
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            pairs.push_back({
                std::hypot(
                    points[i].x - points[j].x,
                    points[i].y - points[j].y,
                    points[i].z - points[j].z
                ),
                i, j
            });
    std::sort(pairs.begin(), pairs.end());
    int remaining = points.size();
    for (int i = 0; p2 || i < N; i++) {
        auto [_, fst, snd] = pairs[i];
        int g1 = find(groups, fst);
        int g2 = find(groups, snd);
        if (g1 == g2) continue;
        groups[g1] = g2;
        if (!p2) {
            counts[g2] += counts[g1];
            counts[g1] = 0;
        } else if (--remaining == 1) {
            delete[] groups;
            return points[fst].x * points[snd].x;
        }
    }
    delete[] groups;
    int res = 1;
    std::sort(counts, counts + points.size(), std::greater<int>());
    for (int i = 0; i < 3; i++) res *= counts[i];
    delete[] counts;
    return res;
}