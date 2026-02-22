#include <iostream>
#include <cmath>

typedef long long ll;

int main() {
    int n, profit;
    std::cin >> n >> profit;
    ll *costs = new ll[n + 1];
    ll **dp = new ll*[n + 1];
    int max_len = std::sqrt(2 * n);
    costs[0] = 0;
    for (int i = 0; i <= n; i++) {
        if (i) {
            std::cin >> costs[i];
            costs[i] += costs[i - 1];
        }
        dp[i] = new ll[max_len + 1]();
    }
    for (int i = n; i--;) {
        ll acc = 0;
        for (int k = max_len; k--;)
            dp[i][k] = std::max(
                dp[i + 1][k],
                i + k < n ? (acc = std::max(
                    acc,
                    profit - costs[i + k + 1] + costs[i] + dp[i + k + 1][k + 1]
                )) : 0
            );
    }
    std::cout << dp[0][0] << "\n";
    for (int i = 0; i <= n; i++) delete[] dp[i];
    delete[] dp;
    delete[] costs;
    return 0;
}