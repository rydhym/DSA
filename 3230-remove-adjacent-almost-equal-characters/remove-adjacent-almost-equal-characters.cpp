class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int ans = 0;
        for(int i = 0;i<word.length();i++){
            if(abs(word[i] - word[i+1])<=1){
                ans++;
                i++;
            }
        }
        return ans;
    }
};