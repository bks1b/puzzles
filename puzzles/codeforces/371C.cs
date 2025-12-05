long[] Read() => Console.ReadLine()!.Split().Select(long.Parse).ToArray();
string line = Console.ReadLine()!;
var pattern = "BSC".ToCharArray().Select(c => (long)line.Count(x => c == x)).ToArray();
var available = Read();
var prices = Read();
long have = Read()[0];
long need = 0;
foreach (var (a, b, c) in pattern.Zip(available, prices)) if (a > 0) {
    have += c * b;
    need += c * a;
}
bool loop = true;
while (loop) {
    long approx = have / need;
    int i = 0;
    while ((loop = i < prices.Length) && (pattern[i] == 0 || pattern[i] * approx >= available[i])) i++;
    if (!loop) Console.WriteLine(approx);
    else {
        long denom = need - prices[i] * pattern[i];
        loop = denom > 0 && have > (have = (
            available[i] = (have -= available[i] * prices[i]) * pattern[i] / denom
        ) * prices[i] + have);
        if (!loop) Console.WriteLine(0);
    }
}

/*
In general, for @n@ ingredients, when:
- the burger's structure is @(v_1,ldots,v_n)@ (excluding ingredients which do not occur)
- the prices are @(p_1,ldots,p_n)@
- the available items are @(c_1,ldots,c_n)@
- the budget is @b@
We need to find a tuple @(x_1,ldots,x_n)@ of nonnegative integers such that:
- @sum_(k=1)^n p_k x_k=<b@
- @min_(1=<k=<n)(floor((c_k+x_k)/v_k))@ is maximal
Suppose that for some tuple, there exits a @t@ such that @c_k+x_k=tv_k@ for all @k@.
Solving for @x_k@, taking the dot product with the tuple of prices, then solving for @t@:

<math>
t sum_(k=1)^n p_k v_k =< b+sum_(k=1)^n p_k c_k

If for the highest such integer value of @t@, @x_k>=0@ holds for all @k@, this @t@ is the solution.
Otherwise, we repeat the process, after setting @c_k:=r@ for the first @k@ for which @x_k<0@, to the highest @r@ such that @x_k>=0@ on the next iteration:

<math>
(b+sum_(j=1)^n p_j c_j)/(sum_(j=1)^n p_j v_j) v_k-r>=0
<=> (b-p_k c_k+sum_(j=1)^n p_j c_j) v_k >= r (-p_k v_k + sum_(j=1)^n p_j v_j)
*/