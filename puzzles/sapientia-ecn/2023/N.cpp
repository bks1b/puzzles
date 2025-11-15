#include <iostream>

int min_from(int x, int y, int p, int r, int c, int **grid, bool **pass, int ***memo) {
    if (x == c) return p == 0 ? 0 : __INT_MAX__;
    if (p < 0 || y < 0 || y >= r || grid[y][x] < 0) return __INT_MAX__;
    if (memo[y][x][p]) return memo[y][x][p];
    int min = __INT_MAX__;
    for (int dy = -1; dy < 2; dy++) min = std::min(
        min,
        min_from(x + 1, y + dy, p - pass[y][x], r, c, grid, pass, memo)
    );
    return memo[y][x][p] = min == __INT_MAX__ ? min : min + grid[y][x];
}

int main() {
    int r, c, p;
    std::cin >> r >> c >> p;
    int **grid = new int*[r];
    bool **pass = new bool*[r];
    for (int i = 0; i < r; i++) {
        grid[i] = new int[c]();
        pass[i] = new bool[c]();
        for (int j = 0; j < c; j++) {
            std::cin >> grid[i][j];
            if (i > 1 && j > 1) {
                int v = grid[i - 1][j - 1];
                pass[i - 1][j - 1] = grid[i - 1][j - 2] > -1 && grid[i - 1][j] > -1
                    && v < grid[i - 2][j - 1] && v < grid[i][j - 1]
                    && v > grid[i - 1][j - 2] && v > grid[i - 1][j];
            }
        }
    }
    int ***memo = new int**[r];
    for (int i = 0; i < r; i++) {
        memo[i] = new int*[c];
        for (int j = 0; j < c; j++)
            memo[i][j] = new int[p + 1]();
    }
    int min = -1;
    for (int i = 0; i < r; i++) {
        int d = min_from(0, i, p, r, c, grid, pass, memo);
        if (min < 0 || d < min) min = d;
    }
    if (min == __INT_MAX__) std::cout << "impossible\n";
    else std::cout << min << "\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            delete[] memo[i][j];
        delete[] memo[i];
    }
    delete[] memo;
    return 0;
}