class Solution {
public:
    long long countCommas(long long n) {

        long long ans = 0;

        for(long long start = 1000;start<=n;start*=1000){
            ans += n - start + 1;
            if(start>n/1000){
                break;
            }
        }
        return ans;
    }
};