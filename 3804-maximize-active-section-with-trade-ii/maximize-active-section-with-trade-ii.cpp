#include <bits/stdc++.h>
using namespace std;

struct Group {
    int start;
    int length;
};

class SparseTable {
public:
    SparseTable(const vector<int>& nums) : n(nums.size()) {
        if (n == 0) return;

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        st.assign(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            st[0][i] = nums[i];

        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = max(st[i - 1][j],
                               st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }

private:
    int n;
    vector<vector<int>> st;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int ones = 0;
        for (char c : s)
            if (c == '1')
                ones++;

        auto temp = getZeroGroups(s);
        vector<Group> zeroGroups = temp.first;
        vector<int> zeroGroupIndex = temp.second;

        if (zeroGroups.empty())
            return vector<int>(queries.size(), ones);

        SparseTable st(getZeroMergeLengths(zeroGroups));

        vector<int> ans;

        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];

            int left =
                zeroGroupIndex[l] == -1
                    ? -1
                    : (zeroGroups[zeroGroupIndex[l]].length -
                       (l - zeroGroups[zeroGroupIndex[l]].start));

            int right =
                zeroGroupIndex[r] == -1
                    ? -1
                    : (r - zeroGroups[zeroGroupIndex[r]].start + 1);

            auto p = mapToAdjacentGroupIndices(
                zeroGroupIndex[l] + 1,
                s[r] == '1' ? zeroGroupIndex[r]
                            : zeroGroupIndex[r] - 1);

            int startAdjacentGroupIndex = p.first;
            int endAdjacentGroupIndex = p.second;

            int activeSections = ones;

            if (s[l] == '0' &&
                s[r] == '0' &&
                zeroGroupIndex[l] + 1 == zeroGroupIndex[r]) {
                activeSections =
                    max(activeSections, ones + left + right);
            } else if (startAdjacentGroupIndex <= endAdjacentGroupIndex &&
                       endAdjacentGroupIndex >= 0) {
                activeSections =
                    max(activeSections,
                        ones + st.query(startAdjacentGroupIndex,
                                        endAdjacentGroupIndex));
            }

            if (s[l] == '0' &&
                zeroGroupIndex[l] + 1 <=
                    (s[r] == '1' ? zeroGroupIndex[r]
                                 : zeroGroupIndex[r] - 1)) {
                activeSections =
                    max(activeSections,
                        ones + left +
                            zeroGroups[zeroGroupIndex[l] + 1].length);
            }

            if (s[r] == '0' &&
                zeroGroupIndex[l] < zeroGroupIndex[r] - 1) {
                activeSections =
                    max(activeSections,
                        ones + right +
                            zeroGroups[zeroGroupIndex[r] - 1].length);
            }

            ans.push_back(activeSections);
        }

        return ans;
    }

private:
    pair<vector<Group>, vector<int>> getZeroGroups(const string& s) {
        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex;

        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0')
                    zeroGroups.back().length++;
                else
                    zeroGroups.push_back({i, 1});
            }
            zeroGroupIndex.push_back((int)zeroGroups.size() - 1);
        }

        return {zeroGroups, zeroGroupIndex};
    }

    vector<int> getZeroMergeLengths(const vector<Group>& zeroGroups) {
        vector<int> zeroMergeLengths;

        for (int i = 0; i + 1 < (int)zeroGroups.size(); i++) {
            zeroMergeLengths.push_back(
                zeroGroups[i].length +
                zeroGroups[i + 1].length);
        }

        return zeroMergeLengths;
    }

    pair<int, int> mapToAdjacentGroupIndices(int startGroupIndex,
                                             int endGroupIndex) {
        return {startGroupIndex, endGroupIndex - 1};
    }
};