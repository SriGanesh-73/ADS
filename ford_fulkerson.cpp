#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

#define INF INT_MAX

// Function to perform BFS and find if there's a path from source to sink
bool bfs(int n, vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    
    // Standard BFS loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < n; v++) {
            // If v is not visited and there's residual capacity
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
                
                // If we reach the sink, no need to explore further
                if (v == sink) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

// Ford-Fulkerson algorithm to find maximum flow in a given graph
int fordFulkerson(int n, vector<vector<int>>& graph, int source, int sink) {
    vector<vector<int>> residualGraph = graph; // Residual graph
    vector<int> parent(n);
    int maxFlow = 0;
    
    // Augment the flow while there is a path from source to sink
    while (bfs(n, residualGraph, source, sink, parent)) {
        // Find the maximum flow through the path found by BFS
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }
        
        // Update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }
        
        maxFlow += pathFlow;
    }
    
    return maxFlow;
}

int main() {
    int n = 6; // Number of vertices
    vector<vector<int>> graph(n, vector<int>(n, 0));
    
    // Example graph:
    // Source (0) -> 1, 2
    // 1 -> Sink (5)
    // 2 -> 3, 4
    // 3 -> Sink (5)
    // 4 -> Sink (5)
    
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    int source = 0, sink = 5;
    int maxFlow = fordFulkerson(n, graph, source, sink);
    
    cout << "The maximum possible flow is " << maxFlow << endl;

    return 0;
}
