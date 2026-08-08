class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        vector<int> suf(n1 + 1, 0);
        int j = n2 - 1;
        for (int i = n1 - 1; i >= 0; --i) {
            suf[i] = suf[i + 1];
            if (j >= 0 && word1[i] == word2[j]) {
                suf[i]++;
                j--;
            }
        }

        vector<int> result;
        int i = 0, k = 0;
        bool usedMismatch = false;

        while (i < n1 && k < n2) {
            if (word1[i] == word2[k]) {
                result.push_back(i);
                i++; k++;
            } else if (!usedMismatch && suf[i + 1] >= n2 - k - 1) {
                usedMismatch = true;
                result.push_back(i);
                i++; k++;
            } else {
                i++;
            }
        }

        return (k < n2) ? vector<int>{} : result;
    }
};