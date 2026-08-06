class Solution {
public:
    int smallestNumber(int n, int t) {
        while(true){
            int product = 1;
            int num = n;
            while(num>0){
                int digit = num%10;
                product = product * digit;
                num = num/10;
            }
            if(product %t == 0){
                return n;
            }
            n = n+1;
        }
    }
};