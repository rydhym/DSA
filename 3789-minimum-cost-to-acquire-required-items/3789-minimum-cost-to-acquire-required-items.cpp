class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long common = min(need1, need2);
        long long ans1 =
            common * costBoth +
            (need1 - common) * 1LL * cost1 +
            (need2 - common) * 1LL * cost2;
        long long ans2 =
            max(need1, need2) * 1LL * costBoth;
        long long ans3 =
            need1 * 1LL * cost1 +
            need2 * 1LL * cost2;

        return min({ans1, ans2, ans3});
    }
};