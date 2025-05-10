#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

using namespace std;
const int INF = 1e9;

struct Edge {
    int u, v, w;
};

void bellman_ford(int V, vector<Edge>& edges, vector<int>& h) {
    h.assign(V + 1, 0);
    for (int i = 0; i < V; ++i) {
        for (const auto& e : edges) {
            if (h[e.u] < INF && h[e.u] + e.w < h[e.v]) {
                h[e.v] = h[e.u] + e.w;
            }
        }
    }
}

vector<int> dijkstra(int src, int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(V, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void johnson(int V, vector<Edge>& edges) {
    // Step 1: Add a dummy node with zero-weight edges to all nodes
    for (int i = 0; i < V; ++i) {
        edges.push_back({V, i, 0});
    }

    vector<int> h;
    bellman_ford(V, edges, h); // h[i] will be the potential

    // Step 2: Reweight edges
    vector<vector<pair<int, int>>> adj(V);
    for (const auto& e : edges) {
        if (e.u == V) continue; // skip dummy edges
        int new_w = e.w + h[e.u] - h[e.v];
        adj[e.u].push_back({e.v, new_w});
    }

    // Step 3: Run Dijkstra from each vertex
    for (int u = 0; u < V; ++u) {
        vector<int> dist = dijkstra(u, V, adj);
        cout << "From node " << u << ":\n";
        for (int v = 0; v < V; ++v) {
            if (dist[v] == INF) cout << "  to " << v << " = INF\n";
            else cout << "  to " << v << " = " << dist[v] - h[u] + h[v] << "\n";
        }
    }
}

int main() {
    int V = 4; // number of vertices
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 1},
        {2, 1, 2}, {1, 3, 1},
        {2, 3, 5}
    };

    johnson(V, edges);
    return 0;
}