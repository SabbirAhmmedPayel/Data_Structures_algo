#include <iostream>
#include <vector>
#include <string>

using namespace std;


 
extern int hashmode; // sdbm=1 , poly =2 
extern int probingMode; // LINEAR = 1, , DOUBLEHASH = 2

int hash1(const string &str);
int hash2(const string &s);
bool isPrime(int num);

int getHash(const string &key, int bucketCount)
{
    int h = (hashmode == 1) ? hash1(key) : hash2(key);
    return ((unsigned int)h) % bucketCount;
}

int getDoubleHash(const string &key, int bucketCount)
{
    int h = hash2(key);
    return 1 + (((unsigned int)h) % (bucketCount - 1));
}


int nextPrime(int n)
{
    while (!isPrime(n))
        n++;
    return n;
}

struct Entry
{
    string key;
    int index;
    bool isDeleted;

    Entry(const string &k, int i) : key(k), index(i), isDeleted(false) {}
};

class OpenHashtable
{
    vector<Entry *> table;
    int bucketCount;
    int dataCount;

    // Statistics
    int collisionCount = 0;
     long totalSearchProbes = 0;
    

    int probeIndex(int h1, int h2, int i) const
    {
        if (probingMode == 1)
            return (h1 + i * 5) % bucketCount;
       
        else if (probingMode == 2)
            return (h1 + i * h2) % bucketCount;


        return 0 ;     
    }

public:
    OpenHashtable(int size = 8)
        : dataCount(0)
    {
        bucketCount = nextPrime(size);
        table.resize(bucketCount, nullptr);
    }

    ~OpenHashtable()
    {
        for (auto e : table)
            delete e;
    }

    void insert(const string &key)
    {
        if (search(key) != -1)
            return;

        int h1 = getHash(key, bucketCount);
        int h2 = 0;
        if (probingMode == 2)
            h2 = getDoubleHash(key, bucketCount);

        int index;

        for (int i = 0; i < bucketCount; ++i)
        {
            index = probeIndex(h1, h2, i);
               
            if (!table[index] || table[index]->isDeleted)
            {
                table[index] = new Entry(key, ++dataCount);
                return;
            }
            else
            {
                collisionCount++; 
            }
        }

        cout << "Hash table full, couldn't insert: " << key << endl;
    }

    int search(const string &key)
    {
        int h1 = getHash(key, bucketCount);
        int h2 = 0;
        if (probingMode == 2)
            h2 = getDoubleHash(key, bucketCount);

        int index;

        for (int i = 0; i < bucketCount; ++i)
        {
            index = probeIndex(h1, h2, i);
            totalSearchProbes++; 
            

            if (!table[index])
                return -1;
            if (!table[index]->isDeleted && table[index]->key == key)
                return table[index]->index;
        }
        return -1;
    }

    void remove(const string &key)
    {
        int h1 = getHash(key, bucketCount);

        int h2 = 0;
        if (probingMode == 2)
            h2 = getDoubleHash(key, bucketCount);

        int index;
        for (int i = 0; i < bucketCount; ++i)
        {
            index = probeIndex(h1, h2, i);
         
            if (!table[index])
                return;
            if (!table[index]->isDeleted && table[index]->key == key)
            {
                table[index]->isDeleted = true;
                return;
            }
        }
    }

    void printAll() const
    {
        for (int i = 0; i < bucketCount; ++i)
        {
            cout << "Bucket " << i << ": ";
            if (table[i] && !table[i]->isDeleted)
                cout << table[i]->key << " (Index: " << table[i]->index << ")";
            else
                cout << "Empty";
            cout << endl;
        }
    }

    void clear()
    {
        for (int i = 0; i < bucketCount; ++i)
        {
            delete table[i];
            table[i] = nullptr;
        }
        dataCount = 0;
        resetStats();
    }

    bool isEmpty() const
    {
        return dataCount == 0;
    }

    int getCollisionCount() const { return collisionCount; }

    void resetStats()
    {
        collisionCount = 0;
        totalSearchProbes = 0;
        
    }

    long long getTotalProbes() const {
    return totalSearchProbes;
}

};
