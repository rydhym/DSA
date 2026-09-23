class Solution {
public:

    struct Node {
        int prod;
        long long cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    int n;
    vector<Node> tree;


    Node mergeNode(const Node& L, const Node& R) {

        Node res;

        // Product of complete segment
        res.prod = (L.prod * R.prod) % k;

        // Prefixes completely inside LEFT
        for (int r = 0; r < k; r++) {
            res.cnt[r] += L.cnt[r];
        }

        // Prefixes containing whole LEFT
        // and some prefix of RIGHT
        for (int r = 0; r < k; r++) {

            int newRemainder =
                (L.prod * r) % k;

            res.cnt[newRemainder] += R.cnt[r];
        }

        return res;
    }


    void build(int node, int l, int r,
               vector<int>& nums) {

        if (l == r) {

            int rem = nums[l] % k;

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);
        tree[node] =
            mergeNode(tree[node * 2],
                      tree[node * 2 + 1]);
    }
    void update(int node, int l, int r,
                int index, int value) {
        if (l == r) {
            tree[node] = Node();
            int rem = value % k;
            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        if (index <= mid) {
            update(node * 2,
                   l, mid,
                   index, value);
        }
        else {
            update(node * 2 + 1,
                   mid + 1, r,
                   index, value);
        }
        tree[node] =
            mergeNode(tree[node * 2],
                      tree[node * 2 + 1]);
    }
    Node query(int node, int l, int r,
               int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if (qr <= mid) {
            return query(node * 2,
                         l, mid,
                         ql, qr);
        }
        if (ql > mid) {
            return query(node * 2 + 1,
                         mid + 1, r,
                         ql, qr);
        }
        Node left =
            query(node * 2,
                  l, mid,
                  ql, qr);
        Node right =
            query(node * 2 + 1,
                  mid + 1, r,
                  ql, qr);
        return mergeNode(left, right);
    }
    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries) {

        this->k = k;
        n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];
            update(1, 0, n - 1,
                   index, value);
            Node result =
                query(1, 0, n - 1,
                      start, n - 1);

            ans.push_back(result.cnt[x]);
        }

        return ans;
    }
};