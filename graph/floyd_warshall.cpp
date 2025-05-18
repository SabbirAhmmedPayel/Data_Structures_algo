#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; // Representation of infinity

class Graph {
private:
    int V;
    vector<vector<int>> dist;
    vector<vector<int>> next; // For path reconstruction

public:
    Graph(int vertices) {
        V = vertices;
        dist.resize(V, vector<int>(V, INF));
        next.resize(V, vector<int>(V, -1));

        // Distance to self is zero
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0;
            next[i][i] = i;
        }
    }

    void addEdge(int u, int v, int w) {
        dist[u][v] = w;
        next[u][v] = v; // Set direct path
    }

    void floydWarshall() {
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF && 
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k]; // Update path
                    }
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

    vector<int> getPath(int u, int v) {
        if (next[u][v] == -1) return {}; // No path

        vector<int> path = {u};
        while (u != v) {
            u = next[u][v];
            if (u == -1) return {}; // Just in case
            path.push_back(u);
        }
        return path;
    }

    void printPath(int u, int v) {
        vector<int> path = getPath(u, v);
        if (path.empty()) {
            cout << "No path from " << u << " to " << v << "\n";
        } else {
            cout << "Shortest path from " << u << " to " << v << ": ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 3, 10);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 1);

    g.floydWarshall();

    g.printDistanceMatrix();

    g.printPath(0, 3); // Expected: 0 1 2 3
}
