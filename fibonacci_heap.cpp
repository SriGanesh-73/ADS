#include <iostream>
#include <cmath>
#include <vector>
#include <climits>

using namespace std;

class FibonacciHeap {
private:
    struct Node {
        int data;
        Node* parent;
        Node* child;
        Node* next;
        Node* prev;
        int degree;
        bool mark;

        Node(int value) : data(value), parent(nullptr), child(nullptr), next(nullptr), prev(nullptr), degree(0), mark(false) {}
    };

    Node* minNode;
    int nodeCount;

    void link(Node* y, Node* x) {
        y->prev->next = y->next;
        y->next->prev = y->prev;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->next = y;
            y->prev = y;
        } else {
            y->next = x->child;
            y->prev = x->child->prev;
            x->child->prev->next = y;
            x->child->prev = y;
        }
        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int maxDegree = (int)log2(nodeCount) + 1;
        vector<Node*> degreeTable(maxDegree, nullptr);
        Node* current = minNode;
        do {
            Node* x = current;
            int d = x->degree;
            while (degreeTable[d]) {
                Node* y = degreeTable[d];
                if (y->data < x->data) {
                    swap(x, y);
                }
                link(y, x);
                degreeTable[d] = nullptr;
                d++;
            }
            degreeTable[d] = x;
            current = current->next;
        } while (current != minNode);
        
        minNode = nullptr;
        for (Node* node : degreeTable) {
            if (node != nullptr) {
                if (minNode == nullptr || node->data < minNode->data) {
                    minNode = node;
                }
            }
        }
    }

    void cut(Node* x, Node* y) {
        if (x->next == x) {
            y->child = nullptr;
        } else {
            y->child = x->next;
        }
        y->degree--;
        x->next = minNode;
        x->prev = minNode->prev;
        minNode->prev->next = x;
        minNode->prev = x;
        x->parent = nullptr;
        x->mark = false;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    bool isEmpty() {
        return minNode == nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (minNode == nullptr) {
            minNode = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            minNode->prev->next = newNode;
            newNode->prev = minNode->prev;
            newNode->next = minNode;
            minNode->prev = newNode;
            if (newNode->data < minNode->data) {
                minNode = newNode;
            }
        }
        nodeCount++;
    }

    void decreaseKey(Node* x, int newKey) {
        if (newKey > x->data) {
            cout << "New key is greater than current key!" << endl;
            return;
        }
        x->data = newKey;
        Node* y = x->parent;
        if (y && x->data < y->data) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->data < minNode->data) {
            minNode = x;
        }
    }

    Node* findMin() {
        return minNode;
    }

    void extractMin() {
        Node* z = minNode;
        if (z != nullptr) {
            if (z->child != nullptr) {
                Node* child = z->child;
                do {
                    child->parent = nullptr;
                    child = child->next;
                } while (child != z->child);
            }
            z->prev->next = z->next;
            z->next->prev = z->prev;
            if (z == z->next) {
                minNode = nullptr;
            } else {
                minNode = z->next;
                consolidate();
            }
            nodeCount--;
            delete z;
        }
    }

    void merge(FibonacciHeap& other) {
        if (minNode == nullptr) {
            minNode = other.minNode;
        } else if (other.minNode != nullptr) {
            Node* temp = minNode->next;
            minNode->next = other.minNode->next;
            other.minNode->next->prev = minNode;
            other.minNode->next = temp;
            temp->prev = other.minNode;
            if (other.minNode->data < minNode->data) {
                minNode = other.minNode;
            }
        }
        nodeCount += other.nodeCount;
        other.minNode = nullptr;
        other.nodeCount = 0;
    }

    void printHeap() {
        if (minNode == nullptr) {
            cout << "Heap is empty!" << endl;
            return;
        }
        Node* current = minNode;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != minNode);
        cout << endl;
    }

    ~FibonacciHeap() {
        while (!isEmpty()) {
            extractMin();
        }
    }
};

int main() {
    FibonacciHeap heap;
    FibonacciHeap heap2;
    int choice, value;
    Node* nodePtr;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert element into heap\n";
        cout << "2. Decrease key\n";
        cout << "3. Extract minimum\n";
        cout << "4. Merge with another heap\n";
        cout << "5. Display heap\n";
        cout << "6. Find minimum\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                break;

            case 2:
                cout << "Enter node value to decrease key: ";
                cin >> value;
                nodePtr = heap.findMin();
                while (nodePtr && nodePtr->data != value) {
                    nodePtr = nodePtr->next;
                }
                if (nodePtr) {
                    int newKey;
                    cout << "Enter new key: ";
                    cin >> newKey;
                    heap.decreaseKey(nodePtr, newKey);
                } else {
                    cout << "Node not found!" << endl;
                }
                break;

            case 3:
                cout << "Extracting minimum element\n";
                heap.extractMin();
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
                heap.printHeap();
                break;

            case 6:
                cout << "Minimum element: " << heap.findMin()->data << endl;
                break;

            case 7:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
