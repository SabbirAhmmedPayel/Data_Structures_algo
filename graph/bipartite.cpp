#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // undirected graph
    }

    bool isBipartite() {
        vector<int> color(V, -1); // -1 means uncolored

        for (int start = 0; start < V; ++start) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0; // Start coloring with 0

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : adjList[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node]; // alternate color
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false; // same color on both ends
                        }
                    }
                }
            }
        }
        return true;
    }
};
