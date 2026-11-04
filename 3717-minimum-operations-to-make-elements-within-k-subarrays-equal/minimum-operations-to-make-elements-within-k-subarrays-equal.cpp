class Solution {
public:
    using ll = long long;

    multiset<ll> low, high;
    ll sumLow = 0, sumHigh = 0;

    void balance() {
        // low should contain (size + 1) / 2 elements
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            ll v = *it;

            low.erase(it);
            sumLow -= v;

            high.insert(v);
            sumHigh += v;
        }

        while (low.size() < high.size()) {
            auto it = high.begin();
            ll v = *it;

            high.erase(it);
            sumHigh -= v;

            low.insert(v);
            sumLow += v;
        }
    }

    void add(ll v) {
        if (low.empty() || v <= *prev(low.end())) {
            low.insert(v);
            sumLow += v;
        } else {
            high.insert(v);
            sumHigh += v;
        }

        balance();
    }

    void remove(ll v) {
        auto it = low.find(v);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= v;
        } else {
            it = high.find(v);
            high.erase(it);
            sumHigh -= v;
        }

        balance();
    }

    ll getCost() {
        ll median = *prev(low.end());

        ll leftCost =
            median * (ll)low.size() - sumLow;

        ll rightCost =
            sumHigh - median * (ll)high.size();

        return leftCost + rightCost;
    }

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        // cost[i] = minimum operations required to make
        // nums[i ... i+x-1] equal
        vector<ll> cost(n - x + 1);

        low.clear();
        high.clear();
        sumLow = sumHigh = 0;

        // First window
        for (int i = 0; i < x; i++)
            add(nums[i]);

        cost[0] = getCost();

        // Sliding windows
        for (int i = 1; i + x <= n; i++) {
            remove(nums[i - 1]);
            add(nums[i + x - 1]);

            cost[i] = getCost();
        }

        const ll INF = 4e18;

        // dp[j][i]:
        // minimum cost to choose j subarrays
        // using first i elements
        vector<vector<ll>> dp(k + 1,
                              vector<ll>(n + 1, INF));

        for (int i = 0; i <= n; i++)
            dp[0][i] = 0;

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {

                // Don't end a selected subarray at i-1
                dp[j][i] = dp[j][i - 1];

                // Choose [i-x ... i-1]
                if (i >= x && dp[j - 1][i - x] != INF) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};