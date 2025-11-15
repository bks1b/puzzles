#include <iostream>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        std::string str;
        std::cin >> str;
        std::unordered_map<char, int> counts;
        char first_max = str[0];
        char second_max = 0;
        for (char c : str) {
            counts[c]++;
            if (c == first_max) continue;
            if (counts[c] >= counts[first_max]) {
                second_max = first_max;
                first_max = c;
            } else if (!second_max || counts[c] > counts[second_max]) second_max = c;
        }
        std::cout << str.size() - counts[first_max] - (second_max ? counts[second_max] : 0) << "\n";
    }
    return 0;
}