struct Solution {
    ListNode *merge(std::vector<ListNode*> &lists, int i, int j) {
        if (i == j) return lists[i];
        int mid = (i + j) / 2;
        auto a = merge(lists, i, mid);
        auto b = merge(lists, mid + 1, j);
        ListNode *root = nullptr;
        ListNode *end = nullptr;
        while (a || b) {
            auto &p = a && (!b || a->val < b->val) ? a : b;
            end = (root ? end->next : root) = p;
            p = p->next;
        }
        return root;
    }

    ListNode *mergeKLists(std::vector<ListNode*> &lists) {
        return lists.size()
            ? merge(lists, 0, lists.size() - 1)
            : nullptr;
    }
};