#include <iostream>
#include <vector>
#include <algorithm> // For std::max
using namespace std;

// Definition of a node in the tree
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
    }
};

// Class to represent the binary tree
class BinaryTree
{
public:
    Node *root;

    BinaryTree()
    {
        root = nullptr;
    }

    // Wrapper functions
    void insert(int value)
    {
        root = insert(root, value);
    }

    void inorder()
    {
        inorder(root) ; 
        cout << endl;
    }

    int numberOfNodes()
    {
        return numberOfNodes(root);
    }

    int height()
    {
        return height(root);
    }

    bool search(int value)
    {
        return search(root, value);
    }

    int findMax()
    {
        return findMax(root);
    }

    int findMin()
    {
        Node *minNode = findMin(root);
        return minNode ? minNode->data : -1;
    }

    void deleteNode(int key)
    {
        root = deleteNode(root, key);
    }

    void printTree()
    {
        printTree(root, 0, 10); // Corrected: pass root and the initial space and height
    }

    void clearTree()
    {
        clearTree(root);
        root = nullptr;
    }

    bool pathToNode(int key, std::vector<int> &path)
    {
        return pathToNode(root, key, path);
    }
    bool isBinarySearchTree() {
    return isBSTUtil(root, 0, 1000000000);
}


private:
    // Private recursive helper functions
    bool isBSTUtil(Node* root, int mindata, int maxdata) {
    // An empty tree is a dataid BST
    if (root == nullptr)
        return true;

    // Check if the current node's dataue is within the dataid range
    if (root->data <= mindata || root->data >= maxdata)
        return false;

    // Recursively check left and right subtrees with updated constraints
    return isBSTUtil(root->left, mindata, root->data) &&
           isBSTUtil(root->right, root->data, maxdata);
}

// Wrapper function to call with initial constraints

    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }
        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else
        {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void preorder(Node *root)
    {
        if (root == nullptr)
            return;

        cout << root->data << " "; 
        preorder(root->left);     
        preorder(root->right);    
    }
    void postorder(Node *root)
    {
        if (root == nullptr)
            return;

        postorder(root->left);    
        postorder(root->right);  
        cout << root->data << " ";
    }

    int numberOfNodes(Node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + numberOfNodes(node->left) + numberOfNodes(node->right);
    }

    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    bool search(Node *node, int value)
    {
        if (node == nullptr)
            return false;
        if (node->data == value)
            return true;
        if (value < node->data)
        {
            return search(node->left, value);
        }
        else
        {
            return search(node->right, value);
        }
    }

    Node *findMin(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    int findMax(Node *node)
    {
        if (node == nullptr)
            return -1;
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node->data;
    }

    Node *deleteNode(Node *node, int key)
    {
        if (node == nullptr)
            return node;

        if (key < node->data)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->data)
        {
            node->right = deleteNode(node->right, key);
        }
        else //found , now to delete ; 
        {
            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            // case when value has 2 childs
            Node *temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void printTree(Node *node, int space, int height)
    {
        if (node == nullptr)
            return;
        space += height;
        printTree(node->left, space, height);
        cout << endl;
        for (int i = height; i < space; i++)
        {
            cout << " ";
        }
        cout << node->data << "\n";
        printTree(node->right, space, height);
    }

    void clearTree(Node *node)
    {
        if (node == nullptr)
            return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    bool pathToNode(Node *node, int key, std::vector<int> &path)
    {
        if (node == nullptr)
            return false;
        path.push_back(node->data);
        if (node->data == key)
            return true;
        if (pathToNode(node->left, key, path))
            return true;
        if (pathToNode(node->right, key, path))
            return true;
        path.pop_back();
        return false;
    }
};

int main()
{
    BinaryTree tree;

    // Insert nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(100);
    tree.insert(19);
    tree.insert(50);

    // Perform in-order traversal
    cout << "In-order traversal: ";
    tree.inorder();

    // Print the tree structure
    cout << "Tree structure: \n";
    tree.printTree();

    // Get the number of nodes
    cout << "Number of nodes: " << tree.numberOfNodes() << endl;

    // Get the height of the tree
    cout << "Height of the tree: " << tree.height() << endl;

    // Search for a value
    int searchValue = 40;
    cout << "Is " << searchValue << " present? " << (tree.search(searchValue) ? "Yes" : "No") << endl;

    // Find min and max values
    cout << "Minimum value: " << tree.findMin() << endl;
    cout << "Maximum value: " << tree.findMax() << endl;

    // Path to a node
    int key = 40;
    std::vector<int> path;
    if (tree.pathToNode(key, path))
    {
        cout << "Path to node " << key << ": ";
        for (int node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Node " << key << " not found.\n";
    }

    // Clear the tree
    cout << "Clearing tree...\n";
    tree.clearTree();
    cout << "Tree cleared.\n";

    return 0;
}
