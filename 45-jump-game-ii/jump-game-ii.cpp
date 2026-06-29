class Solution {
public:
    int jump(vector<int>& nums) {
        int jps = 0;
        int currentEnd = 0;
        int farthest = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            if (i == currentEnd) {
                jps++;
                currentEnd = farthest;
            }
        }
        return jps;
    }
};