#include <iostream>
#include <unordered_map>
#include <set>

typedef long long ll;
typedef std::unordered_map<int, ll> map_t;
typedef std::multiset<ll> set_t;

void insert(map_t &map, set_t &set, int id, ll val) {
    map[id] = val;
    set.insert(val);
}

bool erase(map_t &map, set_t &set, int id) {
    auto it = map.find(id);
    if (it == map.end()) return false;
    set.erase(set.find(it->second));
    map.erase(it);
    return true;
}

int main() {
    ll start, end;
    int n;
    std::cin >> start >> end >> n;
    map_t end_vals, start_vals;
    set_t end_set, start_set;
    for (int i = 0; i < n; i++) {
        char op;
        int id;
        std::cin >> op >> id;
        if (op == '+') {
            ll from, to;
            std::cin >> from >> to;
            if (to >= end) insert(end_vals, end_set, id, from);
            else if (from <= start) insert(start_vals, start_set, id, to);
        } else erase(end_vals, end_set, id) || erase(start_vals, start_set, id);
        std::cout << (end_set.size()
            ? *end_set.begin() <= start
                ? 1
                : start_set.size() && *start_set.rbegin() >= *end_set.begin()
                    ? 2
                    : -1
            : -1) << "\n";
    }
    return 0;
}