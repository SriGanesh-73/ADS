#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfsRecursive(int node, vector<bool>& visited, const vector<vector<int>>& graph) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsRecursive(neighbor, visited, graph);
        }
    }
}

void dfsIterative(const vector<vector<int>>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    stack<int> s;
    s.push(startNode);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            for (auto it = graph[node].rbegin(); it != graph[node].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},     // Node 0
        {0, 3, 4},   // Node 1
        {0, 5},      // Node 2
        {1},         // Node 3
        {1, 5},      // Node 4
        {2, 4}       // Node 5
    };

    cout << "Recursive DFS: ";
    vector<bool> visited(graph.size(), false);
    dfsRecursive(0, visited, graph);
    cout << endl;

    cout << "Iterative DFS: ";
    dfsIterative(graph, 0);
    cout << endl;

    return 0;
}
