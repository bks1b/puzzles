#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

struct Node {
    std::set<Node*> edges;
    std::vector<Node*> ancestors;
    int label;
    int depth;
    int start;
    int end;

    void dfs(Node *parent, std::vector<int> &labels) {
        if (parent) {
            depth = parent->depth + 1;
            ancestors.push_back(parent);
            for (int i = 0; i < ancestors[i]->ancestors.size(); i++)
                ancestors.push_back(ancestors[i]->ancestors[i]);
        }
        start = labels.size();
        labels.push_back(label + 1);
        for (Node *next : edges) {
            next->edges.erase(this);
            next->dfs(this, labels);
        }
        end = labels.size() - 1;
    }

    int find_closest(std::vector<int> &query, int goal, int *prefix, std::vector<int> &labels) {
        int right = std::upper_bound(prefix + start, prefix + end + 1, goal) - prefix;
        int left = right - 1;
        while (left >= start && std::find(query.begin(), query.end(), labels[left]) != query.end()) left--;
        while (right <= end && std::find(query.begin(), query.end(), labels[right]) != query.end()) right++;
        if (left < start) return labels[right];
        if (right > end) return labels[left];
        int dl = std::abs(prefix[left] - goal);
        int dr = std::abs(prefix[right] - goal);
        return dl == dr
            ? std::min(labels[left], labels[right])
            : labels[dl > dr ? right : left];
    }
};

Node *lca(Node *a, Node *b) {
    if (a->depth > b->depth) std::swap(a, b);
    while (a->depth < b->depth)
        b = b->ancestors[std::log2(b->depth - a->depth)];
    if (a == b) return a;
    int i = a->ancestors.size();
    while (i--)
        if (a->ancestors[i] != b->ancestors[i]) {
            a = a->ancestors[i];
            b = b->ancestors[i];
            i = a->ancestors.size();
        }
    return a->ancestors[0];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n, q;
    std::cin >> n >> q;
    int *prefix = new int[n];
    Node *nodes = new Node[n]();
    for (int i = 0; i < n; i++) {
        nodes[i].label = i;
        std::cin >> prefix[i];
        if (i) prefix[i] += prefix[i - 1];
    }
    while (--n) {
        int a, b;
        std::cin >> a >> b;
        nodes[--a].edges.insert(nodes + --b);
        nodes[b].edges.insert(nodes + a);
    }
    std::vector<int> labels;
    nodes[0].dfs(nullptr, labels);
    while (q--) {
        int sum, k;
        std::cin >> sum >> k;
        std::vector<int> query;
        Node *root = nullptr;
        while (k--) {
            int v;
            std::cin >> v;
            query.push_back(v);
            Node *p = nodes + v - 1;
            sum -= prefix[p->start];
            root = root ? lca(root, p) : p;
        }
        std::cout << root->find_closest(query, sum, prefix, labels) << " ";
    }
    delete[] nodes;
    delete[] prefix;
    return 0;
}