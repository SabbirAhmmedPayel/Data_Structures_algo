#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX = 100;

int capacity[MAX][MAX], flow[MAX][MAX];
vector<int> adj[MAX];
int parent[MAX];
int n, source, sink;

bool bfs(int s, int t) {
    fill(parent, parent + n, -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int f = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(f, capacity[u][v] - flow[u][v]);
                if (v == t)
                    return true;
                q.push({v, new_flow});
            }
        }
    }
    return false;
}

int maxflow(int s, int t) {
    int total_flow = 0;

    while (bfs(s, t)) {
        int f = INF;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            f = min(f, capacity[prev][cur] - flow[prev][cur]);
            cur = prev;
        }

        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            flow[prev][cur] += f;
            flow[cur][prev] -= f;
            cur = prev;
        }

        total_flow += f;
    }

    return total_flow;
}

void dfs(int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v] && capacity[u][v] - flow[u][v] > 0)
            dfs(v, visited);
    }
}

void printMinCut(int s) {
    vector<bool> visited(n, false);
    dfs(s, visited);

    cout << "Min-Cut Edges:\n";
    for (int u = 0; u < n; ++u) {
        if (visited[u]) {
            for (int v : adj[u]) {
                if (!visited[v] && capacity[u][v] > 0) {
                    cout << u << " - " << v << " (cap: " << capacity[u][v] << ")\n";
                }
            }
        }
    }
}

int main() {
    // Example: build graph
    n = 6;
    source = 0, sink = 5;

    auto addEdge = [](int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // for residual graph
    };

    addEdge(0, 1, 16);
    addEdge(0, 2, 13);
    addEdge(1, 2, 10);
    addEdge(2, 1, 4);
    addEdge(1, 3, 12);
    addEdge(3, 2, 9);
    addEdge(2, 4, 14);
    addEdge(4, 3, 7);
    addEdge(3, 5, 20);
    addEdge(4, 5, 4);

    int mf = maxflow(source, sink);
    cout << "Max Flow: " << mf << "\n";

    printMinCut(source);
}
