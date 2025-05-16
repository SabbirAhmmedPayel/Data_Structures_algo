#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void prim(const vector<vector<int>>& adj, int V) {
    vector<bool> vis(V, false);
    vector<int> key(V, 1e9), par(V, -1);
    key[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;

        for (int v = 0; v < V; ++v) {
            if (adj[u][v] && !vis[v] && adj[u][v] < key[v]) {
                key[v] = adj[u][v];
                par[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    int cost = 0;
    for (int i = 1; i < V; ++i) {
        cout << par[i] << " - " << i << " (Weight: " << adj[par[i]][i] << ")\n";
        cost += adj[par[i]][i];
    }
    cout << "Total cost of MST: " << cost << '\n';
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adj(V, vector<int>(V, 0));
    while (E--) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = w;
    }
    prim(adj, V);
}
