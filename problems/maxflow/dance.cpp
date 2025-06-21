#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205; // Max nodes (girls + boys + source + sink)
int capacity[MAXN][MAXN], parent[MAXN];
vector<int> adj[MAXN];

bool bfs(int s, int t) {
    fill(parent, parent + MAXN, -1);
    queue<int> q;
    q.push(s);
    parent[s] = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int edmondsKarp(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int aug = INT_MAX;
        for (int v = t; v != s; v = parent[v])
            aug = min(aug, capacity[parent[v]][v]);
        for (int v = t; v != s; v = parent[v]) {
            capacity[parent[v]][v] -= aug;
            capacity[v][parent[v]] += aug;
        }
        flow += aug;
    }
    return flow;
}

int main() {
    int m, n;
    cin >> m >> n;

    int G, B;
    cin >> G >> B;

    int p;
    cin >> p;

    int total = G + B;
    int s = total, t = total + 1;

    // Connect source to each girl
    for (int i = 0; i < G; ++i) {
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = n;
    }

    // Connect each boy to sink
    for (int i = 0; i < B; ++i) {
        int boy = G + i;
        adj[boy].push_back(t);
        adj[t].push_back(boy);
        capacity[boy][t] = n;
    }

    // Add registered dance pairs with capacity m
    for (int i = 0; i < p; ++i) {
        int x, y;
        cin >> x >> y;
        int girl = x;
        int boy = G + y;
        adj[girl].push_back(boy);
        adj[boy].push_back(girl);
        capacity[girl][boy] = m;
    }

    int maxDances = edmondsKarp(s, t);

    cout << "Maximum Dances: " << maxDances << "\n";

    // Output individual (girl, boy) pairs and their flow
    for (int x = 0; x < G; ++x) {
        for (int y : adj[x]) {
            if (y >= G && y < G + B && capacity[y][x] > 0) {
                cout << "(" << x << "," << (y - G) << ") => " << capacity[y][x] << " dances\n";
            }
        }
    }

    return 0;
}
