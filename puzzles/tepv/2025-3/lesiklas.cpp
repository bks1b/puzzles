#include <iostream>
#include <functional>

int select(int n, std::function<int(int)> at) {
    int max = 0;
    int lower = 0;
    int i = 0;
    while (++i < n)
        if (at(i) == at(lower)) i = ++lower;
        else if (at(i) > at(lower)) {
            max = std::max(max, i - lower);
            lower = i;
        }
    return max;
}

int main() {
    int n;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) std::cin >> arr[i];
    std::cout << std::max(
        select(n, [arr](int i) { return arr[i]; }),
        select(n, [arr, n](int i) { return arr[n - i - 1]; })
    ) << "\n";
    delete[] arr;
    return 0;
}