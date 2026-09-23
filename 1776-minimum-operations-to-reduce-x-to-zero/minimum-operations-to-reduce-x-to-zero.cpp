class Solution {
public:
    int minOperations(vector<int>& nums, int x) {

        int n = nums.size();

        // Find total sum
        long long total = 0;

        for (int num : nums) {
            total += num;
        }

        // Sum that should remain
        long long target = total - x;

        // Impossible because all numbers are positive
        if (target < 0) {
            return -1;
        }

        int left = 0;
        long long sum = 0;

        int maxLength = -1;

        for (int right = 0; right < n; right++) {

            sum += nums[right];

            // Shrink window
            while (sum > target && left <= right) {
                sum -= nums[left];
                left++;
            }

         // Found a subarray with sum = target
            if (sum == target) {
                maxLength = max(maxLength,
                                right - left + 1);
            }
        }
        if (maxLength == -1) {
            return -1;
        }

        return n - maxLength;
    }
};