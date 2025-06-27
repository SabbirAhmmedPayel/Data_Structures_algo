#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int value;
    Node *parent;
    list<Node *> children;
    int degree;

    Node(int val)
    {
        value = val;
        parent = nullptr;
        degree = 0;
    }
};

class BinomialHeap
{
public:
    list<Node *> trees;
    Node *min_node;
    int count;

    BinomialHeap()
    {
        min_node = nullptr;
        count = 0;
    }

    bool is_empty()
    {
        return min_node == nullptr;
    }

    void insert(int value)
    {
        Node *node = new Node(value);
        BinomialHeap temp;
        temp.trees.push_back(node);
        temp.count = 1;
        unionp(temp);
    }

    int get_min()
    {
        if (min_node == nullptr)
            return INT_MIN;
        return min_node->value;
    }


     void unionp(BinomialHeap &other)
    {
        for (Node *node : other.trees)
        {
            trees.push_back(node);
        }
        count += other.count;
        combinee();
    }

    int extract_min()
    {
        if (min_node == nullptr)
            return INT_MIN;

        trees.remove(min_node);

        BinomialHeap temp;
        for (Node *child : min_node->children)
        {
            child->parent = nullptr;
            temp.trees.push_back(child);
        }
        temp.count = pow(2, min_node->degree);

        int minVal = min_node->value;
        delete min_node;

        unionp(temp);
        count--;

        return minVal;
    }

   

    void combinee()
    {
        if (trees.empty())
        {
            min_node = nullptr;
            return;
        }

        int max_degree =  static_cast<int>(log2(count)) + 2 ;

        // hash_map  degree : pointer
        vector<Node *> degree_map(max_degree, nullptr);

        // searching for duplicate same degree trees
        for (auto it = trees.begin(); it != trees.end();)
        {
            Node *current = *it;
            int d = current->degree;

            while (degree_map[d] != nullptr)// duplicate found
            {
                Node *other = degree_map[d];
                degree_map[d] = nullptr;

                for (auto jt = trees.begin(); jt != trees.end(); ++jt)
                {
                    if (*jt == other)
                    {
                        trees.erase(jt);
                        break;
                    }
                }

                if (current->value > other->value)
                    swap(current, other); // bigger one is parent 

                link(current, other); // make current parent of other 
                d = current->degree; // new increased degree
            }

            degree_map[d] = current;
            ++it;
        }

        trees.clear();
        min_node = nullptr;

        for (Node *node : degree_map)
        {
            if (node != nullptr)
            {
                trees.push_back(node);
                if (min_node == nullptr || node->value < min_node->value)
                    min_node = node;
            }
        }
    }

    void link(Node *parent, Node *child)
    {
        child->parent = parent;
        parent->children.push_back(child);
        parent->degree++;
    }

    void decrease_key(Node *node, int new_value)
    {
        if (new_value > node->value)
            return;
        node->value = new_value;
        Node *parent = node->parent;

        while (parent != nullptr && node->value < parent->value)
        {
            swap(node->value, parent->value);
            node = parent;
            parent = node->parent;
        }

        if (min_node == nullptr || node->value < min_node->value)
            min_node = node;
    }

    void delete_node(Node *node)
    {
        decrease_key(node, INT_MIN);
        extract_min();
    }

    int size()
    {
        return count;
    }

    // int get_height_tree(Node *root)
    // {  

    //     if (!root)
    //         return 0;
    //         int max = 0 ; 

    //     for (Node *child : root->children)
    //     {
    //         max =   std::max(max,get_height_tree(child)) ; 
    //     }
    //     return 1 +max ;
    // }

 

    void levelOrder(Node *root, int level, vector<vector<int>> &res)
    {
        if (!root)
            return;

        if (res.size() <= level)
        {
            res.push_back({});
        }
        res[level].push_back(root->value);
        for (Node *child : root->children)
        {
            levelOrder(child, level + 1, res);
        }
    }

    vector<vector<int>> level(Node *node)
    {
        vector<vector<int>> res;
        vector<int> restemp;


        levelOrder(node, 0, res);

        for (int i = 0; i < res.size(); i++)
        {
            cout << "level " << i << ": ";
            for (int j = 0; j < res[i].size(); j++)
            {   
                restemp.push_back(res[i][j]) ;
                reverse(restemp.begin(),restemp.end()) ;
               
                
            }
             for (int y : restemp){
                    cout << y  << " ";
                } restemp.clear() ; 
            cout << endl;
        }
        return res;
    }

    void printHeap()
    {
        cout << "Printing Binomial Heap...\n";
        int tree_index = 0;
        for (Node *tree : trees)
        {
            cout << "Binomial Tree, B" << tree->degree  << endl;
            level(tree);
            tree_index++;
        }

        cout << endl;
        
    }

    Node *findNodeInTree(Node *root, int value)
    {
        if (root->value == value)
            return root;
        for (Node *child : root->children)
        {
            Node *res = findNodeInTree(child, value);
            if (res != nullptr)
                return res;
        }
        return nullptr;
    }

    Node *findNode(int value)
    {
        for (Node *root : trees)
        {
            Node *res = findNodeInTree(root, value);
            if (res != nullptr)
                return res;
        }
        return nullptr;
    }

    void decrease(int n, int m)
    {
        if (n < m)
            return;

        Node *res = findNode(n);
        decrease_key(res, m);
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
