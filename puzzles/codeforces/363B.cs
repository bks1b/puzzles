while (Console.Read() != ' ');
int k = int.Parse(Console.ReadLine()!);
var arr = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
int minI = 0;
int min = 0;
int sum = 0;
for (int i = 0; i < arr.Length; i++) {
    sum += arr[i];
    if (i >= k) sum -= arr[i - k];
    if (i == k - 1 || sum < min) {
        min = sum;
        minI = i - k + 2;
    }
}
Console.WriteLine(minI);