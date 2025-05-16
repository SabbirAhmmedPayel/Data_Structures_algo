#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

bool cmp(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int find(int u, vector<int>& parent) {
    return parent[u] == u ? u : parent[u] = find(parent[u], parent);
}

bool unite(int u, int v, vector<int>& parent, vector<int>& rank) {
    int pu = find(u, parent);
    int pv = find(v, parent);
    if (pu == pv) return false;
    if (rank[pu] < rank[pv]) swap(pu, pv);
    parent[pv] = pu;
    if (rank[pu] == rank[pv]) rank[pu]++;
    return true;
}

// Returns MST cost for a given edge weight increase x
pair<long long, long long> kruskal(vector<Edge> edges, int n) {
    sort(edges.begin(), edges.end(), cmp);
    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);
    long long cost = 0;
    long long originalCost = 0;
    int count = 0;

    for (Edge& e : edges) {
        if (unite(e.u, e.v, parent, rank)) {
            cost += e.w;
            originalCost += e.w;
            count++;
        }
    }
    if (count != n - 1) return {-1, -1}; // Not connected
    return {cost, originalCost};
}

int main() {
    int n, m;
    long long W;
    cin >> n >> m >> W;
    vector<Edge> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Binary search over possible weight boost
    long long l = 0, r = 1e6, answer = -1;
    while (l <= r) {
        long long mid = (l + r) / 2;
        vector<Edge> temp = edges;
        for (auto& e : temp) e.w += mid;

        auto [total, original] = kruskal(temp, n);

        if (original >= W) {
            answer = original;
            r = mid - 1; // Try to minimize further
        } else {
            l = mid + 1;
        }
    }

    if (answer == -1)
        cout << "No MST with weight >= " << W << " exists.\n";
    else
        cout << "Minimum MST weight >= " << W << " is: " << answer << "\n";
}
