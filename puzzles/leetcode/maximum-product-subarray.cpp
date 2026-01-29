struct Solution {
    int maxProduct(std::vector<int> &nums) {
        int curr_max = 1;
        int curr_min = 1;
        int res = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            int a = curr_min * nums[i];
            int b = curr_max * nums[i];
            curr_min = std::min({ nums[i], a, b });
            res = std::max(res, curr_max = std::max({ nums[i], a, b }));
        }
        return res;
    }
};