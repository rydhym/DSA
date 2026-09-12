class Solution {
public:

    struct State {
        long long score;
        vector<int> indices;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.indices < b.indices;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<long long, 4>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(arr.begin(), arr.end());

        vector<long long> starts(n);

        for (int i = 0; i < n; i++) {
            starts[i] = arr[i][0];
        }
        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            next[i] = upper_bound(
                starts.begin(),
                starts.end(),
                arr[i][1]
            ) - starts.begin();
        }

        vector<vector<State>> dp(
            n + 1,
            vector<State>(5)
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {
                State skip = dp[i + 1][k];

                State take = dp[next[i]][k - 1];

                take.score += arr[i][2];
                take.indices.push_back(arr[i][3]);

                sort(take.indices.begin(), take.indices.end());
                if (better(take, skip))
                    dp[i][k] = take;
                else
                   dp[i][k] = skip;
            }
        }
        return dp[0][4].indices;
    }
};