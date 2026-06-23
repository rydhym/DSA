class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>ans;
        int n = s.size();
        int m = p.size();

        if(m>n) return ans;

        vector<int>pCount(256,0);
        vector<int>window(256,0);

        for(char ch:p){
            pCount[ch-'a']++;
        }
        for(int i=0;i<m;i++){
            window[s[i]-'a']++;
        }
        if(window==pCount){
            ans.push_back(0);
        }
        for(int i=m;i<n;i++){
            window[s[i]-'a']++;
            window[s[i-m]-'a']--;
            if(window==pCount){
                ans.push_back(i-m+1);
            }
        }
        return ans;
    }
};