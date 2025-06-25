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

    void unionp(BinomialHeap &other)
    {
        for (Node *node : other.trees)
        {
            trees.push_back(node);
        }
        count += other.count;
        combinee();
    }

    void combinee()
    {
        if (trees.empty())
        {
            min_node = nullptr;
            return;
        }

        int max_degree = (count > 0) ? static_cast<int>(log2(count)) + 2 : 2;
        vector<Node *> degree_map(max_degree, nullptr);

        for (auto it = trees.begin(); it != trees.end();)
        {
            Node *current = *it;
            int d = current->degree;

            while (degree_map[d] != nullptr)
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
                    swap(current, other);

                link(current, other);
                d = current->degree;
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

    int get_height_tree(Node *root)
    {  

        if (!root)
            return 0;
            int max = 0 ; 

        for (Node *child : root->children)
        {
            max =   std::max(max,get_height_tree(child)) ; 
        }
        return 1 +max ;
    }

 

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

    vector<vector<int>> level(Node *node, ofstream &out)
    {
        vector<vector<int>> res;
        vector<int> restemp;


        levelOrder(node, 0, res);

        for (int i = 0; i < res.size(); i++)
        {
            out << "level " << i << ": ";
            for (int j = 0; j < res[i].size(); j++)
            {   
                restemp.push_back(res[i][j]) ;
                reverse(restemp.begin(),restemp.end()) ;
               
                
            }
             for (int y : restemp){
                    out << y  << " ";
                } restemp.clear() ; 
            out << endl;
        }
        return res;
    }

    void printHeap(ofstream &out)
    {
        out << "Printing Binomial Heap...\n";
        int tree_index = 0;
        for (Node *tree : trees)
        {
            out << "Binomial Tree, B" << (get_height_tree(tree)-1)   << endl;
            level(tree, out);
            tree_index++;
        }

        out << endl;
        
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

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string line;
    BinomialHeap bh;

    while (getline(in, line))
    {
        vector<string> tokens;
        stringstream ss(line);
        string word;
        while (ss >> word)
        {
            tokens.push_back(word);
        }

        if (tokens.empty())
            continue;

        char command = tokens[0][0];

        int num1 = 0, num2 = 0;
        if (tokens.size() > 1)
            num1 = stoi(tokens[1]);
        if (tokens.size() > 2)
            num2 = stoi(tokens[2]);

        if (command == 'I')
        {
            bh.insert(num1);
        }
        else if (command == 'F')
        {
            out << "Find Min returned: " << bh.get_min() << endl;
        }
        else if (command == 'E')
        {
            int val = bh.extract_min();
            out << "Extracte Min returned : " << val << endl;
        }
        else if (command == 'P')
        {
            bh.printHeap(out);
        }
        else if (command == 'D')
        {
            bh.decrease(num1, num2);
        }
        else if (command == 'R')
        {
            bh.delete_node(bh.findNode(num1));
        }
    }

    return 0;
}
