class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {

        const int MAXD = 100000;

        vector<long long> freq(MAXD + 1, 0);

        // Store frequency of each difference
        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            freq[d]++;
        }

        long long k = (long long)k1 + k2;

        // Start reducing from largest difference
        for (int d = MAXD; d > 0 && k > 0; d--) {

            if (freq[d] == 0)
                continue;

            if (k >= freq[d]) {
                // Move ALL elements having difference d
                // down to d-1
                k -= freq[d];

                freq[d - 1] += freq[d];
                freq[d] = 0;
            }
            else {
                // Only some can be reduced
                freq[d] -= k;
                freq[d - 1] += k;
                k = 0;
            }
        }

        long long ans = 0;

        for (long long d = 1; d <= MAXD; d++) {
            ans += freq[d] * d * d;
        }

        return ans;
    }
};