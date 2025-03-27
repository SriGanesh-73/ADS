#include <iostream>
#include <cstdlib> // For rand()

class TreapNode {
public:
int key, priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int key) : key(key), priority(rand()), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    TreapNode* root;

    TreapNode* rotateRight(TreapNode* y) {
        TreapNode* x = y->left;
        TreapNode* T = x->right;

        x->right = y;
        y->left = T;

        return x;
    }

    TreapNode* rotateLeft(TreapNode* x) {
        TreapNode* y = x->right;
        TreapNode* T = y->left;

        y->left = x;
        x->right = T;

        return y;
    }

    TreapNode* insert(TreapNode* node, int key) {
        if (!node) return new TreapNode(key);

        if (key <= node->key) {
            node->left = insert(node->left, key);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        } else {
            node->right = insert(node->right, key);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        }

        return node;
    }

    TreapNode* deleteNode(TreapNode* node, int key) {
        if (!node) return node;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (!node->left) {
                TreapNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreapNode* temp = node->left;
                delete node;
                return temp;
            }

            if (node->left->priority < node->right->priority) {
                node = rotateLeft(node);
                node->left = deleteNode(node->left, key);
            } else {
                node = rotateRight(node);
                node->right = deleteNode(node->right, key);
            }
        }

        return node;
    }

    void inorderTraversal(TreapNode* node) {
        if (!node) return;

        inorderTraversal(node->left);
        std::cout << node->key << " ";
        inorderTraversal(node->right);
    }

public:
    Treap() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void inorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    Treap treap;
    int choice, key;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Display (Inorder Traversal)\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter key to insert: ";
                std::cin >> key;
                treap.insert(key);
                break;
            case 2:
                std::cout << "Enter key to delete: ";
                std::cin >> key;
                treap.deleteNode(key);
                break;
            case 3:
                std::cout << "Treap (Inorder Traversal): ";
                treap.inorder();
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}


