#include <iostream>
#include <cmath>

typedef unsigned long long ull;

int main() {
    int q;
    std::cin >> q;
    while (q--) {
        ull l, r;
        std::cin >> l >> r;
        ull start = 9 * std::ceil((l - 1) / 9.l);
        ull end = 9 * std::ceil(r / 9.l);
        ull sum = 0;
        while (l <= start) sum += (l++ - 1) % 9 + 1;
        while (r < end) sum -= r++ % 9 + 1;
        std::cout << (end - start) * 5 + sum << "\n";
    }
    return 0;
}