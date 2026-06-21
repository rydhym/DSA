class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int number = 0;
        int count =0;
        for(int num:nums){
            if(count==0){
                number = num;
                count =1;
            }
            else if(num==number){
                count++;
            }
            else
                count--;
            
        }
        return number;
    }
};