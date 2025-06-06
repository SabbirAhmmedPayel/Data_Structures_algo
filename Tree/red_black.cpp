#include <iostream>
#include <iomanip>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;
    Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* gp = z->parent->parent;
            if (z->parent == gp->left) {
                Node* y = gp->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rightRotate(gp);
                }
            } else {
                Node* y = gp->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    leftRotate(gp);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node* u, Node* v) {
        if (!u->parent) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    Node* minValueNode(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    void fixDelete(Node* x, Node* xParent) {
        while (x != root && (!x || x->color == BLACK)) {
            if (x == xParent->left) {
                Node* w = xParent->right;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    xParent->color = RED;
                    leftRotate(xParent);
                    w = xParent->right;
                }
                if ((!w->left || w->left->color == BLACK) &&
                    (!w->right || w->right->color == BLACK)) {
                    if (w) w->color = RED;
                    x = xParent;
                    xParent = x->parent;
                } else {
                    if (!w->right || w->right->color == BLACK) {
                        if (w->left) w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = xParent->right;
                    }
                    if (w) w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->right) w->right->color = BLACK;
                    leftRotate(xParent);
                    x = root;
                    break;
                }
            } else {
                Node* w = xParent->left;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    xParent->color = RED;
                    rightRotate(xParent);
                    w = xParent->left;
                }
                if ((!w->left || w->left->color == BLACK) &&
                    (!w->right || w->right->color == BLACK)) {
                    if (w) w->color = RED;
                    x = xParent;
                    xParent = x->parent;
                } else {
                    if (!w->left || w->left->color == BLACK) {
                        if (w->right) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = xParent->left;
                    }
                    if (w) w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->left) w->left->color = BLACK;
                    rightRotate(xParent);
                    x = root;
                    break;
                }
            }
        }
        if (x) x->color = BLACK;
    }

    Node* search(Node* root, int key) {
        if (!root || root->key == key)
            return root;
        if (key < root->key)
            return search(root->left, key);
        else
            return search(root->right, key);
    }

    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << (node->color == RED ? "R " : "B ");
            inorder(node->right);
        }
    }

    void visualize(Node* node, int space = 0, int height = 10) {
        if (!node) return;
        space += height;
        visualize(node->right, space);
        cout << endl << setw(space)
             << node->key << (node->color == RED ? "R" : "B") << "\n";
        visualize(node->left, space);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (key < x->key)
                x = x->left;
            else if (key > x->key)
                x = x->right;
            else
                return; // no duplicate keys
        }

        z->parent = y;
        if (!y) root = z;
        else if (key < y->key)
            y->left = z;
        else
            y->right = z;

        fixInsert(z);
    }

    void remove(int key) {
        Node* z = search(root, key);
        if (!z) return;

        Node* y = z;
        Node* x;
        Color yOriginalColor = y->color;

        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        } else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minValueNode(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z && x) x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left) y->left->parent = y;
            y->color = z->color;
        }

        delete z;
        if (yOriginalColor == BLACK)
            fixDelete(x, y->parent);
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }

    void displayTree() {
        visualize(root);
    }
};