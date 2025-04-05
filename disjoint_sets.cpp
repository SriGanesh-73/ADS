#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    DisjointSet ds(6); // 6 elements: 0 to 5

    ds.unionSets(0, 1);
    ds.unionSets(1, 2);
    ds.unionSets(3, 4);
    ds.unionSets(4, 5);

    cout << "Is 0 connected to 2? " << (ds.isConnected(0, 2) ? "Yes" : "No") << endl;
    cout << "Is 1 connected to 3? " << (ds.isConnected(1, 3) ? "Yes" : "No") << endl;
    cout << "Is 3 connected to 5? " << (ds.isConnected(3, 5) ? "Yes" : "No") << endl;

    return 0;
}
