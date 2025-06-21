#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9, MAX = 200;
int capacity[MAX][MAX], flow[MAX][MAX];
vector<int> adj[MAX];
int parent[MAX];

bool bfs(int s, int t, int n) {
    fill(parent, parent + n, -1);
    queue<pair<int, int>> q;
    q.push({s, INF});
    parent[s] = -2;

    while (!q.empty()) {
        int u = q.front().first, f = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push({v, min(f, capacity[u][v] - flow[u][v])});
            }
        }
    }
    return false;
}

int maxflow(int s, int t, int n) {
    int total = 0;
    while (bfs(s, t, n)) {
        int cur = t, f = INF;
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
        total += f;
    }
    return total;
}

int main() {
    int n_projects = 3;
    int S = n_projects, T = n_projects + 1;
    int N = n_projects + 2;

    // Profits: project 0 = 10, project 1 = 5, project 2 = 7
    int profit[] = {10, 5, 7};
    int totalProfit = 0;

    for (int i = 0; i < n_projects; ++i) {
        adj[S].push_back(i);
        adj[i].push_back(S);
        capacity[S][i] = profit[i];
        totalProfit += profit[i];
    }

    // Costs: project 0 = 0, project 1 = 3, project 2 = 6
    int cost[] = {0, 3, 6};
    for (int i = 0; i < n_projects; ++i) {
        if (cost[i]) {
            adj[i].push_back(T);
            adj[T].push_back(i);
            capacity[i][T] = cost[i];
        }
    }

    // Dependencies: if 0 is selected, 1 must be selected → add edge 0 → 1
    adj[0].push_back(1);
    adj[1].push_back(0);
    capacity[0][1] = INF;

    int cut = maxflow(S, T, N);
    int maxProfit = totalProfit - cut;
    cout << "Max total profit: " << maxProfit << endl;
}
