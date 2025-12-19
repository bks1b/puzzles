#include <iostream>

const int N = 4;

int main() {
    int weights[N];
    for (int i = 0; i < N; i++) std::cin >> weights[i];
    for (int ss = 0; ss < 1 << N; ss++) {
        int incl = 0;
        int excl = 0;
        for (int i = 0; i < N; i++)
            *(ss >> i & 1 ? &incl : &excl) += weights[i];
        if (incl == excl) {
            std::cout << "IGEN\n";
            return 0;
        }
    }
    std::cout << "NEM\n";
    return 0;
}