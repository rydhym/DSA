class Solution {
public:
    string minWindow(string s, string t) {
        int n=s.size();
        int m = t.size();
        if(m>n) return "";
        vector<int>hash(256,0); //(char,freq)
        for(int i=0;i<m;i++){
            hash[t[i]]++;
        }
        int l=0;
        int r=0;
        int minLen=INT_MAX;
        int startIndex=-1;
        int count= 0;

        while(r<n){
            if(hash[s[r]]>0){
                count ++;
            }
            hash[s[r]]--;
            while(count==m){
                int currLen = r-l+1;
                if(currLen<minLen){
                    minLen = currLen;
                    startIndex = l;
                }
                hash[s[l]]++;
                if(hash[s[l]]>0){
                    count--;
                }
                l++;
            }
            r++;
        }

        return startIndex == -1 ? "" : s.substr(startIndex, minLen);
    }
};