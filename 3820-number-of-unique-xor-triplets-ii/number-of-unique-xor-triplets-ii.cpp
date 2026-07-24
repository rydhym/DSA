class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        vector<bool> present(2048, false);
        for (int x : nums) present[x] = true;

        vector<int> vals;
        for (int i = 0; i < 2048; i++)
            if (present[i]) vals.push_back(i);

        vector<bool> dp(2048, false);
        dp[0] = true;

        for (int step = 0; step < 3; step++) {
            vector<bool> ndp(2048, false);
            for (int x = 0; x < 2048; x++) {
                if (!dp[x]) continue;
                for (int v : vals)
                    ndp[x ^ v] = true;
            }
            dp = move(ndp);
        }

        int ans = 0;
        for (bool ok : dp)
            if (ok) ans++;

        return ans;
    }
};