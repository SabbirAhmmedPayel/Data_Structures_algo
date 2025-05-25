#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int value;
    bool color;
    Node *left, *right, *parent;

    Node(int value): value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node *root;

    void rotateLeft(Node *&piv) {
        Node *rchild = piv->right;

        piv->right = rchild->left;
        if (piv->right)
            piv->right->parent = piv;

        rchild->parent = piv->parent;

        if (!piv->parent)
            root = rchild;
        else if (piv == piv->parent->left)
            piv->parent->left = rchild;
        else
            piv->parent->right = rchild;

        rchild->left = piv;
        piv->parent = rchild;
    }

    void rotateRight(Node *&piv) {
        Node *leftChild = piv->left;

        piv->left = leftChild->right;
        if (piv->left)
            piv->left->parent = piv;

        leftChild->parent = piv->parent;

        if (!piv->parent)
            root = leftChild;
        else if (piv == piv->parent->left)
            piv->parent->left = leftChild;
        else
            piv->parent->right = leftChild;

        leftChild->right = piv;
        piv->parent = leftChild;
    }

    void fixViolation(Node *&newNode) {
        Node *parentNode = nullptr;
        Node *gParent = nullptr;

        while ((newNode != root) && (newNode->color == RED) && (newNode->parent->color == RED)) {
            parentNode = newNode->parent;
            gParent = parentNode->parent;

            if (parentNode == gParent->left) {
                Node *uncle = gParent->right;

                if (uncle && uncle->color == RED) {
                    gParent->color = RED;
                    parentNode->color = BLACK;
                    uncle->color = BLACK;
                    newNode = gParent;
                } else {
                    if (newNode == parentNode->right) {
                        rotateLeft(parentNode);
                        newNode = parentNode;
                        parentNode = newNode->parent;
                    }
                    rotateRight(gParent);
                    swap(parentNode->color, gParent->color);
                    newNode = parentNode;
                }
            } else {
                Node *uncle = gParent->left;

                if (uncle && uncle->color == RED) {
                    gParent->color = RED;
                    parentNode->color = BLACK;
                    uncle->color = BLACK;
                    newNode = gParent;
                } else {
                    if (newNode == parentNode->left) {
                        rotateRight(parentNode);
                        newNode = parentNode;
                        parentNode = newNode->parent;
                    }
                    rotateLeft(gParent);
                    swap(parentNode->color, gParent->color);
                    newNode = parentNode;
                }
            }
        }

        root->color = BLACK;
    }

    void inorderHelper(Node *node) {
        if (!node) return;
        inorderHelper(node->left);
        cout << node->value << (node->color ? "(R) " : "(B) ");
        inorderHelper(node->right);
    }

public:
    RBTree(): root(nullptr) {}

    void insert(int value) {
        Node *newNode = new Node(value);
        Node *parentNode = nullptr;
        Node *current = root;

        while (current != nullptr) {
            parentNode = current;
            if (newNode->value < current->value)
                current = current->left;
            else
                current = current->right;
        }

        newNode->parent = parentNode;

        if (!parentNode)
            root = newNode;
        else if (newNode->value < parentNode->value)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;

        fixViolation(newNode);
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    RBTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);

    cout << "In-order traversal of the Red-Black Tree:\n";
    tree.inorder();

    return 0;
}
