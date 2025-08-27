const int n = 16;

long result(std::string _) {
    long sum = 0;
    for (long b = 0;; b++) {
        int k = int(std::log10(b)) + 1;
        if (k > n / 2) return sum;
        long p = std::pow(10, k);
        double d = std::sqrt(p * p + 4 * b * (1 - p));
        if (d != long(d)) continue;
        for (int c = -1; c < 2; c += 2) {
            long r = (p - 2 * b + d * c) / 2 * p + b;
            if (r > 1) sum += r;
        }
    }
}

/*
The concatenation of @a@ and @b@ is a 2025-number if and only if @a*10^n+b=(a+b)^2@ where @10^(n-1)=<b<10^n@. Rearranging as a quadratic in @a@:

a^2+(2b-10^n)a+b^2-b=0
=> a=(10^n-2b+-sqrt(10^(2n)+4b(1-10^n)))/2

The result from the other file implies that the maximum length of @b@ is half of the exponent of the upper bound.
*/