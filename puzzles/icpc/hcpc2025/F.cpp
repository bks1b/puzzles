#include <iostream>
#include <vector>
#include <unordered_map>

typedef std::vector<long> vec_t;
typedef std::vector<std::pair<int, int>> pairs_t;
typedef std::unordered_map<int, bool> history_t;

long match_dist(int n, vec_t &dists, vec_t &goal) {
    long d = goal[0] - dists[0];
    if (!d) return -1;
    for (int i = 1; i < n; i++) if (goal[i] - dists[i] != d) return -1;
    return d;
}

void update_dists(int to, long d, int from, history_t &history, pairs_t &trails, std::vector<vec_t> &dists) {
    if (history[to]) return;
    history[to] = true;
    dists[to][from] = d;
    for (auto &p : trails)
        if (p.first == to || p.second == to)
            update_dists(p.first + p.second - to, d + 1, from, history, trails, dists);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<vec_t> exit_dists(n, vec_t(n));
    for (auto &r : exit_dists)
        for (long &v : r) std::cin >> v;
    pairs_t trails;
    for (int i = 1; i < n; i++) {
        int from = i > 1 ? n : 0;
        long d;
        while ((d = match_dist(i, exit_dists[from], exit_dists[i])) < 0) from++;
        for (int j = 1; j < d; j++) {
            trails.push_back({ j > 1 ? exit_dists.size() - 1 : from, exit_dists.size() });
            vec_t dists(n);
            for (int k = 0; k < n; k++)
                dists[k] = exit_dists[from][k] + j;
            exit_dists.push_back(dists);
        }
        trails.push_back({ d > 1 ? exit_dists.size() - 1 : from, i });
        history_t history;
        update_dists(i, 0, i, history, trails, exit_dists);
    }
    std::cout << exit_dists.size() << "\n";
    for (auto &t : trails) std::cout << t.first + 1 << " " << t.second + 1 << "\n";
    return 0;
}

/*
For each glade, store its distances from the exit glades in a vector. To output the layout and to update distances, also store a set of trails (pairs of glade indices).
For each exit glade, find a glade from which it's possible to add a sequence of glades which leads to the given exit glade. For exit glade @2@, choose exit glade @1@.
Otherwise, to find this glade for the @i@-th exit glade, the difference of the first @i-1@ elements of the distance vectors of the found glade and the @i@-th exit glade must consist of 1 unique element.
This unique element is @1@ more than the amount of glades required to connect the found glade to exit glade @i@. After the glades have been added, update the distance of all glades from exit glade @i@.
*/