class Solution {
public:
    static const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<long long> preNum(n + 1, 0);
        vector<long long> pow10(n + 1, 1);
        vector<int> preSum(n + 1, 0);
        vector<int> preCnt(n + 1, 0);

        // Precompute powers of 10 modulo MOD
        for (int i = 1; i <= n; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        // Prefix preprocessing
        for (int i = 0; i < n; i++) {
            int d = s[i] - '0';

            preSum[i + 1] = preSum[i] + d;
            preCnt[i + 1] = preCnt[i];
            preNum[i + 1] = preNum[i];

            if (d != 0) {
                preCnt[i + 1]++;
                preNum[i + 1] = (preNum[i] * 10 + d) % MOD;
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int sum = preSum[r + 1] - preSum[l];
            int cnt = preCnt[r + 1] - preCnt[l];

            long long x = (preNum[r + 1] -
                           preNum[l] * pow10[cnt] % MOD +
                           MOD) % MOD;

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};