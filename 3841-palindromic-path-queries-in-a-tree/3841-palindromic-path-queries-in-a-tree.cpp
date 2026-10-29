class Solution {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sz;
    vector<int> seg;
    int curPos;
    int dfs(int u, int p) {
        parent[u] = p;
        sz[u] = 1;

        int maxSize = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            int childSize = dfs(v, u);

            sz[u] += childSize;

            if (childSize > maxSize) {
                maxSize = childSize;
                heavy[u] = v;
            }
        }

        return sz[u];
    }
    void decompose(int u, int h) {
        head[u] = h;
        pos[u] = curPos++;

        if (heavy[u] != -1)
            decompose(heavy[u], h);

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u])
                continue;

            decompose(v, v);
        }
    }
        void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }

        int mid = l + (r - l) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }
    int querySeg(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return seg[node];

        int mid = l + (r - l) / 2;

        return querySeg(node * 2, l, mid, ql, qr) ^
               querySeg(node * 2 + 1, mid + 1, r, ql, qr);
    }
        int pathQuery(int u, int v) {
        int mask = 0;

        while (head[u] != head[v]) {

            // Make u belong to deeper chain
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            mask ^= querySeg(
                1, 0, n - 1,
                pos[head[u]],
                pos[u]
            );

            u = parent[head[u]];
        }
        if (depth[u] > depth[v])
            swap(u, v);

        mask ^= querySeg(
            1, 0, n - 1,
            pos[u],
            pos[v]
        );

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;

        adj.assign(n, {});
        parent.resize(n);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.resize(n);
        pos.resize(n);
        sz.resize(n);

        seg.assign(4 * n, 0);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        dfs(0, -1);

        curPos = 0;
        decompose(0, 0);
        for (int i = 0; i < n; i++) {
            int mask = 1 << (s[i] - 'a');
            update(1, 0, n - 1, pos[i], mask);
        }

        vector<bool> ans;

        for (string q : queries) {
            stringstream ss(q);

            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;

                ss >> u >> c;

                s[u] = c;

                int mask = 1 << (c - 'a');

                update(
                    1, 0, n - 1,
                    pos[u],
                    mask
                );
            }
            else {
                int u, v;
                ss >> u >> v;

                int mask = pathQuery(u, v);
                bool possible =
                    (mask == 0) ||
                    ((mask & (mask - 1)) == 0);

                ans.push_back(possible);
            }
        }

        return ans;
    }
};