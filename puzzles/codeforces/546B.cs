Console.ReadLine()!;
var nums = Console.ReadLine()!.Split().Select(int.Parse).OrderDescending().ToArray();
int incr = 0;
int i = 0;
while (i < nums.Length - 1)
    if (nums[i] == nums[i + 1]) {
        nums[i]++;
        incr++;
        if (i > 0) i--;
    } else i++;
Console.WriteLine(incr);