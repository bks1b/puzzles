struct Solution {
    int trap(std::vector<int> &height) {
        int sum = 0;
        int ptrs[] = { 0, (int)height.size() - 1 };
        int maxes[] = { height[0], height.back() };
        while (ptrs[0] < ptrs[1]) {
            int i = height[ptrs[0]] > height[ptrs[1]];
            maxes[i] = std::max(maxes[i], height[ptrs[i]]);
            sum += maxes[i] - height[ptrs[i]];
            ptrs[i] += 1 - 2 * i;
        }
        return sum;
    }
};

/*
The height of a column, including the trapped water, is the minimum of maximum bar heights on each side, including the column itself.
By using 2 pointers starting from each endpoint, and stepping with whichever has the smaller bar height, the minimum of maximums is the maximum on the given side.
*/