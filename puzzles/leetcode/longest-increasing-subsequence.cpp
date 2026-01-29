struct Solution {
    int lengthOfLIS(std::vector<int> &nums) {
        std::vector<int> res = { nums[0] };
        for (int i = 1; i < nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
            if (it == res.end()) res.push_back(nums[i]);
            else *it = nums[i];
        }
        return res.size();
    }
};