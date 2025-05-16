#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

vector<int> dijkstra(int V, int src, const vector<vector<int>>& adjMatrix) {
    vector<int> dist(V, INF);
    vector<bool> visited(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (adjMatrix[u][v] != INF && dist[v] > dist[u] + adjMatrix[u][v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V = 5;
    vector<vector<int>> adjMatrix(V, vector<int>(V, INF));

    // Add edges
    adjMatrix[0][1] = 4; adjMatrix[1][0] = 4;
    adjMatrix[0][2] = 8; adjMatrix[2][0] = 8;
    adjMatrix[1][4] = 6; adjMatrix[4][1] = 6;
    adjMatrix[2][3] = 2; adjMatrix[3][2] = 2;
    adjMatrix[3][4] = 10; adjMatrix[4][3] = 10;

    int src = 0;
    vector<int> dist = dijkstra(V, src, adjMatrix);

    cout << "Shortest distances from node " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) cout << "Node " << i << ": INF\n";
        else cout << "Node " << i << ": " << dist[i] << "\n";
    }

    return 0;
}
