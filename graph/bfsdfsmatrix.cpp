#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

// Node struct to represent each vertex in the graph
struct Node {
    int data;
    Node(int data) : data(data) {}
};

// Graph class using adjacency matrix representation
class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

public:
    // Constructor to initialize the graph with V vertices
    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    // Add an edge between two nodes
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    // BFS (Breadth-First Search) function
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            cout << node << " ";
            q.pop();

            for (int i = 0; i < V; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
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

        while (!s.empty()) {
            int node = s.top();
            cout << node << " ";
            s.pop();

            for (int i = 0; i < V; i++) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    s.push(i);
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

    cout << "Breadth-First Search (BFS) starting from vertex 0:" << endl;
    g.bfs(0); // BFS traversal starting from vertex 0

    cout << "Depth-First Search (DFS) starting from vertex 0:" << endl;
    g.dfs(0); // DFS traversal starting from vertex 0

    return 0;
}
