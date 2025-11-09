#include <sstream>
#include <regex>

std::vector<std::string> split_string(std::string s, char c) {
    std::vector<std::string> res;
    std::stringstream ss(s);
    std::string tok;
    while (getline(ss, tok, c)) res.push_back(tok);
    return res;
}

std::vector<int> match_ints(std::string &str) {
    std::regex r("\\d+");
    std::vector<int> res;
    for (auto it = std::sregex_iterator(str.begin(), str.end(), r); it != std::sregex_iterator(); ++it)
        res.push_back(std::stoi(it->str()));
    return res;
}

void pad_start(std::string &s, size_t n, char c) {
    if (s.size() < n) s.insert(0, n - s.size(), c);
}

int sgn(int n) {
    return (0 < n) - (n < 0);
}