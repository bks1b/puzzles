#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    int max = std::max(std::max(a, b), c);
    int s = a + b + c;
    std::cout << (s == 3 * max || (s == 2 * max && max == 2 * (max == c ? a : c)) ? "YES" : "NO") << "\n";
    return 0;
}

/*
Two possibilities:
- the squares are all congruent (placed in a row or column)
- two squares are congruent (placed in a row or column), the third one has 4 times the area (placed along the longer side of the rectangle)
*/