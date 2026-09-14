class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        
        int n = img1.size();
        int ans = 0;
        for (int dx = -n + 1; dx <= n - 1; dx++) {
            for (int dy = -n + 1; dy <= n - 1; dy++) {

                int overlap = 0;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {

                        int newRow = i + dx;
                        int newCol = j + dy;

                        // Check if shifted position is inside img2
                        if (newRow >= 0 && newRow < n &&
                            newCol >= 0 && newCol < n) {

                            if (img1[i][j] == 1 &&
                                img2[newRow][newCol] == 1) {
                                    overlap++;
                            }
                        }
                    }
                }
                ans = max(ans, overlap);
            }
        }
        return ans;
    }
};