#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Node {
    int key, degree;
    bool mark;
    Node *parent, *child, *left, *right;
    Node(int k) : key(k), degree(0), mark(false), parent(nullptr), child(nullptr) {
        left = right = this;
    }
};

class FibonacciHeap {
    Node* minNode = nullptr;
    int n = 0;

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        y->left = y->right = y;
        if (!x->child) x->child = y;
        else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }
        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int D = (int)log2(n) + 1;
        vector<Node*> A(D, nullptr);
        vector<Node*> roots;
        Node* w = minNode;
        if (w) {
            do {
                roots.push_back(w);
                w = w->right;
            } while (w != minNode);
        }
        for (Node* x : roots) {
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        minNode = nullptr;
        for (Node* x : A) {
            if (x) {
                if (!minNode) minNode = x;
                else {
                    x->left->right = x->right;
                    x->right->left = x->left;
                    x->left = minNode->left;
                    x->right = minNode;
                    minNode->left->right = x;
                    minNode->left = x;
                    if (x->key < minNode->key) minNode = x;
                }
            }
        }
    }

public:
    void insert(int key) {
        Node* node = new Node(key);
        if (!minNode) minNode = node;
        else {
            node->right = minNode;
            node->left = minNode->left;
            minNode->left->right = node;
            minNode->left = node;
            if (key < minNode->key) minNode = node;
        }
        n++;
    }

    int extractMin() {
        Node* z = minNode;
        if (z) {
            if (z->child) {
                Node* c = z->child;
                do {
                    Node* next = c->right;
                    c->left->right = c->right;
                    c->right->left = c->left;
                    c->left = minNode->left;
                    c->right = minNode;
                    minNode->left->right = c;
                    minNode->left = c;
                    c->parent = nullptr;
                    c = next;
                } while (c != z->child);
            }
            z->left->right = z->right;
            z->right->left = z->left;
            if (z == z->right) minNode = nullptr;
            else {
                minNode = z->right;
                consolidate();
            }
            n--;
            return z->key;
        }
        return INT_MIN;
    }
};

int main() {
    FibonacciHeap fh;
    fh.insert(10);
    fh.insert(3);
    fh.insert(7);
    fh.insert(1);
    cout << "Min: " << fh.extractMin() << "\n";
    cout << "Min: " << fh.extractMin() << "\n";
}
