#include <iostream>

const int YEAR = 2024;

int sum(int n) {
    int r = 0;
    while (n) {
        r += n % 10;
        n /= 10;
    }
    return r;
}

int main() {
    int ps = 0;
    int i = 0;
    while (++i) {
        int n;
        std::cin >> n;
        if (!n) {
            std::cout << "-1\n";
            return 0;
        }
        ps += sum(n);
        if (n % YEAR == ps) {
            std::cout << i << "\n";
            return 0;
        }
    }
}