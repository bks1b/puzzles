// !include ../../util.cpp

ll solve(std::string &inp, bool p2) {
    int len = 2 + 10 * p2;
    ll sum = 0;
    for (auto &line : split_string(inp, '\n')) {
        std::string picked;
        for (int i = 0; i < line.size(); i++) {
            int j = std::max(len + i - (int)line.size(), 0);
            while (j < picked.size() && line[i] <= picked[j]) j++;
            if (j < len) picked = (j
                ? std::string(picked.begin(), picked.begin() + j)
                : "") + line[i];
        }
        sum += std::stoll(picked);
    }
    return sum;
}