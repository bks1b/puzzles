#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> indegs(n);
    std::vector<std::vector<int>> edges(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        indegs[u - 1]++;
        edges[v - 1].push_back(u - 1);
    }
    std::queue<int> no_incoming;
    for (int i = 0; i < n; i++)
        if (!indegs[i]) no_incoming.push(i);
    std::vector<int> result;
    while (!no_incoming.empty()) {
        int front = no_incoming.front();
        no_incoming.pop();
        result.push_back(front + 1);
        for (int n : edges[front]) {
            if (!--indegs[n]) no_incoming.push(n);
            m--;
        }
    }
    if (m) std::cout << "-1\n";
    else {
        std::cout << result.size() << "\n";
        for (int r : result) std::cout << r << " 1\n";
    }
    return 0;
}