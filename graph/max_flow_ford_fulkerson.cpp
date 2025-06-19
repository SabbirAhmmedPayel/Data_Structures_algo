#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define vi vector<int>
#define vii vector<vector<int>>

int dfs(int u, int t, int flow, int n, vii &graph, vi &visited) {
    if (u == t) return flow;
    visited[u] = true;

    for (int v = 0; v < n; ++v) {
        if (!visited[v] && graph[u][v] > 0) {
            int min_cap = min(flow, graph[u][v]);
            int currflow = dfs(v, t, min_cap, n, graph, visited);
            if (currflow > 0) {
                graph[u][v] -= currflow;
                graph[v][u] += currflow;
                return currflow;
            }
        }
    }
    return 0;
}

int fordFulkerson(int s, int t, int n, vii &graph) {
    int maxFlow = 0;
    vi visited(n);

    while (true) {
        for (int i = 0; i < n; ++i)  visited[i] = 0;

        int flow = dfs(s, t, 1e9, n, graph, visited);
        if (flow == 0) break;

        maxFlow += flow;
    }

    return maxFlow;
}

int main() {
    int n;
    cin >> n;
    vii graph(n, vi(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> graph[i][j];

    int s, t;
    cin >> s >> t;

    cout << "Maximum Flow: " << fordFulkerson(s, t, n, graph) << "\n";

    return 0;
}
