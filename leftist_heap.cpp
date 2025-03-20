#include <iostream>
#include <algorithm>

using namespace std;

class LeftistHeap {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int NPL;

        Node(int val) : data(val), left(nullptr), right(nullptr), NPL(0) {}
    };

    Node* root;

    Node* merge(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        if (h1->data > h2->data) {
            swap(h1, h2);
        }

        h1->right = merge(h1->right, h2);

        if (!h1->left || h1->left->NPL < h1->right->NPL) {
            swap(h1->left, h1->right);
        }

        h1->NPL = (h1->right ? h1->right->NPL : -1) + 1;

        return h1;
    }

public:
    LeftistHeap() : root(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        root = merge(root, newNode);
    }

    void deleteMin() {
        if (!root) {
            cout << "Heap is empty!" << endl;
            return;
        }

        Node* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }

    int findMin() const {
        if (root) {
            return root->data;
        }
        cout << "Heap is empty!" << endl;
        return -1;
    }

    void merge(LeftistHeap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    void printHeap(Node* node) const {
        if (node) {
            printHeap(node->left);
            cout << node->data << " ";
            printHeap(node->right);
        }
    }

    void print() const {
        printHeap(root);
        cout << endl;
    }

    ~LeftistHeap() {
        while (root) {
            deleteMin();
        }
    }
};

int main() {
    LeftistHeap heap;
    int choice, value;
    LeftistHeap heap2;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert element into heap\n";
        cout << "2. Delete minimum element\n";
        cout << "3. Find minimum element\n";
        cout << "4. Merge with another heap\n";
        cout << "5. Display heap\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                break;

            case 2:
                heap.deleteMin();
                cout << "Minimum element deleted.\n";
                break;

            case 3:
                cout << "Minimum element: " << heap.findMin() << endl;
                break;

            case 4:
                cout << "Enter elements for the second heap (0 to stop):\n";
                while (true) {
                    cout << "Enter value: ";
                    cin >> value;
                    if (value == 0) break;
                    heap2.insert(value);
                }
                heap.merge(heap2);
                cout << "Heaps merged.\n";
                break;

            case 5:
                cout << "Current heap: ";
                heap.print();
                break;

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
