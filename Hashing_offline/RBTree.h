#include <iostream>
#include <string>

using namespace std;

struct pairdata
{
    string text;
    int index;
};

enum Color
{
    RED,
    BLACK
};

struct RBNode
{
    string key;
    int val;
    Color color;
    RBNode *left, *right, *parent;

    RBNode(pairdata p)
        : key(p.text), val(p.index), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree
{
private:
    RBNode *root;
    RBNode *NIL;

    void fixDelete(RBNode *x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                RBNode *w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                RBNode *w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    void leftRotate(RBNode *x)
    {
        RBNode *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode *y)
    {
        RBNode *x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;
        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    void fixInsert(RBNode *z)
    {
        while (z->parent != nullptr && z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBNode *y = z->parent->parent->right;
                if (y->color == RED)
                {
                    // Case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        // Case 2
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                RBNode *y = z->parent->parent->left;
                if (y->color == RED)
                {
                    // Case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        // Case 2
                        z = z->parent;
                        rightRotate(z);
                    }
                    // Case 3
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(RBNode *u, RBNode *v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    RBNode *minimum(RBNode *node)
    {
        while (node->left != NIL)
        {
            node = node->left;
        }
        return node;
    }

    RBNode *searchNode(const string &key) const
    {
        RBNode *current = root;
        while (current != NIL)
        {
            if (key == current->key)
                return current;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }

public:


    RBTree()
    {
        NIL = new RBNode({"", 0});
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = nullptr;
        root = NIL;
    }
void remove(const string &key) {
        RBNode *z = searchNode(key);
        if (z == nullptr) return; 

        RBNode *y = z;
        RBNode *x;
        Color yOriginalColor = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }
    void insert(pairdata p)
    {
        RBNode *z = new RBNode(p);
        z->left = z->right = z->parent = NIL;

        RBNode *y = nullptr;
        RBNode *x = root;

        while (x != NIL)
        {
            y = x;
            if (z->key == x->key)
            {
               
                delete z;
                return;
            }
            else if (z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        z->left = NIL;
        z->right = NIL;
        z->color = RED;

        fixInsert(z);
    }

   
    int getVal(const string &key) const
    {
        RBNode *node = searchNode(key);
        if (node == nullptr)
            return -1;
        return node->val;
    }

    void inorderHelper(RBNode *node) const
    {
        if (node != NIL)
        {
            inorderHelper(node->left);
            cout << node->key << " : " << node->val << endl;
            inorderHelper(node->right);
        }
    }

    void inorder() const
    {
        inorderHelper(root);
    }

    bool isEmpty() const {
    return root == NIL;
}

~RBTree() {
    destroyTree(root);
    delete NIL;
}

void destroyTree(RBNode* node) {
    if (node != NIL) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }


}} ;
