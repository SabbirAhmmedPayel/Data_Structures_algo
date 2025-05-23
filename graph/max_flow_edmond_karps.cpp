#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;

bool bfs(const vector<vector<int>>& residual, int s, int t, vector<int>& parent) {
    int n = residual.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && residual[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push(v);
                visited[v] = true;
            }
        }
    }
    return false;
}

int edmondsKarp(vector<vector<int>>& capacity, int source, int sink) {
    int n = capacity.size();
    vector<vector<int>> residual = capacity;
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(residual, source, sink, parent)) {
        int pathFlow = INF;

        for (int v = sink; v != source; v = parent[v])
            pathFlow = min(pathFlow, residual[parent[v]][v]);

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathFlow;
            residual[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int n = 6; // number of nodes
    vector<vector<int>> capacity(n, vector<int>(n, 0));

    // Sample graph edges with capacities
    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[1][3] = 12;
    capacity[2][1] = 4;
    capacity[2][4] = 14;
    capacity[3][2] = 9;
    capacity[3][5] = 20;
    capacity[4][3] = 7;
    capacity[4][5] = 4;

    int source = 0, sink = 5;

    cout << "Maximum Flow: " << edmondsKarp(capacity, source, sink) << endl;

    return 0;
}
