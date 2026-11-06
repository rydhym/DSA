class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, 
                             int x, vector<int>& queries) {
        
        // Sort logs according to time
        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        // Store queries with their original index
        vector<pair<int, int>> q;

        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(queries.size());

        // cnt[server] = number of requests from that server
        // currently inside the sliding window
        vector<int> cnt(n + 1, 0);

        int activeServers = 0;

        int left = 0;
        int right = 0;

        for (auto [queryTime, index] : q) {

            // Add all logs with time <= queryTime
            while (right < logs.size() && 
                   logs[right][1] <= queryTime) {

                int server = logs[right][0];

                if (cnt[server] == 0) {
                    activeServers++;
                }

                cnt[server]++;
                right++;
            }

            // Remove logs with time < queryTime - x
            while (left < right && 
                   logs[left][1] < queryTime - x) {

                int server = logs[left][0];

                cnt[server]--;

                if (cnt[server] == 0) {
                    activeServers--;
                }

                left++;
            }

            // Servers with zero requests
            ans[index] = n - activeServers;
        }

        return ans;
    }
};