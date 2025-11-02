#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    long *dealers = new long[n];
    for (int i = 0; i < n; i++) std::cin >> dealers[i];
    auto transfers = new std::vector<long>[n]();
    while (m--) {
        int from, to;
        std::cin >> from >> to;
        transfers[to].push_back(dealers[from]);
        transfers[from].clear();
        dealers[to] += dealers[from];
        dealers[from] = 0;
    }
    delete[] dealers;
    std::vector<long> last;
    while (n--) last.insert(last.end(), transfers[n].begin(), transfers[n].end());
    delete[] transfers;
    std::sort(last.begin(), last.end(), std::greater());
    long sum = 0;
    for (long x : last) if (k-- > 0) sum += x;
    std::cout << sum << "\n";
    return 0;
}