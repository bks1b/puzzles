Console.ReadLine();
int[] nums = Console.ReadLine().Split().Select(int.Parse).Order().ToArray();
int count = 1;
ulong prevScore = 0;
ulong score = 0;
for (int i = 0; i < nums.Length; i++)
    if (i + 1 < nums.Length && nums[i] == nums[i + 1]) count++;
    else (count, prevScore, score) = (
        1,
        score,
        i >= count && nums[i] - nums[i - count] == 1
            ? Math.Max(score, prevScore + (ulong)nums[i] * (ulong)count)
            : score + (ulong)nums[i] * (ulong)count
    );
Console.WriteLine(score);