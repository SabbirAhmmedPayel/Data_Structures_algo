#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 1000;
int capacity[MAX][MAX];   // capacity[u][v]
vector<int> adj[MAX];     // adjacency list
bool visited[MAX];

int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] > 0) {
            int min_cap = min(flow, capacity[u][v]);
            int pushed = dfs(v, t, min_cap);
            if (pushed > 0) {
                capacity[u][v] -= pushed;
                capacity[v][u] += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int fordFulkerson(int s, int t, int n) {
    int maxFlow = 0;

    while (true) {
        memset(visited, false, sizeof(visited));
        int flow = dfs(s, t, 1e9);  // find an augmenting path
        if (flow == 0) break;
        maxFlow += flow;
    }

    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m; // number of nodes and edges

    for (int i = 0; i < m; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        capacity[u][v] += cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // add reverse edge for residual graph
    }

    int s, t;
    cin >> s >> t;
    cout << "Maximum Flow: " << fordFulkerson(s, t, n) << "\n";

    return 0;
}
