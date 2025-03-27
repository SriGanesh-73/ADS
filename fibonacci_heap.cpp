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
        
        if (minNode == nullptr) return;
        
        vector<Node*> roots;
        Node* current = minNode;
        do {
            roots.push_back(current);
            current = current->next;
        } while (current != minNode);
        
        for (Node* node : roots) {
            Node* x = node;
            int d = x->degree;
            
            while (degreeTable[d] != nullptr) {
                Node* y = degreeTable[d];
                if (y->data < x->data) {
                    swap(x, y);
                }
                link(y, x);
                degreeTable[d] = nullptr;
                d++;
            }
            degreeTable[d] = x;
        }
        
        minNode = nullptr;
        for (Node* node : degreeTable) {
            if (node != nullptr) {
                if (minNode == nullptr) {
                    minNode = node;
                    node->next = node;
                    node->prev = node;
                } else {
                    node->prev = minNode->prev;
                    node->next = minNode;
                    minNode->prev->next = node;
                    minNode->prev = node;
                    
                    if (node->data < minNode->data) {
                        minNode = node;
                    }
                }
            }
        }
    }

    void cut(Node* x, Node* y) {
        if (x->next == x) {
            y->child = nullptr;
        } else {
            y->child = x->next;
            x->next->prev = x->prev;
            x->prev->next = x->next;
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
                Node* tempChild;
                do {
                    tempChild = child->next;
                    child->parent = nullptr;
                    
                    child->prev = minNode->prev;
                    child->next = minNode;
                    minNode->prev->next = child;
                    minNode->prev = child;
                    
                    child = tempChild;
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
        if (other.minNode == nullptr) {
            return;  // Nothing to merge
        }
        if (minNode == nullptr) {
            minNode = other.minNode;
            nodeCount = other.nodeCount;
            other.minNode = nullptr;
            other.nodeCount = 0;
            return;
        }

        Node* thisLast = minNode->prev;
        Node* otherLast = other.minNode->prev;
        
        minNode->prev = otherLast;
        otherLast->next = minNode;
        
        thisLast->next = other.minNode;
        other.minNode->prev = thisLast;

        if (other.minNode->data < minNode->data) {
            minNode = other.minNode;
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
    bool running = true;
    
    cout << "\n=== Fibonacci Heap Implementation ===\n";
    
    while (running) {
        cout << "\nMenu Options:" << endl;
        cout << "1. Insert a value into primary heap" << endl;
        cout << "2. Insert a value into secondary heap" << endl;
        cout << "3. Extract minimum from primary heap" << endl;
        cout << "4. Merge secondary heap into primary heap" << endl;
        cout << "5. Display primary heap" << endl;
        cout << "6. Display secondary heap" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert into primary heap: ";
                cin >> value;
                heap.insert(value);
                cout << "Value " << value << " inserted into primary heap." << endl;
                break;
                
            case 2:
                cout << "Enter value to insert into secondary heap: ";
                cin >> value;
                heap2.insert(value);
                cout << "Value " << value << " inserted into secondary heap." << endl;
                break;
                
            case 3:
                if (heap.isEmpty()) {
                    cout << "Primary heap is empty!" << endl;
                } else {
                    cout << "Minimum value in primary heap: " << heap.findMin()->data << endl;
                    heap.extractMin();
                    cout << "Minimum value extracted." << endl;
                }
                break;
                
            case 4:
                if (heap2.isEmpty()) {
                    cout << "Secondary heap is empty! Nothing to merge." << endl;
                } else {
                    heap.merge(heap2);
                    cout << "Secondary heap merged into primary heap." << endl;
                }
                break;
                
            case 5:
                cout << "Primary heap contents: ";
                heap.printHeap();
                break;
                
            case 6:
                cout << "Secondary heap contents: ";
                heap2.printHeap();
                break;
                
            case 7:
                cout << "Exiting program..." << endl;
                running = false;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
    
    return 0;
}
