#include <iostream>

const int segments[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

int get_count(int h, int m) {
    return (h < 10 ? 0 : segments[h / 10]) + segments[h % 10] + segments[m / 10] + segments[m % 10];
}

bool check(int t, int c) {
    int h = t / 60;
    int m = t % 60;
    bool b = t >= 0 && h < 24 && get_count(h, m) == c;
    if (b) std::cout << h << ":" << (m < 10 ? "0" : "") << m << "\n";
    return b;
}

int main() {
    int h, m;
    std::cin >> h >> m;
    int l, r;
    l = r = 60 * h + m;
    int count = get_count(h, m);
    while (l > 0 || r < 24 * 60 - 1)
        if (check(--l, count) || check(++r, count)) return 0;
    std::cout << "Impossible\n";
    return 0;
}