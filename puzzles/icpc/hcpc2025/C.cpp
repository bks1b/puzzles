#include <iostream>

int query(int d, int k) {
    std::cout << "query " << d << std::string(k, '0') << "\n";
    std::cout.flush();
    int r;
    std::cin >> r;
    return r;
}

int main() {
    int k = 0;
    int s = query(0, 0);
    long long ans = 0;
    long long pow = 1;
    while (k < 18) {
        int min = 0;
        int max = 10;
        while (min < max - 1) {
            int d = (min + max) / 2;
            int r = query(d, k);
            if (r < s + d) max = d;
            else min = d;
        }
        ans += (9 - min) * pow;
        k++;
        pow *= 10;
    }
    std::cout << "answer " << ans << "\n";
    return 0;
}

/*
Let @f@ be the digit sum function.
Let @n,k in NN@, @b@ be the digit of @n@ at @10^k@, and @d in {0,ldots,9}@.
If @b=<9-d@, @f(n+d10^k)=f(n)+d@ because only the digit at @10^k@ is changed.
Otherwise, the digit at @10^k@ decreases by @10-d@, and the number increases by @10^(k+1)@: @f(n+d10^k)=f(n+10^(k+1))+d-10@.
In this case, if @l@ consecutive digits starting from @10^(k+1)@ are @9@s, then @f(n+10^(k+1))=f(n)-9l+1@.
Therefore:

<math>
f(n+d10^k)={
f(n)+d @ b=<9-d
f(n)+d-9(l+1)
}
*/