class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {

            int maxi = nums[0];

            // Find maximum from index 0 to i
            for (int j = 0; j <= i; j++) {
                maxi = max(maxi, nums[j]);
            }

            int mini = nums[i];

            // Find minimum from index i to n-1
            for (int j = i; j < n; j++) {
                mini = min(mini, nums[j]);
            }

            // Check if index i is stable
            if (maxi - mini <= k) {
                return i;
            }
        }

        return -1;
    }
};