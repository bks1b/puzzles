int Read() => int.Parse(Console.ReadLine()!);
int n = Read();
var nums = Console.ReadLine()!.Split().Select(int.Parse).Order().ToArray();
int q = Read();
var result = new int[q];
var queries = new (int, int)[q];
for (int i = 0; i < q; i++) queries[i] = (Read(), i);
Array.Sort(queries);
int l = 0;
foreach (var (v, i) in queries) {
    int r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (nums[m] > v) r = m;
        else l = m + 1;
    }
    result[i] = l;
}
foreach (int v in result) Console.WriteLine(v);