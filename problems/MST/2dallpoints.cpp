#include <bits/stdc++.h>
using namespace std;

int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    vector<bool> visited(n, false);
    vector<int> minDist(n, INT_MAX);
    minDist[0] = 0;

    using pii = pair<int, int>; // {cost, node}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});

    int result = 0;
    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        result += cost;

        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                int newCost = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                if (newCost < minDist[v]) {
                    minDist[v] = newCost;
                    pq.push({newCost, v});
                }
            }
        }
    }

    return result;
}

int main() {
    vector<vector<int>> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << "Minimum cost to connect all points: " << minCostConnectPoints(points) << "\n";
    return 0;
}
