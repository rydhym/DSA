class Solution {
public:
    bool isRotation(const vector<int>& nums,
                    const vector<int>& sorted,
                    int start, int k) {

        // Build LPS array for sorted block
        vector<int> lps(k, 0);

        for (int i = 1, len = 0; i < k;) {
            if (sorted[start + i] == sorted[start + len]) {
                lps[i++] = ++len;
            }
            else if (len > 0) {
                len = lps[len - 1];
            }
            else {
                lps[i++] = 0;
            }
        }

        // Search sorted block inside nums block + nums block
        int j = 0;

        for (int i = 0; i < 2 * k - 1; i++) {
            int val = nums[start + (i % k)];

            while (j > 0 && val != sorted[start + j]) {
                j = lps[j - 1];
            }

            if (val == sorted[start + j]) {
                j++;
            }

            if (j == k) {
                return true;
            }
        }

        return false;
    }

    bool possible(const vector<int>& nums,
                  const vector<int>& sorted,
                  int k) {

        int n = nums.size();

        for (int start = 0; start < n; start += k) {
            if (!isRotation(nums, sorted, start, k)) {
                return false;
            }
        }

        return true;
    }

    long long sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        vector<int> divisors;

        // Find divisors of n
        for (int i = 1; 1LL * i * i <= n; i++) {
            if (n % i == 0) {
                divisors.push_back(i);

                if (i != n / i) {
                    divisors.push_back(n / i);
                }
            }
        }

        long long ans = 0;

        for (int k : divisors) {
            if (possible(nums, sorted, k)) {
                ans += k;
            }
        }

        return ans;
    }
};