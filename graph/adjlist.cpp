#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class GraphList {
private:
    int V;
    vector<vector<int>> adjList;
    vector<bool> visited;

public:
    GraphList(int V) {
        this->V = V;
        adjList.resize(V);
        visited.resize(V, false);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Remove for directed graph
    }


    

    void DFS(int node) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor])
                DFS(neighbor);
        }
    }

    void BFS(int start) {
        queue<int> q;
        fill(visited.begin(), visited.end(), false);
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
    vector<vector<int>> convertToAdjMatrix() {
        
        vector<vector<int>> adjMatrix(V, vector<int>(V, 0));
        for (int u = 0; u < V; u++) {
            for (int v : adjList[u]) {
                adjMatrix[u][v] = 1;  
                
            }
        }
        return adjMatrix;
    }

    void resetVisited() {
        fill(visited.begin(), visited.end(), false);
    }
};
