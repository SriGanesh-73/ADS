#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

template<typename T>
class Node {
public:
    T value;
    Node** forward;
    Node(int level, T value) {
        forward = new Node*[level+1];
        memset(forward, 0, sizeof(Node*)*(level+1));
        this->value = value;
    }
    ~Node() {
        delete [] forward;
    }
};

template<typename T>
class SkipList {
private:
    int MAXLVL;
    float P;
    int level;
    Node<T>* header;
public:
    SkipList(int maxlvl, float probability) : MAXLVL(maxlvl), P(probability) {
        level = 0;
        header = new Node<T>(MAXLVL, T());
    }

    int randomLevel() {
        float r = (float)rand() / RAND_MAX;
        int lvl = 0;
        while (r < P && lvl < MAXLVL) {
            lvl++;
            r = (float)rand() / RAND_MAX;
        }
        return lvl;
    }

    void insert(T value) {
        Node<T>* current = header;
        Node<T>* update[MAXLVL+1];
        memset(update, 0, sizeof(Node<T>*) * (MAXLVL + 1));

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != NULL && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == NULL || current->value != value) {
            int rlevel = randomLevel();
            if (rlevel > level) {
                for (int i = level + 1; i <= rlevel; i++) {
                    update[i] = header;
                }
                level = rlevel;
            }

            Node<T>* newNode = new Node<T>(rlevel, value);
            for (int i = 0; i <= rlevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
            cout << "Successfully inserted key " << value << endl;
        }
    }

    void deleteNode(T value) {
        Node<T>* current = header;
        Node<T>* update[MAXLVL+1];
        memset(update, 0, sizeof(Node<T>*) * (MAXLVL + 1));

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != NULL && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != NULL && current->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }

            while (level > 0 && header->forward[level] == NULL) {
                level--;
            }

            delete current;
            cout << "Successfully deleted key " << value << endl;
        } else {
            cout << "Key " << value << " not found!" << endl;
        }
    }

    bool search(T value) {
        Node<T>* current = header;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != NULL && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];

        if (current != NULL && current->value == value) {
            cout << "Found key " << value << endl;
            return true;
        } else {
            cout << "Key " << value << " not found!" << endl;
            return false;
        }
    }

    void displayList() {
        cout << "\n*****Skip List*****" << "\n";
        for (int i = 0; i <= level; i++) {
            Node<T> *node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != NULL) {
                cout << node->value << " ";
                node = node->forward[i];
            }
            cout << "\n";
        }
    }

    ~SkipList() {
        delete header;
    }
};

int main() {
    srand((unsigned)time(0));
    int choice, value;
    SkipList<int> list(3, 0.5);

    do {
        cout << "\nMenu:";
        cout << "\n1. Insert Element";
        cout << "\n2. Delete Element";
        cout << "\n3. Search Element";
        cout << "\n4. Display List";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                list.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                list.search(value);
                break;
            case 4:
                list.displayList();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while(choice != 5);

    return 0;
}
