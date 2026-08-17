class Solution {
public:
    string sortVowels(string s) {
        string ans;
        string vowels;
        for(int i = 0;i<s.size();i++){
            if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
               s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' ||
               s[i] == 'O' || s[i] == 'U'){
                vowels+=s[i];
            }
        }
        sort(vowels.begin(),vowels.end());
        int j = 0;
        for(int i = 0;i<s.size();i++){
            if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
               s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' ||
               s[i] == 'O' || s[i] == 'U'){
                ans+=vowels[j];
                j++;
            }
            else{
                ans+=s[i];
            }
        }
        return ans;
    }
};