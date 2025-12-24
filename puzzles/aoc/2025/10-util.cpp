#include <numeric>

// !include ../../util.cpp

typedef std::vector<int> ints_t;
typedef std::vector<ints_t> mtx_t;

auto read(std::string &inp) {
    std::vector<std::tuple<ints_t, int, ints_t>> res;
    for (auto &line : split_string(inp, '\n')) {
        auto parts = split_string(line, ' ');
        int bits = 0;
        for (int i = parts[0].size() - 1; --i;)
            bits = bits << 1 | (parts[0][i] == '#');
        ints_t buttons;
        ints_t counts;
        for (int i = 1; i < parts.size(); i++) {
            int btn = 0;
            for (auto &s : split_string(std::string(parts[i].begin() + 1, parts[i].end() - 1), ',')) {
                int n = std::stoi(s);
                if (i < parts.size() - 1) btn |= 1 << n;
                else counts.push_back(n);
            }
            if (i < parts.size() - 1) buttons.push_back(btn);
        }
        res.push_back({ buttons, bits, counts });
    }
    return res;
}

std::vector<mtx_t> subset_memo = { { { 0 } } };
mtx_t subsets(int n) {
    if (n < subset_memo.size()) return subset_memo[n];
    auto p = subsets(n - 1);
    subset_memo.push_back(mtx_t(n + 1));
    for (int i = 0; i < n; i++)
        for (int s : p[i]) {
            subset_memo[n][i].push_back(s << 1);
            subset_memo[n][i + 1].push_back(s << 1 | 1);
        }
    return subset_memo[n];
}

ints_t filter_subsets(ints_t &buttons, int bits) {
    ints_t res;
    for (auto &v : subsets(buttons.size()))
        for (int s : v) {
            int val = 0;
            for (int i = 0; i < buttons.size(); i++)
                if (s >> i & 1)
                    val ^= buttons[i];
            if (val == bits) res.push_back(s);
        }
    return res;
}

int part1(std::string &inp) {
    int sum = 0;
    for (auto &[buttons, bits, _] : read(inp)) {
        int s = filter_subsets(buttons, bits)[0];
        while (s) {
            sum += s & 1;
            s >>= 1;
        }
    }
    return sum;
}