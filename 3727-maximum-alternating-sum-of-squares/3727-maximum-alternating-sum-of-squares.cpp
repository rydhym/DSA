class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        vector<long long> sq;
        sq.reserve(n);

        for (long long x : nums) {
            sq.push_back(x * x);
        }

        sort(sq.begin(), sq.end());

        int negativeCount = n / 2;

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            if (i < negativeCount)
                ans -= sq[i];
            else
                ans += sq[i];
        }

        return ans;
    }
};