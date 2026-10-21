class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // Case 1: already sorted
        bool sorted = true;

        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }

        if (sorted)
            return 0;

        // Case 2: unsorted string of length 2
        // We cannot sort the whole string.
        if (n == 2)
            return -1;

        // Find minimum and maximum character
        char mn = s[0];
        char mx = s[0];

        for (char c : s) {
            mn = min(mn, c);
            mx = max(mx, c);
        }

        // Case 3: one operation
        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        // Case 4: two operations
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx)
                return 2;
        }

        // Case 5: three operations
        return 3;
    }
};