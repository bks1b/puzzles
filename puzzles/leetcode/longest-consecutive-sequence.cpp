struct Solution {
    int longestConsecutive(std::vector<int> &nums) {
        std::unordered_map<int, int> lengths;
        int result = 0;
        for (int n : nums)
            if (!lengths[n]) result = std::max(
                result,
                lengths[n - lengths[n - 1]]
                    = lengths[n + lengths[n + 1]]
                    = lengths[n]
                    = 1 + lengths[n - 1] + lengths[n + 1]
            );
        return result;
    }
};