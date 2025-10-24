#include <iostream>

bool point_in_rect(int px, int py, int cx, int cy, int r) {
    return std::abs(px - cx) < r && std::abs(py - cy) < r;
}

bool non_empty(int c1, int r1, int c2, int r2) {
    return std::max(c1 - r1, c2 - r2) < std::min(c1 + r1, c2 + r2);
}

int main() {
    int a1, b1, r1, a2, b2, r2;
    std::cin >> a1 >> b1 >> r1 >> a2 >> b2 >> r2;
    std::cout << (point_in_rect(a1, b1, a2, b2, r2) || point_in_rect(a2, b2, a1, b1, r1)
        ? "MOVE"
        : non_empty(a1, r1, a2, r2) && non_empty(b1, r1, b2, r2)
            ? "FIGHT"
            : "PEACE") << "\n";
    return 0;
}