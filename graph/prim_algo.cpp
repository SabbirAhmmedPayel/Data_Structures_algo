#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int MAX = 1e5;
vector<pair<int, int>> adj[MAX]; // adj[u] = {v, weight}

void prim(int start, int V) {
    vector<bool> visited(V, false);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    pq.push({0, start, -1});  // {cost, currentNode, parent}
    int totalCost = 0;
    vector<pair<int, int>> mstEdges;

    while (!pq.empty()) {
        auto [cost, u, parent] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        
        visited[u] = true;
        totalCost += cost;

        if (parent != -1)
            mstEdges.push_back({parent, u}); // Edge included in MST

        for (auto [v, wt] : adj[u]) {
            if (!visited[v]) {
                pq.push({wt, v, u});
            }
        }
    }

    // Output
    cout << "Total cost of MST: " << totalCost << "\n";
    cout << "Edges in MST:\n";
    for (auto [u, v] : mstEdges) {
        cout << u << " - " << v << "\n";
    }
}

int main() {
    int V, E;
    cin >> V >> E;  // number of vertices and edges

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected graph
    }

    prim(0, V); // starting from node 0
    return 0;
}
