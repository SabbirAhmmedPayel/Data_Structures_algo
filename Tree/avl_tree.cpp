#include <iostream>
#include <iomanip>
using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    Node *root;

    int getHeight(Node *node)
    {
        return node ? node->height : 0;
    }

    int getBalance(Node *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node *node)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node *fixTree(Node *node)
    {
        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *insert(Node *node, int key)
    {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        return fixTree(node);
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *node, int key)
    {
        if (!node)
            return node;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;
                if (!temp)
                { 
                      // Case: No children (leaf node)
                    temp = node;
                    node = nullptr;
                }
                else
                { //  Case: One child
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                Node *temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (!node)
            return node;

        return fixTree(node);
    }

    void inorder(Node *node)
    {
        if (node)
        {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    void visualize(Node *node, int space = 0, int height = 10)
    {
        if (!node)
            return;
        space += height;
        visualize(node->right, space);
        cout << endl
             << setw(space) << node->key << "\n";
        visualize(node->left, space);
    }
    bool search(Node *node, int key)
    {
        if (!node)
            return false;
        if (key == node->key)
            return true;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    int countNodes(Node *node)
    {
        if (!node)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int getTreeHeight(Node *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key)
    {
        root = insert(root, key);
    }

    void remove(int key)
    {
        root = deleteNode(root, key);
    }

    void displayInorder()
    {
        inorder(root);
        cout << endl;
    }

    void displayTree()
    {
        visualize(root);
    }
    bool search(int key)
    {
        return search(root, key);
    }

    int countNodes()
    {
        return countNodes(root);
    }

    int getTreeHeight()
    {
        return getTreeHeight(root);
    }
};

int main()
{
    AVLTree tree;

    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int key : keys)
        tree.insert(key);

    cout << "In-order traversal of AVL Tree:\n";
    tree.displayInorder();

    cout << "\nVisual representation of AVL Tree:\n";
    tree.displayTree();

    cout << "\n\nDeleting node 40...\n";
    tree.remove(40);

    cout << "\nIn-order after deletion:\n";
    tree.displayInorder();

    cout << "\nVisual representation after deletion:\n";
    tree.displayTree();

    return 0;
}
