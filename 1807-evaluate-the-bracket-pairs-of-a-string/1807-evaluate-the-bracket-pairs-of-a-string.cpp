class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        
        unordered_map<string, string> mp;

        // Store knowledge in hashmap
        for (auto &k : knowledge) {
            mp[k[0]] = k[1];
        }

        string ans = "";

        for (int i = 0; i < s.size(); i++) {

            // Normal character
            if (s[i] != '(') {
                ans += s[i];
            }

            // Start of a key
            else {
                i++;  // skip '('

                string key = "";

                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // i is now at ')'

                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                }
                else {
                    ans += "?";
                }
            }
        }

        return ans;
    }
};