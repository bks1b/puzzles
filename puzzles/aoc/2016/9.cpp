#include <functional>

typedef long long ll;

ll f(std::string str, std::function<ll(int, int)> cb) {
    ll len = str.size();
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != '(') continue;
        int j = i;
        int k;
        while (str[j] != ')') {
            if (str[j] == 'x') k = j;
            j++;
        }
        int l = std::stoi(std::string(str.begin() + i + 1, str.begin() + k));
        len += cb(l, j) * std::stoi(std::string(str.begin() + k + 1, str.begin() + j)) + i - j - l - 1;
        i = j + l;
    }
    return len;
}

ll part1(std::string &inp) {
    return f(inp, [](int l, int) { return l; });
}

ll part2(std::string inp) {
    return f(inp, [&inp](int l, int j) {
        return part2(std::string(inp.begin() + j + 1, inp.begin() + j + l + 1));
    });
}