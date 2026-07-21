class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();

        int totalOnes = 0;
        int preZero = INT_MIN;   
        int maxMerge = 0;

        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }

            int len = j - i;

            if (s[i] == '1') {
                totalOnes += len;
            } else {
                maxMerge = max(maxMerge, preZero + len);
                preZero = len;
            }

            i = j;
        }

        return totalOnes + maxMerge;
    }
};