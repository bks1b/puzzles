#include <iostream>
#include <iomanip>
#include <algorithm>

double quadr(long long *a, double x) {
    return x * (a[0] * x + a[1]) + a[2];
}

int main() {
    int n;
    std::cin >> n;
    int **data = new int*[n];
    for (int i = 0; i < n; i++) {
        data[i] = new int[4];
        std::cin >> data[i][1] >> data[i][2] >> data[i][3] >> data[i][0];
    }
    std::sort(data, data + n, [](int *a, int *b) {
        return *a < *b;
    });
    long long partial[3] = { 0, 0, 0 };
    double max = 0;
    while (n--) {
        partial[0] += data[n][1];
        partial[1] += data[n][2];
        partial[2] += data[n][3];
        int lower = n ? data[n - 1][0] : 0;
        max = std::max(max, std::max(quadr(partial, lower), quadr(partial, data[n][0])));
        double der_x = partial[1] / (-2. * partial[0]);
        if (der_x > lower && der_x < data[n][0]) max = std::max(max, quadr(partial, der_x));
        delete[] data[n];
    }
    delete[] data;
    std::cout << std::fixed << std::setprecision(8) << max << "\n";
    return 0;
}