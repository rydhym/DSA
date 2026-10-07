class Solution {
public:

    bool valid(string s) {
        int count = 0;

        for (char c : s) {

            if (c == '(') {
                count++;
            }

            else if (c == ')') {
                count--;

                if (count < 0)
                    return false;
            }
        }

        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;
        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {

            int size = q.size();

            for (int k = 0; k < size; k++) {

                string curr = q.front();
                q.pop();
                if (valid(curr)) {
                    ans.push_back(curr);
                    found = true;
                }

                if (found)
                    continue;
                for (int i = 0; i < curr.size(); i++) {
                    if (curr[i] != '(' && curr[i] != ')')
                        continue;

                    string next =
                        curr.substr(0, i) +
                        curr.substr(i + 1);

                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            if (found)
                break;
        }

        return ans;
    }
};