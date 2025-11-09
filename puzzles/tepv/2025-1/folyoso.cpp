#include <iostream>
#include <vector>

typedef unsigned long long ull;

int main() {
    std::string str;
    std::cin >> str;
    std::vector<ull> lefts;
    for (int i = 0; i < str.size(); i++)
        lefts.push_back((i ? lefts.back() : 0) + (str[i] == '<'));
    ull sum = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '>') sum += lefts.back() - lefts[i];
    std::cout << sum << "\n";
    return 0;
}