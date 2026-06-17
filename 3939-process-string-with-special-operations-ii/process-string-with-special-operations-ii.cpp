class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.size();
        vector<long long>len(n+1,0);

        //forward: compute length
        for(int i=0;i<n;i++){
            char ch = s[i];
            if ('a' <= ch && ch <= 'z') {
               len[i + 1] = len[i] + 1;
            } else if (ch == '*') {
                len[i + 1] = (len[i] > 0 ? len[i] - 1 : 0);
            } else if (ch == '#') {
                len[i + 1] = min((long long)4e18, len[i] * 2);
            } else {
                len[i + 1] = len[i];
            }
        }
        if(k<0||k>=len[n]) return '.';

        //Backward
                for (int i = n - 1; i >= 0; i--) {
            char ch = s[i];
            long long before = len[i];
            long long after = len[i + 1];

            if ('a' <= ch && ch <= 'z') {
                if (k == after - 1) return ch;
            } else if (ch == '#') {
                if (before > 0) k %= before;
            } else if (ch == '%') {
                if (before > 0) k = before - 1 - k;
            }
        }
        return '-';
    }
};