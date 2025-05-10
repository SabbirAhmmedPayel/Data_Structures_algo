#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
using namespace std;

class Graph {
private:
    int V; 
    vector<list<int>> adjList; 

public:
    // Constructor to initialize the graph with V vertices
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

  
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add v to u's list
        adjList[v].push_back(u); // Add u to v's list (undirected graph)
    }

    // BFS (Breadth-First Search) function
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ": ";
        
        while (!q.empty()) {
            int node = q.front();
            cout << node << " ";
            q.pop();

            // Traverse all the neighbors of the current node
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // DFS (Depth-First Search) function
    void dfs(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        visited[start] = true;
        s.push(start);

        cout << "DFS starting from vertex " << start << ": ";

        while (!s.empty()) {
            int node = s.top();
            cout << node << " ";
            s.pop();

            // Traverse all the neighbors of the current node
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Create a graph with 6 vertices
    Graph g(6);

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Perform BFS and DFS starting from vertex 0
    g.bfs(0); // BFS traversal starting from vertex 0
    g.dfs(0); // DFS traversal starting from vertex 0

    return 0;
}
