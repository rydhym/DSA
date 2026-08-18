class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int,int>count;

        for(int i = 0;i<=nums.size()-k;i++){
            unordered_set<int>seen;
        for(int j = i;j<i+k;j++){
            seen.insert(nums[j]);
        }
        for(int num:seen){
            count[num]++;
        }
    }
    int ans = -1;
    for(auto &[num,freq]:count){
        if(freq==1){
            ans = max(ans,num);
        }
    }
return ans;
    }
};