class Solution {
public:
    string smallestNumber(string num, long long t) {
        int n = num.size();
        int R2=0,R3=0,R5=0,R7=0;
        long long tt = t;
        while (tt % 2 == 0) { tt /= 2; R2++; }
        while (tt % 3 == 0) { tt /= 3; R3++; }
        while (tt % 5 == 0) { tt /= 5; R5++; }
        while (tt % 7 == 0) { tt /= 7; R7++; }
        if (tt != 1) return "-1";

        static const int dexp[10][4] = {
            {0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {2,0,0,0},
            {0,0,1,0}, {1,1,0,0}, {0,0,0,1}, {3,0,0,0}, {0,2,0,0}
        };

        vector<vector<int>> DP(R2+1, vector<int>(R3+1, 0));
        int optA[6] = {1,0,2,1,3,0};
        int optB[6] = {0,1,0,1,0,2};
        for (int i = 0; i <= R2; i++) {
            for (int j = 0; j <= R3; j++) {
                if (i == 0 && j == 0) continue;
                int best = INT_MAX;
                for (int k = 0; k < 6; k++) {
                    int a = optA[k], b = optB[k];
                    int pi = max(i - a, 0);
                    int pj = max(j - b, 0);
                    // FIX: skip self-referencing / no-progress transitions
                    if (pi == i && pj == j) continue;
                    int c = DP[pi][pj] + 1;
                    if (c < best) best = c;
                }
                DP[i][j] = best;
            }
        }

        auto need = [&](int r2, int r3, int r5, int r7) -> int {
            return DP[r2][r3] + r5 + r7;
        };

        vector<int> prefE2(n+1,0), prefE3(n+1,0), prefE5(n+1,0), prefE7(n+1,0);
        for (int i = 1; i <= n; i++) {
            int d = num[i-1] - '0';
            prefE2[i] = prefE2[i-1] + dexp[d][0];
            prefE3[i] = prefE3[i-1] + dexp[d][1];
            prefE5[i] = prefE5[i-1] + dexp[d][2];
            prefE7[i] = prefE7[i-1] + dexp[d][3];
        }

        bool hasZero = (num.find('0') != string::npos);
        if (!hasZero && prefE2[n] >= R2 && prefE3[n] >= R3 && prefE5[n] >= R5 && prefE7[n] >= R7) {
            return num;
        }

        size_t zPos = num.find('0');
        int startP = (zPos != string::npos) ? (int)zPos : n - 1;

        auto greedyConstruct = [&](int r2, int r3, int r5, int r7, int k) -> string {
            string res;
            res.reserve(k);
            for (int pos = 0; pos < k; pos++) {
                int rem = k - pos - 1;
                for (int d = 1; d <= 9; d++) {
                    int nr2 = max(r2 - dexp[d][0], 0);
                    int nr3 = max(r3 - dexp[d][1], 0);
                    int nr5 = max(r5 - dexp[d][2], 0);
                    int nr7 = max(r7 - dexp[d][3], 0);
                    if (need(nr2, nr3, nr5, nr7) <= rem) {
                        res.push_back('0' + d);
                        r2 = nr2; r3 = nr3; r5 = nr5; r7 = nr7;
                        break;
                    }
                }
            }
            return res;
        };

        for (int p = startP; p >= 0; p--) {
            int b2 = prefE2[p], b3 = prefE3[p], b5 = prefE5[p], b7 = prefE7[p];
            int m = n - 1 - p;
            for (int d = num[p] - '0' + 1; d <= 9; d++) {
                int t2 = b2 + dexp[d][0];
                int t3 = b3 + dexp[d][1];
                int t5 = b5 + dexp[d][2];
                int t7 = b7 + dexp[d][3];
                int r2 = max(R2 - t2, 0);
                int r3 = max(R3 - t3, 0);
                int r5 = max(R5 - t5, 0);
                int r7 = max(R7 - t7, 0);
                if (need(r2, r3, r5, r7) <= m) {
                    return num.substr(0, p) + char('0' + d) + greedyConstruct(r2, r3, r5, r7, m);
                }
            }
        }

        int L = max(n + 1, need(R2, R3, R5, R7));
        return greedyConstruct(R2, R3, R5, R7, L);
    }
};