#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

// Get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Get the balance factor of a node
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Update the height of a node
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Right rotate subtree rooted with y
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    // Return new root
    return y;
}

// Insert a key into the AVL tree
Node* insert(Node* node, int key) {
    // Standard BST insertion
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    // Update height
    updateHeight(node);

    // Get balance factor
    int balance = getBalance(node);

    // Balance the tree

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// In-order traversal
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Driver program
int main() {
    Node* root = nullptr;

    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int key : keys)
        root = insert(root, key);

    cout << "In-order traversal of the AVL Tree:\n";
    inorder(root);
    cout << endl;

    return 0;
}