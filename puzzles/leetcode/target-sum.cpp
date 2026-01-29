struct Solution {
    int findTargetSumWays(std::vector<int> &nums, int target) {
        int sum = std::accumulate(nums.begin(), nums.end(), target);
        if (sum < 0 || sum % 2) return 0;
        sum /= 2;
        std::vector<int> dp(sum + 1, 0);
        dp[0]++;
        for (int n : nums)
            for (int s = sum; s >= n; s--)
                dp[s] += dp[s - n];
        return dp[sum];
    }
};

/*
After all elements are assigned a sign, let @a,b@ be the sums of elements with positive and negative signs respectively.
Then @a+b@ is the sum of the input array, @a-b@ is the target, and the average of these is @a@.
Therefore, the problem is equivalent to finding all subsets of the input array which sum to this average.
*/