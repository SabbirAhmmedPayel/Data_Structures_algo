#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int key;
    string color; // "r", "b", "db"
    Node *left, *right, *parent;

    Node(int k) : key(k), color("r"), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node* root = nullptr;

    Node* grandparent(Node* n) {
        return n && n->parent ? n->parent->parent : nullptr;
    }

    Node* sibling(Node* n) {
        if (!n || !n->parent) return nullptr;
        return n == n->parent->left ? n->parent->right : n->parent->left;
    }

    Node* uncle(Node* n) {
        Node* g = grandparent(n);
        if (!g) return nullptr;
        if (n->parent == g->left) return g->right;
        else return g->left;
    }

    Node* minValueNode(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

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

  void insertFixup(Node* node) {
    Node* p = node->parent;

    if (!p) {
        node->color = "b";
        return;
    }

    if (p->color == "b") return;

    Node* g = grandparent(node);
    if (!g) return;

    Node* u = uncle(node);

    if (u && u->color == "r") {
        // Case 1: Uncle is red
        p->color = u->color = "b";
        
        g->color = "r";
        insertFixup(g);
    } else {
        // Uncle is black or null
        if (p == g->left) {
            if (node == p->right) {
                // Left-Right
                leftRotate(p);
                node = p;
                p = node->parent;
            }
            // Left-Left
            p->color = "b";
            g->color = "r";
            rightRotate(g);
        } else {
            if (node == p->left) {
                // Right-Left
                rightRotate(p);
                node = p;
                p = node->parent;
            }
            // Right-Right
            p->color = "b";
            g->color = "r";
            leftRotate(g);
        }
    }
}

    void fixDoubleBlack(Node* node) {
        if (!node || node == root) {
            if (node && node->color == "db") node->color = "b";
            return;
        }

        Node* siblingNode = sibling(node);
        Node* parent = node->parent;

        if (!siblingNode) {
            fixDoubleBlack(parent);
        } else if (siblingNode->color == "r") {
            parent->color = "r";
            siblingNode->color = "b";
            if (siblingNode == parent->left) rightRotate(parent);
            else leftRotate(parent);
            fixDoubleBlack(node);
        } else {
            bool redChild = (siblingNode->left && siblingNode->left->color == "r") ||
                            (siblingNode->right && siblingNode->right->color == "r");
            if (redChild) {
                if (siblingNode->left && siblingNode->left->color == "r") {
                    if (siblingNode == parent->left) {
                        siblingNode->left->color = siblingNode->color;
                        siblingNode->color = parent->color;
                        rightRotate(parent);
                    } else {
                        siblingNode->left->color = parent->color;
                        rightRotate(siblingNode);
                        leftRotate(parent);
                    }
                } else {
                    if (siblingNode == parent->left) {
                        siblingNode->right->color = parent->color;
                        leftRotate(siblingNode);
                        rightRotate(parent);
                    } else {
                        siblingNode->right->color = siblingNode->color;
                        siblingNode->color = parent->color;
                        leftRotate(parent);
                    }
                }
                parent->color = "b";
                if (node->color == "db") node->color = "b";
            } else {
                siblingNode->color = "r";
                if (parent->color == "b") {
                    parent->color = "db";
                    if (node->color != "db") node->color = "b";
                    fixDoubleBlack(parent);
                } else {
                    parent->color = "b";
                    if (node->color == "db") node->color = "b";
                }
            }
        }
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;

                if (!child) {
                    // No child case
                    if (node->color == "b") {
                        node->color = "db";
                        fixDoubleBlack(node);
                    }
                    if (node == root) root = nullptr;
                    delete node;
                    return nullptr;
                }

                // One child case
                if (node == root) {
                    child->parent = nullptr;
                    root = child;
                    child->color = "b";
                    delete node;
                    return child;
                }

                child->parent = node->parent;
                if (node == node->parent->left) node->parent->left = child;
                else node->parent->right = child;

                if (node->color == "b" && child->color == "b") {
                    child->color = "db";
                    fixDoubleBlack(child);
                } else {
                    child->color = "b";
                }

                delete node;
                return child;
            }

            Node* succ = minValueNode(node->right);
            node->key = succ->key;
            node->right = deleteNode(node->right, succ->key);
        }
        return node;
    }

public:
    void insert(int key) {
        Node* newNode = new Node(key);
        if (!root) {
            root = newNode;
            root->color = "b";
            return;
        }

        Node* temp = root;
        Node* parent = nullptr;

        while (temp) {
            parent = temp;
            if (key < temp->key) temp = temp->left;
            else temp = temp->right;
        }

        newNode->parent = parent;
        if (key < parent->key) parent->left = newNode;
        else parent->right = newNode;

        insertFixup(newNode);
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << "(" << node->color << ") ";
        inorder(node->right);
    }

    void printInorder() {
        inorder(root);
        cout << "\n";
    }
};

int main() {
    RBTree tree;

    // Insert keys
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);

    cout << "Inorder after insertion: ";
    tree.printInorder();

    // Delete some keys
    tree.deleteKey(20);
    cout << "Inorder after deleting 20: ";
    tree.printInorder();

    tree.deleteKey(10);
    cout << "Inorder after deleting 10: ";
    tree.printInorder();

    return 0;
}
