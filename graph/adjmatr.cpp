
#include<bits/stdc++.h>
using namespace std;


class GraphMatrix {
    private:
        int V;
        vector<vector<int>> adjMatrix;
        vector<bool> visited;
    
    public:
        GraphMatrix(int V) {
            this->V = V;
            adjMatrix.resize(V, vector<int>(V, 0));
            visited.resize(V, false);
        }
    
        void addEdge(int u, int v) {
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1; // Remove for directed graph
        }
    
        void DFS(int node) {
            visited[node] = true;
            cout << node << " ";
            for (int i = 0; i < V; ++i) {
                if (adjMatrix[node][i] && !visited[i])
                    DFS(i);
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
    
                for (int i = 0; i < V; ++i) {
                    if (adjMatrix[node][i] && !visited[i]) {
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
        }
    
        void resetVisited() {
            fill(visited.begin(), visited.end(), false);
        }
    };
    