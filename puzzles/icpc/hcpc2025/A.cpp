#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int *home = new int[100000]();
    int *teams = new int[n];
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        home[a - 1]++;
        teams[i] = b - 1;
    }
    for (int i = 0; i < n; i++)
        std::cout << n - 1 + home[teams[i]] << " " << n - 1 - home[teams[i]] << "\n";
    delete[] home;
    delete[] teams;
    return 0;
}