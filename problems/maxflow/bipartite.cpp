#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

bool bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    fill(parent.begin(), parent.end(), -1);
    queue<pair<int, int>> q;
    q.push({s, INF});
    parent[s] = -2;

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return true;
                q.push({next, new_flow});
            }
        }
    }
    return false;
}

int maxflow(int s, int t, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    int flow = 0;
    vector<int> parent(adj.size());

    while (bfs(s, t, parent, capacity, adj)) {
        int cur = t;
        int new_flow = INF;

        // Find minimum capacity in path
        while (cur != s) {
            int prev = parent[cur];
            new_flow = min(new_flow, capacity[prev][cur]);
            cur = prev;
        }

        // Update residual graph
        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }

        flow += new_flow;
    }
    return flow;
}

int main() {
    int m, n, e;
    cin >> m >> n >> e; // left size, right size, number of edges

    // Total nodes = m left + n right + source + sink
    int total = m + n + 2;
    int source = 0, sink = total - 1;

    vector<vector<int>> adj(total);
    vector<vector<int>> capacity(total, vector<int>(total, 0));

    // Left side nodes: 1 to m
    // Right side nodes: m+1 to m+n

    for (int i = 1; i <= m; ++i) {
        adj[source].push_back(i);
        adj[i].push_back(source);
        capacity[source][i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        int v = m + i;
        adj[v].push_back(sink);
        adj[sink].push_back(v);
        capacity[v][sink] = 1;
    }

    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v; // 1-based index
        int uu = u, vv = m + v;
        adj[uu].push_back(vv);
        adj[vv].push_back(uu);
        capacity[uu][vv] = 1;
    }

    cout << maxflow(source, sink, capacity, adj) << endl;
    return 0;
}