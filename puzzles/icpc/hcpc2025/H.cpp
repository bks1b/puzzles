#include <iostream>
#include <list>

int main() {
    int n, x;
    std::cin >> n >> x;
    std::list<int> added;
    while (n--) {
        std::string ev;
        std::cin >> ev;
        if (ev == "ADD") added.push_back(n);
        if (ev == "EAT") {
            if (added.front() - n > x) {
                std::cout << "FAIL\n";
                return 0;
            }
            added.erase(added.begin());
        }
    }
    std::cout << "SUCCESS\n";
    return 0;
}