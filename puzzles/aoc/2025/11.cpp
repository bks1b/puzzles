// !include ../../util.cpp

typedef std::unordered_map<std::string, std::vector<std::string>> edges_t;
typedef std::unordered_map<std::string, int> memo_t;

auto read(std::string &inp) {
    edges_t edges;
    for (auto &line : split_string(inp, '\n')) {
        auto parts = split_string(line, ':');
        parts[1].erase(parts[1].begin());
        edges[parts[0]] = split_string(parts[1], ' ');
    }
    return edges;
}

int dfs(std::string root, std::string &dest, edges_t &edges, memo_t &memo) {
    if (root == dest) return 1;
    auto m = memo.find(root);
    if (m != memo.end()) return m->second;
    int sum = 0;
    for (auto &e : edges[root]) sum += dfs(e, dest, edges, memo);
    return memo[root] = sum;
}

ll init_dfs(std::string root, std::string dest, edges_t &edges) {
    memo_t memo;
    return dfs(root, dest, edges, memo);
}

int part1(std::string &inp) {
    auto edges = read(inp);
    return init_dfs("you", "out", edges);
}

ll part2(std::string &inp) {
    auto edges = read(inp);
    return init_dfs("svr", "fft", edges) * init_dfs("fft", "dac", edges) * init_dfs("dac", "out", edges)
        + init_dfs("svr", "dac", edges) * init_dfs("dac", "fft", edges) * init_dfs("fft", "out", edges);
}