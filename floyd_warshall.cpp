#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void FloydWarshall(int V, vector<vector<int>>& graph) {
    // Initialize distance matrix with graph values
    vector<vector<int>> dist = graph;

    // Step 1: Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Update the distance between i and j
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Step 2: Check for negative weight cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
        }
    }

    // Step 3: Print the shortest distance matrix
    cout << "Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                cout << "INF" << " ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int V = 4;
    vector<vector<int>> graph = {
        {0, 3, INT_MAX, INT_MAX},
        {2, 0, INT_MAX, 1},
        {INT_MAX, 7, 0, 4},
        {INT_MAX, INT_MAX, 2, 0}
    };

    FloydWarshall(V, graph);

    return 0;
}
