#include <iostream>
#include <list>
#include <cmath>
#include <climits>
#include<vector>
#include <algorithm>

using namespace std;

class Node {
public:
    int value;
    Node* parent;
    list<Node*> children;
    int degree;

    Node(int val) {
        value = val;
        parent = nullptr;
        degree = 0;
    }
};

class BinomialHeap {
public:
    list<Node*> trees;
    Node* min_node;
    int count;

    BinomialHeap() {
        min_node = nullptr;
        count = 0;
    }

    bool is_empty() {
        return min_node == nullptr;
    }

    void insert(int value) {
        Node* node = new Node(value);
        BinomialHeap temp;
        temp.trees.push_back(node);
        temp.count = 1;
        merge(temp);
    }

    int get_min() {
        if (min_node == nullptr) return INT_MIN;
        return min_node->value;
    }

    int extract_min() {
        if (min_node == nullptr) return INT_MIN;

        trees.remove(min_node);

        BinomialHeap temp;
        for (Node* child : min_node->children) {
            child->parent = nullptr;
            temp.trees.push_back(child);
        }
        temp.count = pow(2, min_node->degree);

        int minVal = min_node->value;
        delete min_node;

        merge(temp);
        count--;

        return minVal;
    }

    void merge(BinomialHeap& other) {
        for (Node* node : other.trees) {
            trees.push_back(node);
        }
        count += other.count;
        consolidate();
    }

    void consolidate() {
        if (trees.empty()) {
            min_node = nullptr;
            return;
        }

        int max_degree = (count > 0) ? static_cast<int>(log2(count)) + 2 : 2;
        vector<Node*> degree_map(max_degree, nullptr);

        for (auto it = trees.begin(); it != trees.end();) {
            Node* current = *it;
            int d = current->degree;

            while (degree_map[d] != nullptr) {
                Node* other = degree_map[d];
                degree_map[d] = nullptr;

                auto remove_it = find(trees.begin(), trees.end(), other);
                if (remove_it != trees.end()) trees.erase(remove_it);

                if (current->value > other->value)
                    swap(current, other);

                link(current, other);
                d = current->degree;
            }

            degree_map[d] = current;
            ++it;
        }

        trees.clear();
        min_node = nullptr;

        for (Node* node : degree_map) {
            if (node != nullptr) {
                trees.push_back(node);
                if (min_node == nullptr || node->value < min_node->value)
                    min_node = node;
            }
        }
    }

    void link(Node* parent, Node* child) {
        child->parent = parent;
        parent->children.push_back(child);
        parent->degree++;
    }

    void decrease_key(Node* node, int new_value) {
        if (new_value > node->value) return;
        node->value = new_value;
        Node* parent = node->parent;

        while (parent != nullptr && node->value < parent->value) {
            swap(node->value, parent->value);
            node = parent;
            parent = node->parent;
        }

        if (min_node == nullptr || node->value < min_node->value)
            min_node = node;
    }

    void delete_node(Node* node) {
        decrease_key(node, INT_MIN);
        extract_min();
    }

    int size() {
        return count;
    }

    void print_tree(Node* node, int depth) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << node->value << "\n";
        for (Node* child : node->children) {
            print_tree(child, depth + 1);
        }
    }

    void printHeap() {
        cout << "Heap Trees:\n";
        for (Node* tree : trees) {
            print_tree(tree, 0);
            cout << "------\n";
        }
    }

   
};

int main() {
    BinomialHeap heap;

    heap.insert(10);
    heap.insert(3);
    heap.insert(7);
    heap.insert(6);
    heap.insert(15);
    heap.insert(1);

    cout << "Initial Heap:\n";
    heap.printHeap();

    cout << "Extracted min: " << heap.extract_min() << "\n";
    cout << "Heap after extract_min:\n";
    heap.printHeap();

    cout << "Insert 2 and 8\n";
    heap.insert(2);
    heap.insert(8);
    heap.printHeap();

    return 0;
}
