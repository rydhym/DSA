class Solution {
public:
    struct Node {
        uint8_t r, c;
        uint8_t e;
        uint16_t mask;
    };

    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        vector<vector<int>> id(m, vector<int>(n, -1));

        int sr = 0, sc = 0;
        int k = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    id[i][j] = k++;
                }
            }
        }

        int FULL = (1 << k) - 1;
        int MASKS = 1 << k;
        int E = energy + 1;

        auto encode = [&](int r, int c, int e, int mask) {
            return (((r * n + c) * E + e) * MASKS + mask);
        };

        vector<char> vis((size_t)m * n * E * MASKS, 0);

        queue<Node> q;
        q.push({(uint8_t)sr, (uint8_t)sc, (uint8_t)energy, 0});
        vis[encode(sr, sc, energy, 0)] = 1;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        int steps = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                Node cur = q.front();
                q.pop();

                if (cur.mask == FULL)
                    return steps;

                if (cur.e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = cur.r + dr[d];
                    int nc = cur.c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    char cell = classroom[nr][nc];
                    if (cell == 'X')
                        continue;

                    int ne = cur.e - 1;
                    if (cell == 'R')
                        ne = energy;

                    int nmask = cur.mask;
                    if (cell == 'L')
                        nmask |= (1 << id[nr][nc]);

                    int idx = encode(nr, nc, ne, nmask);

                    if (!vis[idx]) {
                        vis[idx] = 1;
                        q.push({(uint8_t)nr,
                                (uint8_t)nc,
                                (uint8_t)ne,
                                (uint16_t)nmask});
                    }
                }
            }

            steps++;
        }

        return -1;
    }
};