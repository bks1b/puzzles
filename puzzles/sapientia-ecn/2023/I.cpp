#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

typedef std::pair<int, int> point_t;

double dist(point_t &a, point_t &b) {
    return std::hypot(a.first - b.first, a.second - b.second);
}

double min_from(int i, int j, point_t *points, double **memo) {
    return memo[i][j]
        ? memo[i][j]
        : memo[i][j] = std::min(
            min_from(i + 1, i, points, memo) + dist(points[i + 1], points[j]),
            min_from(i + 1, j, points, memo) + dist(points[i + 1], points[i])
        );
}

int main() {
    int n;
    std::cin >> n;
    auto points = new point_t[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        points[i] = { x, y };
    }
    std::sort(points, points + n);
    double **memo = new double*[n];
    for (int i = 0; i < n - 1; i++) {
        memo[n - 2 - i] = new double[n - 2 - i]();
        if (i < n - 2) memo[n - 2][i] = dist(points[i], points[n - 1]);
    }
    std::cout << std::fixed << std::setprecision(6)
        << dist(points[n - 2], points[n - 1]) + min_from(0, 0, points, memo) << "\n";
    for (int i = 0; i < n - 1; i++) delete[] memo[i];
    delete[] memo;
    return 0;
}

/*
@"memo"[i][j]@ is the shortest possible sum of 2 paths which end at @i@ and @j@, where @j<i@.
@i+1@ gets added to either the path ending at @i@ (@"memo"[i+1][j]+|p[i+1]-p[i]|@) or ending at @j@ (@"memo"[i+1][i]+|p[i+1]-p[j]|@).
*/