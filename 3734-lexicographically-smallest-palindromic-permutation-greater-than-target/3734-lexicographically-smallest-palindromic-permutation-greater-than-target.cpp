#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string makePalindrome(string half, char mid) {
        string res = half;
        if (mid) res.push_back(mid);
        for (int i = (int)half.size() - 1; i >= 0; i--)
            res.push_back(half[i]);
        return res;
    }

    string lexPalindromicPermutation(string s, string target) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        vector<int> cnt(26);
        int m = s.size() / 2;

        for (int i = 0; i < 26; i++)
            cnt[i] = freq[i] / 2;

        string half = "";

        for (int pos = 0; pos < m; pos++) {
            for (int c = 0; c < 26; c++) {
                if (cnt[c] == 0)
                    continue;

                cnt[c]--;

                string temp = half;
                temp.push_back(char('a' + c));

                // Form the LARGEST possible first half with the remaining characters
                // to see if ANY valid palindrome > target can be made with this prefix.
                for (int k = 25; k >= 0; k--)
                    temp.append(cnt[k], char('a' + k));

                string max_pal = makePalindrome(temp, mid);

                if (max_pal > target) {
                    // This character works. Lock it in and break.
                    half.push_back(char('a' + c));
                    break;
                }

                // If it doesn't work, backtrack and try the next character.
                cnt[c]++;
            }
        }

        if ((int)half.size() != m)
            return "";

        string ans = makePalindrome(half, mid);
        return ans > target ? ans : "";
    }
};