#include <cstdlib>
#include <iostream>

using namespace std;

class SplayTree {
private:
    struct Node {
        int key;
        Node* parent;
        Node* left;
        Node* right;
    };

    Node* root;
    int size;

    Node* createNode(int key, Node* parent = NULL) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->parent = parent;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void splay(Node* x) {
        while (x->parent) {
            Node* parent = x->parent;
            Node* grandparent = parent->parent;
            if (!grandparent) {
                if (x == parent->left)
                    rotateRight(parent);
                else
                    rotateLeft(parent);
            } else {
                if (parent == grandparent->left) {
                    if (x == parent->left) {
                        rotateRight(grandparent);
                        rotateRight(parent);
                    } else {
                        rotateLeft(parent);
                        rotateRight(grandparent);
                    }
                } else {
                    if (x == parent->right) {
                        rotateLeft(grandparent);
                        rotateLeft(parent);
                    } else {
                        rotateRight(parent);
                        rotateLeft(grandparent);
                    }
                }
            }
        }
    }

    Node* findMin(Node* node) {
        if (!node)
            return NULL;
        while (node->left)
            node = node->left;
        return node;
    }

    Node* findMax(Node* node) {
        if (!node)
            return NULL;
        while (node->right)
            node = node->right;
        return node;
    }

public:
    SplayTree() {
        root = NULL;
        size = 0;
    }

    bool add(int key) {
        return insert(key);
    }

    bool get(int key) {
        return search(key);
    }

    bool remove(int key) {
        return removeNode(key);
    }

    bool swap(int key1, int key2) {
        Node* node1 = getNode(root, key1);
        Node* node2 = getNode(root, key2);

        if (!node1 || !node2)
            return false; // One or both keys not found

        // Swap the keys
        int temp = node1->key;
        node1->key = node2->key;
        node2->key = temp;

        return true;
    }

    bool insert(int key) {
        if (!root) {
            root = createNode(key);
            size++;
            return true;
        }

        Node* current = root;
        Node* parent = NULL;
        while (current) {
            parent = current;
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return false; // Key already exists
        }

        Node* newNode = createNode(key, parent);
        if (key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;
        size++;
        splay(newNode);
        return true;
    }

    bool removeNode(int key) {
        Node* nodeToRemove = getNode(root, key);
        if (!nodeToRemove)
            return false; // Key not found

        splay(nodeToRemove);

        Node* leftSubtree = nodeToRemove->left;
        Node* rightSubtree = nodeToRemove->right;

        if (!leftSubtree)
            root = rightSubtree;
        else {
            root = leftSubtree;
            Node* maxNode = findMax(leftSubtree);
            splay(maxNode);
            maxNode->right = rightSubtree;
            if (rightSubtree)
                rightSubtree->parent = maxNode;
        }

        delete nodeToRemove;
        size--;
        return true;
    }

    Node* getNode(Node* node, int key) {
        while (node) {
            if (key < node->key)
                node = node->left;
            else if (key > node->key)
                node = node->right;
            else
                return node;
        }
        return NULL; // Key not found
    }

    bool search(int key) {
        Node* current = root;
        while (current) {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else {
                splay(current);
                return true;
            }
        }
        return false;
    }

    void print() {
        cout << "Size: " << size << endl;
        print(root, "", "");
    }

    void print(Node* node, string indent, string childIndicator) {
        if (node) {
            cout << indent << "|-- " << childIndicator << node->key << endl;
            print(node->left, indent + "    ", "L: ");
            print(node->right, indent + "    ", "R: ");
        }
    }
};
