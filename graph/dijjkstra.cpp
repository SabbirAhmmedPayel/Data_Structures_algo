#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

<<<<<<< HEAD
class Compare {
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second; 
=======
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
>>>>>>> ed06302 (Your commit message here)
    }

    return dist;
}

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
<<<<<<< HEAD
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
=======
    int V = 5;
    vector<vector<int>> adjMatrix(V, vector<int>(V, INF));

    // Add edges
    adjMatrix[0][1] = 4;
    adjMatrix[1][0] = 4;

    adjMatrix[0][2] = 8;
    adjMatrix[2][0] = 8;

    adjMatrix[1][4] = 6;
    adjMatrix[4][1] = 6;

    adjMatrix[2][3] = 2;
    adjMatrix[3][2] = 2;

    adjMatrix[3][4] = 10;
    adjMatrix[4][3] = 10;

    int src = 0;
    vector<int> result = dijkstra(V, src, adjMatrix);

    for (int dist : result) {
        if (dist == INF) cout << "INF ";
        else cout << dist << " ";
    }
>>>>>>> ed06302 (Your commit message here)

    return 0;
}