class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long lazy = 0;
    };

    vector<Node> tree;

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = (l + r) / 2;
        long long val = tree[node].lazy;

        int leftLen = mid - l + 1;
        int rightLen = r - mid;

        tree[node * 2].sum =
            (tree[node * 2].sum + val * leftLen) % MOD;

        tree[node * 2 + 1].sum =
            (tree[node * 2 + 1].sum + val * rightLen) % MOD;

        tree[node * 2].lazy =
            (tree[node * 2].lazy + val) % MOD;

        tree[node * 2 + 1].lazy =
            (tree[node * 2 + 1].lazy + val) % MOD;

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, long long val) {

        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            tree[node].sum =
                (tree[node].sum + val * (r - l + 1)) % MOD;

            tree[node].lazy =
                (tree[node].lazy + val) % MOD;

            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;
    }

    long long query(int node, int l, int r,
                    int ql, int qr) {

        if (ql > r || qr < l)
            return 0;

        if (ql <= l && r <= qr)
            return tree[node].sum;

        push(node, l, r);

        int mid = (l + r) / 2;

        return (query(node * 2, l, mid, ql, qr) +
                query(node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        tree.resize(4 * n);
        vector<int> last(100001, -1);

        long long currentSquareSum = 0;
        long long answer = 0;

        for (int i = 0; i < n; i++) {

            int L = last[nums[i]] + 1;
            int R = i;
            long long oldSum = query(1, 0, n - 1, L, R);

            long long len = R - L + 1;
            long long increase =
                (2 * oldSum + len) % MOD;

            currentSquareSum =
                (currentSquareSum + increase) % MOD;
            update(1, 0, n - 1, L, R, 1);
            answer =
                (answer + currentSquareSum) % MOD;

            last[nums[i]] = i;
        }

        return answer;
    }
};