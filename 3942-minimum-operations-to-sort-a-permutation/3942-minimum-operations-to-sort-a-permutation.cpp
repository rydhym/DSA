class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        if (n <= 1) return 0;

        int pos0 = 0;

        // Find position of 0
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                pos0 = i;
                break;
            }
        }

        // -------------------------
        // Case 1: Circular increasing
        // -------------------------
        bool increasing = true;

        for (int k = 0; k < n; k++) {
            if (nums[(pos0 + k) % n] != k) {
                increasing = false;
                break;
            }
        }

        if (increasing) {
            // Method 1: rotate left pos0 times
            int option1 = pos0;

            // Method 2:
            // reverse -> rotate -> reverse
            int option2 = n - pos0 + 2;

            return min(option1, option2);
        }

        // -------------------------
        // Case 2: Circular decreasing
        // -------------------------
        bool decreasing = true;

        for (int k = 0; k < n; k++) {
            int expected = (n - k) % n;

            if (nums[(pos0 + k) % n] != expected) {
                decreasing = false;
                break;
            }
        }

        if (decreasing) {
            // Reverse first, then rotate
            int option1 = n - pos0;

            // Rotate first, then reverse
            int option2 = pos0 + 2;

            return min(option1, option2);
        }

        return -1;
    }
};