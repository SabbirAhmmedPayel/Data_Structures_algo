#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree {
private:
    Node* root = nullptr;

    void rightRotate(Node* x) {
        Node* y = x->left;
        if (!y) return;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        if (!y) return;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void splay(Node* x) {
        while (x->parent) {
            if (!x->parent->parent) {
                if (x == x->parent->left)
                    rightRotate(x->parent);
                else
                    leftRotate(x->parent);
            } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
                leftRotate(x->parent);
                rightRotate(x->parent);
            } else {
                rightRotate(x->parent);
                leftRotate(x->parent);
            }
        }
    }

    Node* subtreeInsert(Node* root, int key) {
        Node* z = root;
        Node* p = nullptr;
        while (z) {
            p = z;
            if (key < z->key)
                z = z->left;
            else
                z = z->right;
        }
        Node* node = new Node(key);
        node->parent = p;
        if (!p)
            return node;
        else if (key < p->key)
            p->left = node;
        else
            p->right = node;
        return node;
    }

    Node* search(Node* root, int key) {
        Node* z = root;
        while (z) {
            if (key == z->key)
                return z;
            else if (key < z->key)
                z = z->left;
            else
                z = z->right;
        }
        return nullptr;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    void insert(int key) {
        Node* node = subtreeInsert(root, key);
        splay(node);
    }

    void find(int key) {
        Node* node = search(root, key);
        if (node)
            splay(node);
    }

    void printInorder() {
        inorder(root);
        cout << "\n";
    }
};

int main() {
    SplayTree t;
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(15);

    cout << "Inorder before find: ";
    t.printInorder();

    t.find(5);

    cout << "Inorder after splaying 5: ";
    t.printInorder();
    return 0;
}
