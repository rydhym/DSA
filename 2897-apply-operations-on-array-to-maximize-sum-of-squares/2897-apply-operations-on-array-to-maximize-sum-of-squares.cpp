class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;

        // nums[i] <= 1e9, so bits 0..30 are enough
        int cnt[31] = {};

        // Count how many times each bit appears
        for (int x : nums) {
            for (int bit = 0; bit < 31; bit++) {
                if (x & (1 << bit)) {
                    cnt[bit]++;
                }
            }
        }

        long long ans = 0;

        // Build k numbers greedily
        for (int i = 0; i < k; i++) {
            long long x = 0;

            for (int bit = 0; bit < 31; bit++) {
                if (cnt[bit] > 0) {
                    x |= (1LL << bit);
                    cnt[bit]--;
                }
            }

            ans = (ans + (x * x) % MOD) % MOD;
        }

        return (int)ans;
    }
};