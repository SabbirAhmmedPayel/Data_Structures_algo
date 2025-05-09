#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

void prim(const vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<int> key(V, INF); // minimum weight to connect to MST
    vector<int> parent(V, -1); // store MST edges

    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        // Find the minimum key vertex not yet included in MST
        int u = -1;
        int minKey = INF;
        for (int i = 0; i < V; ++i) {
            if (!visited[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }
        }

        visited[u] = true;

        // Update the keys of adjacent vertices
        for (int v = 0; v < V; ++v) {
            if (adj[u][v] && !visited[v] && adj[u][v] < key[v]) {
                key[v] = adj[u][v];
                parent[v] = u;
            }
        }
    }

    // Output
    int totalCost = 0;
    cout << "Edges in MST:\n";
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " (Weight: " << adj[parent[i]][i] << ")\n";
        totalCost += adj[parent[i]][i];
    }
    cout << "Total cost of MST: " << totalCost << "\n";
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adj(V, vector<int>(V, 0));

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w; // undirected
    }

    prim(adj, V);
    return 0;
}
