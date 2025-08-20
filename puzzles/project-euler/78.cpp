const long m = 1000000;

std::unordered_map<long, long> cache;
long partitions(long n) {
    if (n < 0) return 0;
    if (n < 2) return 1;
    if (cache.contains(n)) return cache[n];
    cache[n] = 0;
    long i = 1;
    int sign = 1;
    while (true) {
        long p = n - (i * (3 * i - 1)) / 2;
        if (p < 0) return cache[n];
        cache[n] = (cache[n] + sign * (partitions(n - (i * (3 * i + 1)) / 2) + partitions(p))) % m;
        i++; 
        sign *= -1;
    }
}

long result(std::string _) {
    long i = 1;
    while (partitions(++i) != 0) {}
    return i;
}