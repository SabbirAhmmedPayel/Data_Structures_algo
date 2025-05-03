#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
};

void bellmanFord(vector<Edge>& graph, int vertices, int source) {
    vector<int> dis(vertices, INT_MAX);
    dis[source] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        for (const Edge& e : graph) {
            if (dis[e.u] != INT_MAX && dis[e.u] + e.w < dis[e.v]) {
                dis[e.v] = dis[e.u] + e.w;
            }
        }
    }

    for (const Edge& e : graph) {
        if (dis[e.u] != INT_MAX && dis[e.u] + e.w < dis[e.v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    cout << "Vertex   Distance from Source\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << "\t\t" << dis[i] << "\n";
    }
}

int main() {
    int vertices = 6;
    vector<Edge> graph = {
        {0, 1, 5}, {0, 2, 7}, {1, 2, 3},
        {1, 3, 4}, {1, 4, 6}, {3, 4, -1},
        {3, 5, 2}, {4, 5, -3}
    };

    bellmanFord(graph, vertices, 0);
    return 0;
}