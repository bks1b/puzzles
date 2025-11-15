#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

typedef std::unordered_set<int> boundary_t;
typedef std::unordered_map<int, int> dists_t;

void bfs_dists(int m, boundary_t &boundary, dists_t &dists) {
    std::queue<std::pair<int, int>> queue;
    for (int i : boundary) queue.push({ i, 0 });
    while (!queue.empty()) {
        auto [i, depth] = queue.front();
        queue.pop();
        if (dists.contains(i)) continue;
        dists[i] = depth;
        if (i % m < m - 1) queue.push({ i + 1, depth + 1 });
        if (i % m) queue.push({ i - 1, depth + 1 });
        if (i / m < m - 1) queue.push({ i + m, depth + 1 });
        if (i / m) queue.push({ i - m, depth + 1 });
    }
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        auto boundaries = new boundary_t[n]();
        auto dists = new dists_t[n]();
        for (int i = 0; i < n; i++) {
            bool *row = new bool[m + 1]();
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= m; k++) {
                    bool v = false;
                    if (j < m && k < m) std::cin >> v;
                    if (v != row[k]) boundaries[i].insert(k - 1 + (int)v + j * m);
                    if (k < m) {
                        if (v != row[k + 1]) boundaries[i].insert(k + (j - 1 + (int)v) * m);
                        row[k + 1] = v;
                    }
                }
            delete[] row;
            bfs_dists(m, boundaries[i], dists[i]);
        }
        int result = 0;
        for (int i = 0; i < n - 1; i++) {
            int min = -1;
            for (int b : boundaries[i])
                if (min < 0 || dists[i + 1][b] < min) min = dists[i + 1][b];
            result += min;
        }
        std::cout << result << "\n";
        delete[] boundaries;
        delete[] dists;
    }
    return 0;
}