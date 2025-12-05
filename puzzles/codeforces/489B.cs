var lines = new int[2][];
for (int i = 0; i < 2; i++) {
    Console.ReadLine();
    lines[i] = Console.ReadLine()!.Split().Select(int.Parse).Order().ToArray();
}
int count = 0;
int p0 = 0;
int p1 = 0;
while (p0 < lines[0].Length && p1 < lines[1].Length)
    if (Math.Abs(lines[0][p0++] - lines[1][p1++]) < 2) count++;
    else if (lines[0][--p0] < lines[1][--p1]) p0++;
    else p1++;
Console.WriteLine(count);