class Solution {
public:
    string reverseParentheses(string s) {
        string ans = "";

        for (char ch : s) {

            if (ch != ')') {
                ans += ch;
            }
            else {
                string temp = "";

                while (ans.back() != '(') {
                    temp += ans.back();
                    ans.pop_back();
                }
                ans.pop_back();
                ans += temp;
            }
        }

        return ans;
    }
};