class Solution {
public:
    int rob(vector<int>& num) {
        int n = num.size();
        vector<int>dp(n);
        dp[0] = num[0];
        if(n==1) return dp[0];
        dp[1] = max(num[0],num[1]);
        for(int i=2;i<n;i++){
            dp[i] = max(dp[i-1],dp[i-2]+num[i]);
        }
        return dp[n-1];
    }
};