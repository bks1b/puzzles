using System;
using System.Linq;

int cases = int.Parse(Console.ReadLine());
while (cases-- > 0) {
    var line = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
    var a = line[0];
    var b = line[1];
    if (a > b) (a, b) = (b, a);
    int r = 1;
    while (a + b <= line[2]) {
        (a, b) = (b, a + b);
        r++;
    }
    Console.WriteLine(r);
}