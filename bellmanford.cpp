#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
};

void BellmanFord(int V, int E, vector<Edge>& edges, int src) {
    // Step 1: Initialize distances from the source
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Step 2: Relax all edges (V-1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;

            // Relax the edge if a shorter path is found
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
        }
    }

    // Step 4: Print the distance array
    cout << "Vertex   Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            cout << i << "        INF" << endl;
        else
            cout << i << "        " << dist[i] << endl;
    }
}

int main() {
    int V = 5, E = 8;
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    int source = 0;
    BellmanFord(V, E, edges, source);

    return 0;
}
