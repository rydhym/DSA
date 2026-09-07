class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        vector<int> last(26, 0);
        for (int i = 1; i <= n; i++) {
            dp[i] = (2 * dp[i - 1]) % MOD;
            int ch = s[i - 1] - 'a';
            if (last[ch] != 0) {
                int j = last[ch];
                dp[i] = (dp[i] - dp[j - 1] + MOD) % MOD;
            }
            last[ch] = i;
        }
        return (dp[n] - 1 + MOD) % MOD;
    }
};