int cases = int.Parse(Console.ReadLine()!);
while (cases-- > 0) {
    int n = int.Parse(Console.ReadLine()!);
    var line = Console.ReadLine()!.Split(' ').Select(int.Parse).ToArray();
    var scores = new int[n];
    int max = 0;
    for (int i = n - 1; i >= 0; i--) {
        scores[i] = line[i] + (i + line[i] >= n ? 0 : scores[i + line[i]]);
        if (scores[i] > max) max = scores[i];
    }
    Console.WriteLine(max);
}