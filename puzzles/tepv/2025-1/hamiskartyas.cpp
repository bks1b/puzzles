#include <iostream>

int main() {
    int n, p;
    std::cin >> n >> p;
    bool deck[4][13] = {};
    for (int i = 1; i <= n; i++) {
        int c, e;
        std::cin >> c >> e;
        deck[c - 1][e - 1] = true;
        int streak = 0;
        for (int j = std::max(1, e - 2); j <= e + 2 && j <= 13; j++)
            if (!deck[c - 1][j - 1]) streak = 0;
            else if (++streak == 3) {
                std::cout << std::max(1, i - p) << "\n";
                return 0;
            }
    }
    std::cout << "Lehetetlen\n";
    return 0;
}