#include <iostream>
#include <unordered_map>
#include <set>
#include <algorithm>

struct Person {
    int id;
    char adopted;
    std::string name;
    std::string dna;
    bool operator<(const Person &o) const {
        return id < o.id;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    Person *arr = new Person[n]();
    for (int i = 0; i < n; i++) {
        std::string dna;
        std::cin >> arr[i].id >> arr[i].dna >> arr[i].adopted;
        std::cin.get();
        std::getline(std::cin, arr[i].name);
    }
    std::unordered_map<std::string, std::set<Person>> groups;
    while (n--)
        if (groups[arr[n].dna].size() < 3)
            groups[arr[n].dna].insert(arr[n]);
    auto cmp = [](const std::set<Person> &a, const std::set<Person> &b) {
        return a.begin()->id < b.begin()->id;
    };
    std::set<std::set<Person>, decltype(cmp)> ordered(cmp);
    for (auto &g : groups)
        if (g.second.size() > 1 && std::any_of(
            g.second.begin(),
            g.second.end(),
            [](auto &p) { return p.adopted == 'A'; }
        )) ordered.insert(g.second);
    for (auto it = ordered.begin(); it != ordered.end(); it++) {
        for (auto &p : *it) std::cout << p.id << " " << p.name << "\n";
        if (std::next(it) != ordered.end()) std::cout << "\n";
    }
    return 0;
}