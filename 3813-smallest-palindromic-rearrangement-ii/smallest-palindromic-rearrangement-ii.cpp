class Solution {
public:
    string smallestPalindrome(string s, int k) {
        long long K = k; // promote internally to avoid overflow during nCr math

        // Map out the frequency of all items
        vector<long long> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Get parameters for just the first half of the resulting string
        vector<long long> half(26, 0);
        string mid = "";
        long long m = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 != 0) {
                mid += string(1, (char)(i + 'a'));
            }
            half[i] = freq[i] / 2;
            m += half[i];
        }

        // Utility lambda to get remaining arrangements
        auto getWays = [&](vector<long long> f, long long targetK) -> long long {
            long long ways = 1;
            long long currLen = 0;
            for (long long count : f) {
                if (count > 0) {
                    currLen += count;
                    long long n = currLen;
                    long long r = count;

                    if (r > n - r) {
                        r = n - r;
                    }
                    long long curNCr = 1;

                    for (long long i = 1; i <= r; i++) {
                        curNCr = curNCr * (n - i + 1) / i;
                        if (curNCr > targetK) {
                            curNCr = targetK + 1;
                            break;
                        }
                    }
                    ways *= curNCr;
                    if (ways > targetK) {
                        return targetK + 1;
                    }
                }
            }
            return ways;
        };

        // Base requirement check to verify enough permutations exist
        if (getWays(half, K) < K) {
            return "";
        }

        string firstHalf = "";
        for (long long i = 0; i < m; i++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] > 0) {
                    half[c]--;
                    long long ways = getWays(half, K);

                    if (ways >= K) {
                        firstHalf += (char)(c + 'a');
                        break;
                    } else {
                        K -= ways;
                        half[c]++;
                    }
                }
            }
        }

        string res = firstHalf + mid;
        for (int i = (int)firstHalf.size() - 1; i >= 0; i--) {
            res += firstHalf[i];
        }
        return res;
    }
};