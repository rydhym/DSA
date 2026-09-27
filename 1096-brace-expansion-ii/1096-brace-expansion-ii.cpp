class Solution {
public:
    set<string> parse(string &s, int &i) {
        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {

            // Union
            if (s[i] == ',') {
                result.insert(current.begin(), current.end());
                current = {""};
                i++;
            }

            else {
                set<string> next;

                // Nested expression
                if (s[i] == '{') {
                    i++;                    // skip {
                    next = parse(s, i);
                    i++;                    // skip }
                }

                // Letter
                else {
                    next.insert(string(1, s[i]));
                    i++;
                }

                // Concatenation:
                // current × next
                set<string> temp;

                for (auto &a : current) {
                    for (auto &b : next) {
                        temp.insert(a + b);
                    }
                }

                current = temp;
            }
        }

        // Add final part
        result.insert(current.begin(), current.end());

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};