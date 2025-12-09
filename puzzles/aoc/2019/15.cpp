#include <queue>

// !include ./Intcode.cpp

typedef std::deque<int> dq_t;

dq_t bfs(Intcode &comp, dq_t last_input, int *max_len = nullptr) {
    std::queue<std::pair<std::pair<int, int>, dq_t>> queue;
    queue.push({ { 0, 0 }, last_input });
    std::unordered_map<int, std::unordered_map<int, bool>> visited;
    while (!queue.empty()) {
        auto [pos, dq] = queue.front();
        queue.pop();
        if (visited[pos.first][pos.second]) continue;
        visited[pos.first][pos.second] = true;
        int mismatch = 0;
        while (mismatch < last_input.size() && last_input[mismatch] == dq[mismatch]) mismatch++;
        while (last_input.size() > mismatch) {
            comp.input.push_back(3 + (last_input.back() > 2) * 4 - last_input.back());
            last_input.pop_back();
            comp.step(1);
        }
        last_input = dq;
        int res = 1;
        for (int i = mismatch; i < dq.size(); i++) {
            comp.input.push_back(dq[i]);
            res = comp.step(1)[0];
        }
        if (!res) {
            last_input.pop_back();
            continue;
        }
        if (res == 2) break;
        if (max_len) *max_len = std::max(*max_len, (int)last_input.size());
        for (int d = 1; d <= 4; d++) {
            queue.push({
                {
                    pos.first + (d > 2) * (2 * d - 7),
                    pos.second + (d < 3) * (2 * d - 3)
                },
                dq
            });
            queue.back().second.push_back(d);
        }
    }
    return last_input;
}

int part1(std::string &inp) {
    dq_t dq;
    Intcode comp(inp, dq);
    return bfs(comp, dq).size();
}

int part2(std::string &inp) {
    dq_t dq;
    Intcode comp(inp, dq);
    int max = 0;
    bfs(comp, dq = bfs(comp, dq), &max);
    return max - dq.size();
}