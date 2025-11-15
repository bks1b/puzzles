#include <iostream>

typedef long long ll;

int main() {
    int cases;
    std::cin >> cases;
    while (cases--) {
        int n, k;
        std::cin >> n >> k;
        ll *peaks = new ll[n];
        for (int i = 0; i < n; i++) std::cin >> peaks[i];
        ll min = -1;
        int max = 0;
        ll sum = 0;
        for (int i = 0; i <= n - k; i++) {
            if (i) sum += peaks[i + k - 1] - peaks[i - 1];
            if (--max < 0) {
                max = 0;
                for (int j = 0; j < k; j++) {
                    if (max + peaks[i + max] < j + peaks[i + j]) max = j;
                    if (!i) sum += peaks[j];
                }
            } else if (max + peaks[i + max] < k - 1 + peaks[i + k - 1]) max = k - 1;
            ll added = (max + peaks[i + max]) * k - sum;
            if (min < 0 || added < min) min = added;
        }
        delete[] peaks;
        std::cout << min - (k * (k - 1)) / 2 << "\n";
    }
    return 0;
}

/*
Since the minimum amount of units must be added, at least 1 peak must have no added units.
If we select this peak to have index @m in {0,ldots,k-1}@, then the peak with index @i@ has @h[m]+m-h[i]-i@ added units, where @h@ is the array of heights.
Select @m@ which maximizes @m+h[m]@, so that every peak has a nonnegative amount of units to be added. Then, the total amount of added units is @sum_(i=0)^(k-1) (h[m]+m-h[i]-i)@.
The naive algorithm recalculates the maximum @m@ and the number of added units for each window of length @k@, but it's possible to recalculate these based on the previous value.
*/