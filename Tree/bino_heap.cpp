#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Node {
public:
    int key, degree;
    Node *parent, *child, *sibling;
    Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
    vector<Node*> roots;

    Node* mergeTrees(Node* a, Node* b) {
        if (a->key > b->key) swap(a, b);
        b->parent = a;
        b->sibling = a->child;
        a->child = b;
        a->degree++;
        return a;
    }

    vector<Node*> unionHeaps(vector<Node*> &h1, vector<Node*> &h2) {
        vector<Node*> res;
        int i = 0, j = 0;
        while (i < (int)h1.size() && j < (int)h2.size()) {
            if (h1[i]->degree < h2[j]->degree) res.push_back(h1[i++]);
            else res.push_back(h2[j++]);
        }
        while (i < (int)h1.size()) res.push_back(h1[i++]);
        while (j < (int)h2.size()) res.push_back(h2[j++]);
        return res;
    }

    vector<Node*> adjust(vector<Node*> &heap) {
        if (heap.size() <= 1) return heap;
        vector<Node*> res;
        int i = 0;
        while (i < (int)heap.size()) {
            if (i + 1 < (int)heap.size() && heap[i]->degree == heap[i + 1]->degree) {
                if (i + 2 < (int)heap.size() && heap[i + 1]->degree == heap[i + 2]->degree) {
                    res.push_back(heap[i++]);
                } else {
                    heap[i + 1] = mergeTrees(heap[i], heap[i + 1]);
                    i++;
                }
            } else {
                res.push_back(heap[i++]);
            }
        }
        return res;
    }

public:
    void insert(int key) {
        Node* node = new Node(key);
        vector<Node*> temp = {node};
        roots = unionHeaps(roots, temp);
        roots = adjust(roots);
    }

    int extractMin() {
        if (roots.empty()) return INT_MIN;
        int minIndex = 0;
        for (int i = 1; i < (int)roots.size(); ++i)
            if (roots[i]->key < roots[minIndex]->key)
                minIndex = i;

        Node* minNode = roots[minIndex];
        roots.erase(roots.begin() + minIndex);

        vector<Node*> childHeap;
        Node* cur = minNode->child;
        while (cur) {
            Node* next = cur->sibling;
            cur->sibling = nullptr;
            cur->parent = nullptr;
            childHeap.insert(childHeap.begin(), cur);
            cur = next;
        }
        roots = unionHeaps(roots, childHeap);
        roots = adjust(roots);

        int minKey = minNode->key;
        delete minNode;
        return minKey;
    }
};

int main() {
    BinomialHeap bh;
    bh.insert(10);
    bh.insert(2);
    bh.insert(7);
    bh.insert(1);

    cout << "Min: " << bh.extractMin() << "\n";
    cout << "Min: " << bh.extractMin() << "\n";
}
