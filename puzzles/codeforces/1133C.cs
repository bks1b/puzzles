int n = int.Parse(Console.ReadLine()!);
var arr = Console.ReadLine()!.Split().Select(int.Parse).Order().ToArray();
int start = 0;
int max = 1;
for (int end = 1; end < n; end++) {
    while (arr[end] - arr[start] > 5) start++;
    max = Math.Max(max, end - start + 1);
}
Console.WriteLine(max);