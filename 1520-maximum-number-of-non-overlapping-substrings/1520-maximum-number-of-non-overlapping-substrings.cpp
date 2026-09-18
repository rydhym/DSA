class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> first(26, n);
        vector<int> last(26, -1);
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }
        vector<string> ans;
        int prevEnd = -1;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] != i)
                continue;
            int end = last[c];
            bool valid = true;
            for (int j = i; j <= end; j++) {
                int x = s[j] - 'a';
                if (first[x] < i) {
                    valid = false;
                    break;
                }
                end = max(end, last[x]);
            }
            if (!valid)
                continue;
            if (i > prevEnd) {
                ans.push_back(s.substr(i, end - i + 1));
            } else {
                ans.back() = s.substr(i, end - i + 1);
            }
            prevEnd = end;
        }

        return ans;
    }
};