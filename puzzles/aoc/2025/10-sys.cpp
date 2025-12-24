// !include ./10-util.cpp

struct Solver {
    int vars;
    mtx_t mtx;
    ints_t limits;
    std::unordered_map<int, int> basic;
    ints_t free;
    ints_t values;
    int free_sum = 0;
    Solver(ints_t &buttons, ints_t &counts) {
        vars = buttons.size();
        limits.resize(vars, 0);
        for (int i = 0; i < counts.size(); i++) {
            mtx.emplace_back();
            for (int j = 0; j < vars; j++) {
                mtx.back().push_back(buttons[j] >> i & 1);
                if (mtx.back().back()) limits[j] = std::max(limits[j], counts[i]);
            }
            mtx.back().push_back(counts[i]);
        }
        elim();
        for (int i = 0; i < vars; i++)
            if (!basic.contains(i))
                free.push_back(i);
    }
    void elim() {
        int eqs = mtx.size();
        for (int i = 0; i < eqs; i++) {
            int piv = 0;
            while (piv < vars && !mtx[i][piv]) piv++;
            if (piv == vars) continue;
            basic[piv] = i;
            int gcd = sgn(mtx[i][piv]) * std::accumulate(
                mtx[i].begin() + 1,
                mtx[i].end(),
                mtx[i][0],
                std::gcd<int, int>
            );
            for (int k = 0; k <= vars; k++) mtx[i][k] /= gcd;
            for (int j = 0; j < eqs; j++) {
                if (i == j) continue;
                int p = mtx[j][piv];
                for (int k = 0; k <= vars; k++)
                    mtx[j][k] = mtx[i][piv] * mtx[j][k] - mtx[i][k] * p;
            }
        }
    }
    int dfs() {
        int next = values.size();
        if (next == free.size()) {
            int presses = free_sum;
            for (auto &[col, row] : basic) {
                int sum = mtx[row].back();
                for (int i = 0; i < next; i++)
                    sum -= values[i] * mtx[row][free[i]];
                if (sum < 0 || sum % mtx[row][col]) return 0;
                presses += sum / mtx[row][col];
            }
            return presses;
        }
        int min = 0;
        for (values.push_back(0); values[next] <= limits[free[next]]; values[next]++, free_sum++) {
            int r = dfs();
            if (r && (!min || r < min)) min = r;
        }
        values.pop_back();
        free_sum -= limits[free[next]] + 1;
        return min;
    }
};

int part2(std::string &inp) {
    int sum = 0;
    for (auto &[buttons, _, counts] : read(inp))
        sum += Solver(buttons, counts).dfs();
    return sum;
}