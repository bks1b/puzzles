// !include ./10-util.cpp

typedef std::unordered_map<int, ints_t> memo_t;

int dfs(ints_t &buttons, ints_t counts, int remaining, memo_t &memo) {
    if (!remaining) return 0;
    int parity = 0;
    for (int i = counts.size(); i--;)
        parity = 2 * parity + (counts[i] & 1);
    if (!memo.contains(parity)) memo[parity] = filter_subsets(buttons, parity);
    int min = 0;
    for (int s : memo[parity]) {
        bool neg = false;
        int sub_rem = remaining;
        auto sub_counts = counts;
        for (int i = 0; i < counts.size(); i++) {
            bool pos = sub_counts[i];
            for (int j = 0; j < buttons.size(); j++)
                if ((s >> j & 1) && (buttons[j] >> i & 1))
                    sub_counts[i]--;
            if (pos && !sub_counts[i]) sub_rem--;
            if (sub_counts[i] < 0) neg = true;
            sub_counts[i] >>= 1;
        }
        if (neg) continue;
        int r = 2 * dfs(buttons, sub_counts, sub_rem, memo);
        if (sub_rem && !r) continue;
        while (s) {
            r += s & 1;
            s >>= 1;
        }
        if (!min || r < min) min = r;
    }
    return min;
}

int init_dfs(ints_t &buttons, ints_t &counts) {
    std::unordered_map<int, ints_t> memo;
    return dfs(buttons, counts, std::accumulate(counts.begin(), counts.end(), 0, [](int a, int b) {
        return a + !!b;
    }), memo);
}

int part2(std::string &inp) {
    int sum = 0;
    for (auto &[buttons, _, counts] : read(inp))
        sum += init_dfs(buttons, counts);
    return sum;
}