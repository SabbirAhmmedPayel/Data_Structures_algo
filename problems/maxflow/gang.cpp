#include <bits/stdc++.h>
using namespace std;

struct Person {
    int exp, age, crim, origin, wp, trust, lang;
};

bool is_match(const Person &a, const Person &b) {
    return abs(a.exp - b.exp) <= 12 &&
           abs(a.age - b.age) <= 5 &&
           a.crim == b.crim &&
           a.origin == b.origin &&
           (a.wp + b.wp >= 1) &&
           (a.trust + b.trust >= 10) &&
           (a.lang & b.lang);
}

const int INF = 1e9;

bool bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacity, vector<vector<int>>& adj) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});
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
        while (cur != s) {
            int prev = parent[cur];
            new_flow = min(new_flow, capacity[prev][cur]);
            cur = prev;
        }
        flow += new_flow;
        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int m, n;
        cin >> m >> n;
        vector<Person> gang(m), partners(n);
        for (int i = 0; i < m; ++i)
            cin >> gang[i].exp >> gang[i].age >> gang[i].crim >> gang[i].origin
                >> gang[i].wp >> gang[i].trust >> gang[i].lang;
        for (int i = 0; i < n; ++i)
            cin >> partners[i].exp >> partners[i].age >> partners[i].crim >> partners[i].origin
                >> partners[i].wp >> partners[i].trust >> partners[i].lang;

        int V = m + n + 2;
        int src = 0, sink = V - 1;

        vector<vector<int>> capacity(V, vector<int>(V, 0));
        vector<vector<int>> adj(V);

        for (int i = 0; i < m; ++i) {
            int u = i + 1;
            capacity[src][u] = 1;
            adj[src].push_back(u);
            adj[u].push_back(src);
        }

        for (int j = 0; j < n; ++j) {
            int v = m + j + 1;
            capacity[v][sink] = 1;
            adj[v].push_back(sink);
            adj[sink].push_back(v);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (is_match(gang[i], partners[j])) {
                    int u = i + 1;
                    int v = m + j + 1;
                    capacity[u][v] = 1;
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }
            }
        }

        cout << maxflow(src, sink, capacity, adj) << "\n";
    }
    return 0;
}