class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        string ans;

        // Try to match target
        for (int i = 0; i < s.size(); i++) {
            int cur = target[i] - 'a';

            if (freq[cur] > 0) {
                ans += target[i];
                freq[cur]--;
            } 
            else {
                // Find smallest character greater than target[i]
                for (int c = cur + 1; c < 26; c++) {
                    if (freq[c] > 0) {
                        ans += char('a' + c);
                        freq[c]--;

                        // Append remaining characters in sorted order
                        for (int j = 0; j < 26; j++) {
                            ans += string(freq[j], char('a' + j));
                        }

                        return ans;
                    }
                }

                break;
            }
        }

        // Backtrack from right to left
        for (int i = ans.size() - 1; i >= 0; i--) {
            freq[ans[i] - 'a']++;

            int cur = target[i] - 'a';

            // Find smallest available character > target[i]
            for (int c = cur + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    string result = ans.substr(0, i);

                    result += char('a' + c);
                    freq[c]--;

                    // Add remaining characters in sorted order
                    for (int j = 0; j < 26; j++) {
                        result += string(freq[j], char('a' + j));
                    }

                    return result;
                }
            }
        }

        return "";
    }
};