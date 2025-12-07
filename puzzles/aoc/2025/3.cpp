// !include ../../util.cpp

ll solve(std::string &inp, bool p2) {
    int len = 2 + 10 * p2;
    ll sum = 0;
    for (auto &line : split_string(inp, '\n')) {
        auto last_max = line.begin() - 1;
        ll num = 0;
        for (int i = 0; i < len; i++) {
            last_max = std::max_element(last_max + 1, line.end() - len + i + 1);
            num = 10 * num + (*last_max - '0');
        }
        sum += num;
    }
    return sum;
}