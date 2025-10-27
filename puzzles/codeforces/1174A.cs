int n = int.Parse(Console.ReadLine()!);
var line = Console.ReadLine()!.Split(' ').Select(int.Parse).ToArray();
var (first, last) = (line.Take(n).ToArray(), line.Skip(n).ToArray());
var (max, min) = (first.Max(), last.Min());
bool eq = first.Sum() == last.Sum();
if (eq) {
    first[Array.IndexOf(first, max)] = min;
    last[Array.IndexOf(last, min)] = max;
}
Console.WriteLine(min == max && eq ? -1 : string.Join(" ", first.Concat(last)));