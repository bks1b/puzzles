const int M = 1000000;

std::unordered_map<int, int> memo;
int partitions(int n) {
    if (n < 0) return 0;
    if (n < 2) return 1;
    if (memo.contains(n)) return memo[n];
    memo[n] = 0;
    int i = 1;
    int sign = 1;
    while (true) {
        int p = n - (i * (3 * i - 1)) / 2;
        if (p < 0) return memo[n];
        memo[n] = (memo[n] + sign * (partitions(n - (i * (3 * i + 1)) / 2) + partitions(p))) % M;
        i++;
        sign *= -1;
    }
}

int result(std::string _) {
    int i = 1;
    while (partitions(++i));
    return i;
}