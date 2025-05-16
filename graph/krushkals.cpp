#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent, rank;

    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int a = find(x), b = find(y);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

void showMST(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<Edge> edges;

    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (adj[i][j] != 0)
                edges.push_back({i, j, adj[i][j]});
        }
    }

    sort(edges.begin(), edges.end());
    DSU dsu(V);
    int totalCost = 0;

    cout << "Edges in MST:\n";
    for (Edge e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalCost += e.weight;
            cout << e.u << " - " << e.v << " : " << e.weight << "\n";
        }
    }
    cout << "Total cost of MST: " << totalCost << "\n";
}

// Example usage
int main() {
    int V;
    cin >> V;
    vector<vector<int>> adj(V, vector<int>(V));

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> adj[i][j];

    showMST(adj);
    return 0;
}
