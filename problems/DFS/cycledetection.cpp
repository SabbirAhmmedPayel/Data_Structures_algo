#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

    bool dfs(int node, int parent, vector<bool>& visited) {
        visited[node] = true;

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, node, visited))
                    return true;
            } else if (neighbor != parent) {
                return true; // Found a back edge (cycle)
            }
        }

        return false;
    }

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Undirected
    }

    bool containsCycle() {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (dfs(i, -1, visited))
                    return true;
            }
        }

        return false;
    }
};
