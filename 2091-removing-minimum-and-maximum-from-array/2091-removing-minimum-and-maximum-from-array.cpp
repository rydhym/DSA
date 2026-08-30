class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
    int n = nums.size();

    int minIndex = min_element(nums.begin(),nums.end())-nums.begin();
    int maxIndex = max_element(nums.begin(),nums.end())-nums.begin();

    int l = min(minIndex,maxIndex);
    int r = max(minIndex,maxIndex);

    int front = r+1;
    int back = n-l;
    int both = (l+1)+(n-r);

    return min({front,back,both});

    }
};