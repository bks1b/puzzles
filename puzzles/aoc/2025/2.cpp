#include <unordered_set>

// !include ../../util.cpp

ll solve(std::string &inp, bool p2) {
    ll sum = 0;
    for (auto &range : split_string(inp, ',')) {
        auto split = split_string(range, '-');
        ll int_start = std::stoll(split[0]);
        ll int_end = std::stoll(split[1]);
        ll dig = std::log10(int_start);
        ll exp = std::pow(10, dig);
        while (dig < std::log10(int_end)) {
            ll dig_start = std::max(exp, int_start);
            ll dig_end = std::min(10 * exp - 1, int_end);
            std::unordered_set<ll> included;
            for (ll r = 2; r <= (p2 ? dig + 1 : 2); r++) {
                if ((dig + 1) % r) continue;
                ll exp_r = std::pow(10, (dig + 1) / r);
                ll d = (10 * exp - 1) / (exp_r - 1);
                for (ll k = std::ceil(dig_start / (double)d); k * d <= dig_end; k++)
                    if (!included.contains(k * d)) {
                        sum += k * d;
                        included.insert(k * d);
                    }
            }
            exp *= 10;
            dig++;
        }
    }
    return sum;
}

/*
The number @x@ with @n@ digits being repeated @r@ times is:

<math>
x sum_(k=0)^(r-1) 10^(nk)=x (10^(nr)-1)/(10^n-1)

Suppose that a number @x@ with @n@ digits consists of a number being repeated some number of times.
- Let @r@ be the number of repetitions, then the number being repeated is @x*(10^(n//r)-1)/(10^n-1)=:qx@
To find all such numbers between @[a,b]@, we partition the interval by number of digits.
- In an interval with all numbers having @n@ digits, for each possible value of @r@ (divisors of @n@ starting from 2), we add the multiples of @q@ in the interval to the sum, excluding multiples which have been included before.
*/