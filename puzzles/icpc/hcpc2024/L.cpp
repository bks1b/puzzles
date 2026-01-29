#include <iostream>
#include <cmath>

typedef unsigned long long ull;

int main() {
    int n, m;
    std::cin >> n >> m;
    ull *available = new ull[n];
    ull *costers = new ull[m];
    int remaining = m;
    for (int i = 0; i < n; i++) std::cin >> available[i];
    for (int i = 0; i < m; i++) {
        std::cin >> costers[i];
        remaining -= !costers[i];
    }
    while (remaining > 0)
        for (int i = 0; i < m; i++) {
            if (!costers[i]) continue;
            int p = std::log2(costers[i]);
            while (p >= 0 && (p >= n || !available[p])) p--;
            if (p < 0) {
                remaining = -1;
                break;
            }
            available[p]--;
            remaining -= !(costers[i] -= 1 << p);
        }
    delete[] available;
    delete[] costers;
    std::cout << (remaining ? "NO" : "YES") << "\n";
    return 0;
}