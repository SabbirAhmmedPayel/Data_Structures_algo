#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

class Compare {
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second; 
    }
};

void dijkstra(const vector<vector<int>>& graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INF);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    pq.push({src, 0}); // {node, distance}

    while (!pq.empty()) {
        int u = pq.top().first;
        int d_u = pq.top().second;
        pq.pop();

        if (d_u > dist[u]) continue;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] > 0) {  // There is an edge
                int weight = graph[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({v, dist[v]});
                }
            }
        }
    }

   
    cout << "Shortest distances from node " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF)
            cout << "Node " << i << ": INF\n";
        else
            cout << "Node " << i << ": " << dist[i] << "\n";
    }
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    cout << "Enter adjacency matrix (enter 0 for no edge):\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> graph[i][j];

    int src;
    cout << "Enter source vertex (0-based index): ";
    cin >> src;

    dijkstra(graph, src);

    return 0;
}