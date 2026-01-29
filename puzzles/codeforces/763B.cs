Console.WriteLine("YES");
int count = int.Parse(Console.ReadLine()!);
while (count-- > 0)
    if (Console.ReadLine()!.Split().Select(x => Math.Abs(int.Parse(x)) % 2).ToArray() is [int x, int y, ..])
        Console.WriteLine(3 * x + y - 2 * x * y + 1);

/*
Let @(x,y)@ be a rectangle's top left coordinates, then @(x mod 2, y mod 2)@ are both different from any neighboring rectangle.
We need to enumerate the 4 possible values of this pair, eg. with the function @(x,y) |-> 3x + y - 2xy + 1@.
*/