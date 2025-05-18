#include <bits/stdc++.h>
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

    void addEdge(int u, int v, int w = 1) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // Remove for directed graph
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

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v]) {
                    int weight = adjMatrix[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        cout << "Dijkstra from " << src << ":\n";
        for (int i = 0; i < V; ++i)
            cout << "To " << i << ": " << dist[i] << "\n";
    }

    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        vector<vector<int>> edges;
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v]) {
                    edges.push_back({u, v, adjMatrix[u][v]});
                }
            }
        }

        for (int i = 0; i < V - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                cout << "Negative weight cycle detected\n";
                return;
            }
        }

        cout << "Bellman-Ford from " << src << ":\n";
        for (int i = 0; i < V; ++i)
            cout << "To " << i << ": " << dist[i] << "\n";
    }

    void floydWarshall() {
        vector<vector<int>> dist = adjMatrix;
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (i != j && dist[i][j] == 0)
                    dist[i][j] = INT_MAX;

        for (int k = 0; k < V; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = 0; j < V; ++j)
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        cout << "Floyd-Warshall:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INT_MAX)
                    cout << "INF ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void prim() {
        vector<int> key(V, INT_MAX);
        vector<bool> mstSet(V, false);
        vector<int> parent(V, -1);
        key[0] = 0;

        for (int count = 0; count < V - 1; ++count) {
            int u = -1;
            int minKey = INT_MAX;
            for (int v = 0; v < V; ++v)
                if (!mstSet[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }

            mstSet[u] = true;

            for (int v = 0; v < V; ++v)
                if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
        }

        cout << "Prim's MST:\n";
        for (int i = 1; i < V; ++i)
            cout << parent[i] << " - " << i << " : " << adjMatrix[i][parent[i]] << "\n";
    }

    int findParent(int u, vector<int>& parent) {
        if (parent[u] != u)
            parent[u] = findParent(parent[u], parent);
        return parent[u];
    }

    void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
        u = findParent(u, parent);
        v = findParent(v, parent);
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[v] < rank[u])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }

    void kruskal() {
        vector<vector<int>> edges;
        for (int u = 0; u < V; ++u) {
            for (int v = u + 1; v < V; ++v) {
                if (adjMatrix[u][v])
                    edges.push_back({adjMatrix[u][v], u, v});
            }
        }

        sort(edges.begin(), edges.end());

        vector<int> parent(V), rank(V, 0);
        for (int i = 0; i < V; ++i) parent[i] = i;

        cout << "Kruskal's MST:\n";
        for (const auto& edge : edges) {
            int w = edge[0];
            int u = edge[1];
            int v = edge[2];
            if (findParent(u, parent) != findParent(v, parent)) {
                cout << u << " - " << v << " : " << w << "\n";
                unionSet(u, v, parent, rank);
            }
        }
    }
};
int main() {
    GraphMatrix g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.dijkstra(0);
    g.bellmanFord(0);
    g.floydWarshall();
    g.prim();
    g.kruskal();

    return 0;
}
