#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAX = 200;

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
    int J = 4; // number of jobs
    int M = 3; // number of machines
    int machine_capacity[] = {2, 1, 2}; // max jobs each machine can run

    int S = J + M;        // source index
    int T = J + M + 1;    // sink index
    int N = J + M + 2;    // total nodes

    // Sample compatibility list: job i can go to machine j if compatibility[i][j] == 1
    int compatibility[4][3] = {
        {1, 0, 1},  // job 0: machine 0, 2
        {1, 1, 0},  // job 1: machine 0, 1
        {0, 1, 1},  // job 2: machine 1, 2
        {1, 0, 0},  // job 3: machine 0
    };

    // Build graph
    for (int i = 0; i < J; ++i) {
        adj[S].push_back(i);
        adj[i].push_back(S);
        capacity[S][i] = 1;
    }

    for (int j = 0; j < M; ++j) {
        int machine_node = J + j;
        adj[machine_node].push_back(T);
        adj[T].push_back(machine_node);
        capacity[machine_node][T] = machine_capacity[j];
    }

    for (int i = 0; i < J; ++i) {
        for (int j = 0; j < M; ++j) {
            if (compatibility[i][j]) {
                int job_node = i;
                int machine_node = J + j;
                adj[job_node].push_back(machine_node);
                adj[machine_node].push_back(job_node);
                capacity[job_node][machine_node] = 1;
            }
        }
    }

    int result = maxflow(S, T, N);
    cout << "Maximum number of jobs assigned: " << result << "\n";

    // Optional: print assignments
    cout << "Job Assignments:\n";
    for (int i = 0; i < J; ++i) {
        for (int j : adj[i]) {
            if (j >= J && j < J + M && flow[i][j] == 1) {
                cout << "Job " << i << " → Machine " << (j - J) << "\n";
            }
        }
    }
}
