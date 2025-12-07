int solve(std::string &inp, bool p2) {
    int n = 0;
    for (int i = 0; i < inp.length(); i++) {
        if (inp[i] == '(') n++;
        else n--;
        if (p2 && n == -1) return i + 1;
    }
    return n;
}