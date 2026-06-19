class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int alt=0;
        int maxAlt=0;
        int n = gain.size();
        for(int i=0;i<n;i++){
            alt += gain[i];
            maxAlt = max(maxAlt,alt);
        }
        return maxAlt;
    }
};