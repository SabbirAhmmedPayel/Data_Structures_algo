#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;


class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, 
        vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                int wt = adj[u][i].second;

                if (dist[v] > dist[u] + wt) {
                    dist[v] = dist[u] + wt;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 8);
    g.addEdge(1, 4, 6);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 10);

    vector<int> result = g.dijkstra(0);

    for (int dist : result)
        cout << dist << " ";

    return 0;
}
