class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (long long num : nums) {

            vector<long long> next(k, 0);

            // Start a new subarray [num]
            next[num % k]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * (num % k)) % k;
                next[newRemainder] += dp[r];
            }

            // Every subarray represented by next ends here
            for (int r = 0; r < k; r++) {
                ans[r] += next[r];
            }

            dp = next;
        }

        return ans;
    }
};