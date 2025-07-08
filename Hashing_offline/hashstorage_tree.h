#include <iostream>
#include <vector>
#include <string>
#include "RBTree.h"

using namespace std;

extern int hashmode ;

//sdbm
inline int hash1(const string &str)
{
    unsigned long hash = 0;
    for (char c : str)
        hash = c + (hash << 6) + (hash << 16) - hash;
    return (int)hash;
}

// polynomialRollingHash
inline int hash2(const string &s)
{
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s)
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return (int)hash_value;
}
int gethash(const string &key, int bucketcount)
{
    int hash;
    if (hashmode == 1)
        hash = hash1(key);
    else
        hash = hash2(key);
    return ((unsigned int)hash) % bucketcount;
}

inline bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

class HashTable
{
    vector<RBTree*> trees;
    int size;
    int bucketcount;
    int datacount;
    int collisionCount;

public:
    HashTable();
    HashTable(int sizes);
    ~HashTable();

    void insert(const string &key);
    void remove(const string &key);
    int search(const string &key);
    void clear();
    bool isEmpty() const;
    void printall() const;
    int getCollisionCount() const;
};

HashTable::HashTable() : size(0), datacount(0), bucketcount(8), collisionCount(0)
{
    trees.resize(bucketcount);
    for (int i = 0; i < bucketcount; ++i)
        trees[i] = new RBTree();
}

HashTable::HashTable(int sizes) : size(sizes), datacount(0), collisionCount(0)
{
    int n = size;
    while (!isPrime(n))
        n++;
    bucketcount = n;

    trees.resize(bucketcount);
    for (int i = 0; i < bucketcount; ++i)
        trees[i] = new RBTree();
}

HashTable::~HashTable()
{
    for (auto tree : trees)
        delete tree;
}

void HashTable::insert(const string &key)
{
    int h = gethash(key, bucketcount);
    if (trees[h]->getVal(key) != -1)
    return;

    pairdata d1;
    d1.text = key;
    d1.index = ++datacount;

    if (!trees[h]->isEmpty()) 
        collisionCount++;

    trees[h]->insert(d1);
}

void HashTable::remove(const string &key)
{
    int h = gethash(key, bucketcount);
    trees[h]->remove(key);
}

int HashTable::search(const string &key)
{
    int h = gethash(key, bucketcount);
    return trees[h]->getVal(key);
}

void HashTable::clear()
{
    for (auto tree : trees)
       // tree->clear();
        ;
    datacount = 0;
    collisionCount = 0;
}

bool HashTable::isEmpty() const
{
    return datacount == 0;
}

void HashTable::printall() const
{
    for (int i = 0; i < bucketcount; ++i)
    {
        cout << "Bucket " << i << ":\n";
        trees[i]->inorder();
        cout << endl;
    }
}

int HashTable::getCollisionCount() const
{
    return collisionCount;
}
