#include <iostream>

const int N = 10;

int main() {
    int i = 0;
    int sum = 0;
    int first = 0;
    int prev = 0;
    int x;
    while (std::cin >> x) {
        sum += std::max(0, x - prev);
        if (++i == N) {
            first = sum;
            sum = 0;
            prev = 0;
        } else prev = x;
    }
    std::cout << (sum < first) + 1 << "\n";
    return 0;
}