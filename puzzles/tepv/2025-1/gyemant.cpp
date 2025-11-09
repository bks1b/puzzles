#include <iostream>

int step(bool **img, int n, int m, int i, int j, int step) {
    int s = 0;
    while (i >= 0 && i < n && j - s >= 0 && j + s < m && img[i][j - s] && img[i][j + s]) {
        int black = j - s + 1;
        while (black < j + s && !img[i][black]) black++;
        if (black < j + s) break;
        s++;
        i += step;
    }
    return std::max(0, s - 1);
}

bool is_diamond(bool **img, int n, int m, int i, int j) {
    int s = step(img, n, m, i, j, 1);
    return s && s == step(img, n, m, i + 2 * s, j, -1);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    bool **img = new bool*[n];
    for (int i = 0; i < n; i++) {
        std::string r;
        std::cin >> r;
        img[i] = new bool[m];
        for (int j = 0; j < m; j++) img[i][j] = r[j] == '#';
    }
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (is_diamond(img, n, m, i, j)) count++;
    std::cout << count << "\n";
    return 0;
}