#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; // Representation of infinity

class Graph {
private:
    int V;
    vector<vector<int>> dist;

public:
    Graph(int vertices) {
        V = vertices;
        dist.resize(V, vector<int>(V, INF));

        // Distance to self is zero
        for (int i = 0; i < V; ++i)
            dist[i][i] = 0;
    }

    void addEdge(int u, int v, int w) {
        dist[u][v] = w; // directed graph; for undirected use: min(dist[u][v], w) and add dist[v][u]
    }

    void floydWarshall() {
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    void printDistanceMatrix() {
        cout << "All-Pairs Shortest Distance Matrix:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INF)
                    cout << "INF ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << "\n";
        }
    }
};
