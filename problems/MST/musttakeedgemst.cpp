#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const {
        return w < e.w;
    }
};

int find(int u, vector<int>& parent) {
    return parent[u] == u ? u : parent[u] = find(parent[u], parent);
}

bool unite(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = find(u, parent);
    v = find(v, parent);
    if (u == v) return false;
    if (rank[u] < rank[v]) swap(u, v);
    parent[v] = u;
    if (rank[u] == rank[v]) rank[u]++;
    return true;
}

int mstWithForcedEdge(int n, vector<Edge>& edges, Edge mustInclude) {
    sort(edges.begin(), edges.end());

    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);

    int cost = mustInclude.w;
    int count = 1;

    unite(mustInclude.u, mustInclude.v, parent, rank);  // Force include

    for (auto& e : edges) {
        if ((e.u == mustInclude.u && e.v == mustInclude.v && e.w == mustInclude.w) ||
            (e.u == mustInclude.v && e.v == mustInclude.u && e.w == mustInclude.w)) {
            continue; // skip duplicate of forced edge
        }

        if (unite(e.u, e.v, parent, rank)) {
            cost += e.w;
            count++;
        }
    }

    return (count == n - 1) ? cost : -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int u, v, w;
    cin >> u >> v >> w;  // Must include this edge

    int result = mstWithForcedEdge(n, edges, {u, v, w});
    if (result == -1)
        cout << "No MST including the given edge exists.\n";
    else
        cout << "Cost of MST including the edge: " << result << endl;
}
