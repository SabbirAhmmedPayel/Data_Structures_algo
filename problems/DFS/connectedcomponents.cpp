#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor])
                dfs(neighbor, visited);
        }
    }

    int countConnectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfs(i, visited);
                count++; // new connected component
            }
        }

        return count;
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(3, 4);
    g.addEdge(5, 6);

    int components = g.countConnectedComponents();
    cout << "Number of connected components: " << components << endl;

    return 0;
}
