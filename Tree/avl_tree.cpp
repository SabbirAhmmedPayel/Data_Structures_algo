#include <iostream>
#include <iomanip>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insert(Node* node, int key) {
    if (!node)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

void visualizeTree(Node* root, int space = 0, int height = 10) {
    if (!root) return;

    space += height;

    visualizeTree(root->right, space);
    cout << endl;
    cout << setw(space) << root->key << "\n";
    visualizeTree(root->left, space);
}

int main() {
    Node* root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int key : keys)
        root = insert(root, key);

    cout << "In-order traversal of the AVL Tree:\n";
    inorder(root);
    cout << "\n\nVisual representation of AVL Tree:\n";
    visualizeTree(root);

    return 0;
}
