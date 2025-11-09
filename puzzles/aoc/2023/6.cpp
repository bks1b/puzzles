// !include ../../util.cpp

ll get_interval(ll time, ll dist) {
    double d = std::sqrt(time * time - 4 * dist);
    return std::ceil((time + d) / 2 - 1) - std::floor((time - d) / 2 + 1) + 1;
}

void add_decimal(ll &sum, int n) {
    sum = sum * std::pow(10, (int)std::log10(n) + 1) + n;
}

int part1(std::string &inp) {
    auto lines = split_string(inp, '\n');
    auto times = match_ints(lines[0]);
    auto dists = match_ints(lines[1]);
    int res = 1;
    for (int i = 0; i < times.size(); i++) res *= get_interval(times[i], dists[i]);
    return res;
}

ll part2(std::string &inp) {
    auto lines = split_string(inp, '\n');
    auto times = match_ints(lines[0]);
    auto dists = match_ints(lines[1]);
    ll time = 0;
    ll dist = 0;
    for (int i = 0; i < times.size(); i++) {
        add_decimal(time, times[i]);
        add_decimal(dist, dists[i]);
    }
    return get_interval(time, dist);
}

/*
Given the time @l@ and distance @s@, the goal is to find the number of all integers @x@ such that @(l-x)*x>s@.
Since the coefficient of @x^2@ is negative, the solutions are exactly the integers between the 2 roots of @lx-x^2-s=0@ in @x@.
Equivalently: @x^2-lx+s=0@, or @x=(l+-sqrt(l^2-4s))/2@.
*/