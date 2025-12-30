const ll N = std::pow(10, 16);

ll result(std::string _) {
    ll sum = 0;
    for (ll i = 1, j = 1; j < N; i++, j += 2 * i - 1) {
        if (i % 9 > 1) continue;
        int len = std::log10(j) + 1;
        for (int k = std::ceil(len / 2.) - 1, l = std::pow(10, k); k < std::ceil(len / 2.) + 1 && k < len; k++, l *= 10) {
            if (k < 1) continue;
            int b = j % l;
            int a = (j - b) / l;
            if (10 * b >= l && i == a + b) {
                sum += j;
                break;
            }
        }
    }
    return sum;
}

/*
@x@ is a 2025-number if and only if there exist @a,b,n>0@ such that @x=a*10^n+b=(a+b)^2@ and @10^(n-1)=<b<10^n@.
Reducing the first condition mod @9@: @a+b-=(a+b)^2 (mod 9) => a+b mod 9 in {0,1}@.
Let @10^k=<x<10^(k+1)@, then @10^(k-n)=<a<10^(k+1-n)@. Since @x=(a+b)^2@:

align < {
(10^(k-n)+10^(n-1))^2=<x<10^(k+1)
10^(2k-2n)+10^(2n-2)+2*10^(k-1)<10^(k+1)
10^(k-2n+1)+10^(2n-k-1)<98
100^(k-2n+1)-98*10^(k-2n+1)+1<0
}

Which implies @10^(k-2n+1)@ is between the 2 roots of @x^2-98x+1=0@:

49-20sqrt(6)<10^(k-2n+1)<49+20sqrt(6)

Approximately @-3<k-2n<1@, so @(k-1)/2<n<(k+3)/2@.
*/