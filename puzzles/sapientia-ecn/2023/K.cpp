#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
    int r, s;
    std::cin >> r >> s;
    std::unordered_map<std::string, std::vector<std::string>> resources;
    for (int i = 0; i < r; i++) {
        std::string res;
        std::cin >> res;
        res.pop_back();
        while (std::cin.get() != '\n') {
            std::string d;
            std::cin >> d;
            resources[res].push_back(d);
        }
    }
    while (s--) {
        std::unordered_map<std::string, bool> included;
        std::vector<std::string> problems;
        for (int i = 0; i < r; i++) {
            std::string res;
            std::cin >> res;
            if (!(included[res] = std::all_of(
                resources[res].begin(),
                resources[res].end(),
                [&included](auto &d) { return included[d]; }
            ))) problems.push_back(res);
        }
        if (!problems.size()) std::cout << "No problematic resources.";
        else {
            std::cout << "Problematic resource" << (problems.size() > 1 ? "s" : "") << ":";
            for (auto &p : problems) std::cout << " " << p;
        }
        std::cout << "\n";
    }
    return 0;
}