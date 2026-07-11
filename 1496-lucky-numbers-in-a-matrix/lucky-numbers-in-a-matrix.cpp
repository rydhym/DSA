class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<int> ans;

        for (int i = 0; i < m; i++) {
            int minCol = 0;

            // Find minimum in row i
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] < matrix[i][minCol])
                    minCol = j;
            }

            // Check if it is maximum in its column
            bool lucky = true;
            for (int k = 0; k < m; k++) {
                if (matrix[k][minCol] > matrix[i][minCol]) {
                    lucky = false;
                    break;
                }
            }

            if (lucky)
                ans.push_back(matrix[i][minCol]);
        }

        return ans;
    }
};