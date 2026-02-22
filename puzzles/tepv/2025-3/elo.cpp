#include <iostream>
#include <set>
#include <unordered_map>

typedef std::set<std::pair<std::pair<int, int>, int>> set_t;
typedef std::unordered_map<int, int> memo_t;

int dp(int x, set_t &set, memo_t &memo) {
    int m = memo[x];
    if (m) return m;
    int max = x;
    auto it = set.upper_bound({ { x, 0 }, 0 });
    while (it != set.begin())
        if (-(--it)->first.second >= x)
            max = std::max(max, dp(x + it->second, set, memo));
    return memo[x] = max;
}

int main() {
    int n, x;
    std::cin >> n >> x;
    set_t set;
    while (n--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        set.insert({ { a, -b }, c });
    }
    memo_t memo;
    std::cout << dp(x, set, memo) << "\n";
    return 0;
}