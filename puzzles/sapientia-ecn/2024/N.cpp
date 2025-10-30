#include <iostream>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        std::string str;
        std::cin >> str;
        std::unordered_map<char, int> counts;
        char firstMax = str[0];
        char secondMax = 0;
        for (char c : str) {
            counts[c]++;
            if (c == firstMax) continue;
            if (counts[c] >= counts[firstMax]) {
                secondMax = firstMax;
                firstMax = c;
            } else if (!secondMax || counts[c] > counts[secondMax]) secondMax = c;
        }
        std::cout << str.size() - counts[firstMax] - (secondMax ? counts[secondMax] : 0) << "\n";
    }
    return 0;
}