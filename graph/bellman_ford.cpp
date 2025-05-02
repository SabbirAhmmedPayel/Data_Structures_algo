#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

struct Edge {
    int source, destination, weight;
};

void bellmanFord(vector<Edge>& graph, int vertices, int source) {
    vector<int> distance(vertices, INT_MAX);
    distance[source] = 0;

    for (int i = 0; i < vertices - 1; ++i) {
        for (const Edge& e : graph) {
            if (distance[e.source] != INT_MAX && distance[e.source] + e.weight < distance[e.destination]) {
                distance[e.destination] = distance[e.source] + e.weight;
            }
        }
    }

    for (const Edge& e : graph) {
        if (distance[e.source] != INT_MAX && distance[e.source] + e.weight < distance[e.destination]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    cout << "Vertex   Distance from Source\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << "\t\t" << distance[i] << "\n";
    }
}

int main() {
    int vertices = 6;
    vector<Edge> graph = {
        { 0, 1, 5 }, { 0, 2, 7 }, { 1, 2, 3 },
        { 1, 3, 4 }, { 1, 4, 6 }, { 3, 4, -1 },
        { 3, 5, 2 }, { 4, 5, -3 }
    };

    bellmanFord(graph, vertices, 0);

    return 0;
}
