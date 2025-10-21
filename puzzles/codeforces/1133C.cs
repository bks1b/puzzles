using System;
using System.Linq;

int n = int.Parse(Console.ReadLine());
var arr = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
Array.Sort(arr);
int start = 0;
int max = 0;
for (int end = 0; end < n; end++) {
    while (arr[end] - arr[start] > 5) start++;
    max = Math.Max(max, end - start + 1);
}
Console.WriteLine(max);