// !include ./Intcode.cpp

const int N = 5;

int solve(std::string &inp, bool p2) {
    int perm[N];
    for (int i = 0; i < N; i++) perm[i] = i + 5 * p2;
    int max = 0;
    do {
        Intcode *amps[N];
        for (int i = 0; i < N; i++)
            amps[i] = new Intcode(inp, { perm[i] });
        amps[0]->input.push_back(0);
        int halt = 0;
        while (!halt)
            for (int i = 0; i < N && !halt; i++) {
                int front = amps[i]->input.front();
                auto out = amps[i]->step(1);
                if (out.size()) amps[(i + 1) % N]->input.push_back(out.back());
                else halt = front;
            }
        for (int i = 0; i < N; i++) delete amps[i];
        max = std::max(max, halt);
    } while (std::next_permutation(perm, perm + N));
    return max;
}