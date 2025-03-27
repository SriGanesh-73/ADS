#include <iostream>
#include <algorithm>

using namespace std;

class AVLTreeNode {
public:
    int data;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
public:
    AVLTreeNode* root;

    AVLTree() {
        root = nullptr;
    }

    int height(AVLTreeNode* node) {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(AVLTreeNode* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    AVLTreeNode* rightRotate(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLTreeNode* leftRotate(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLTreeNode* insert(AVLTreeNode* node, int key) {
        if (node == nullptr) return new AVLTreeNode(key);

        if (key < node->data) node->left = insert(node->left, key);
        else if (key > node->data) node->right = insert(node->right, key);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->data) return rightRotate(node);
        if (balance < -1 && key > node->right->data) return leftRotate(node);
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLTreeNode* minNode(AVLTreeNode* node) {
        AVLTreeNode* current = node;
        while (current->left != nullptr) current = current->left;
        return current;
    }

    AVLTreeNode* deleteNode(AVLTreeNode* root, int key) {
        if (root == nullptr) return root;

        if (key < root->data) root->left = deleteNode(root->left, key);
        else if (key > root->data) root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLTreeNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else *root = *temp;
                delete temp;
            } else {
                AVLTreeNode* temp = minNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    bool search(AVLTreeNode* root, int key) {
        if (root == nullptr) return false;
        if (key == root->data) return true;
        if (key < root->data) return search(root->left, key);
        return search(root->right, key);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    void inorder(AVLTreeNode* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void print() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    int choice, value;

    while (true) {
        cout << "\nAVL Tree Operations Menu: \n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display In-order Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                cout << (tree.search(value) ? "Found\n" : "Not found\n");
                break;
            case 4:
                cout << "In-order traversal: ";
                tree.print();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

