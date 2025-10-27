long[] Read() => Console.ReadLine()!.Split(' ').Select(long.Parse).ToArray();
(long, long) Pair() => Read() switch { [long a, long b] => (a, b) };

var (n, q) = Pair();
var items = Enumerable.Concat([0], Read().OrderByDescending(x => x)).ToArray();
for (long i = 0; i < n; i++) items[i + 1] += items[i];
while (q-- > 0) {
    var (x, y) = Pair();
    Console.WriteLine(items[x] - items[x - y]);
}