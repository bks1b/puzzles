#include <iostream>
#include <queue>

int main() {
    int n, x;
    std::cin >> n >> x;
    std::queue<int> added;
    while (n--) {
        std::string ev;
        std::cin >> ev;
        if (ev == "ADD") added.push(n);
        if (ev == "EAT") {
            if (added.front() - n > x) {
                std::cout << "FAIL\n";
                return 0;
            }
            added.pop();
        }
    }
    std::cout << "SUCCESS\n";
    return 0;
}