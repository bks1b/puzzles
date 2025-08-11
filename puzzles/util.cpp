#include <sstream>

template<class T>
std::vector<T> split_string(std::string &s, char c, std::function<T(std::string, int)> f) {
    std::vector<T> result;
    std::stringstream ss(s);
    std::string token;
    int i = 0;
    while (getline(ss, token, c)) result.push_back(f(token, i++));
    return result;
}

void pad_start(std::string &s, size_t n, char c) {
    if (s.size() < n) s.insert(0, n - s.size(), c);
}