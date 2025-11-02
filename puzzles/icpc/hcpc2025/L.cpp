#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

const char *COLORS = "RGB";

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<long, long>> flowers[3];
    while (n--) {
        long x, y;
        char c;
        std::cin >> x >> y >> c;
        flowers[std::find(COLORS, COLORS + 3, c) - COLORS].push_back({ x, y });
    }
    double min_total = 0;
    for (int i = 0; i < 3; i++) for (auto &b : flowers[i]) {
        double sum = 0;
        for (int j = 0; j < 3; j++) if (j != i) {
            double min_local = 0;
            for (auto &x : flowers[j]) {
                auto dist = std::hypot(x.first, x.second) + std::hypot(b.first - x.first, b.second - x.second);
                if (!min_local || dist < min_local) min_local = dist;
            }
            sum += min_local;
        }
        if (!min_total || sum < min_total) min_total = sum;
    }
    std::cout << std::fixed << std::setprecision(5) << min_total << "\n";
    return 0;
}

/*
The goal is to minimize @|a|+|b-a|+|b-c|+|c|@ for all triples of coordinates @a,b,c@ with different colors.
For each possible @b@, we can choose the optimal @a@ and @c@ values in linear time.
*/