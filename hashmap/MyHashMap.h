#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <vector>
#include <list>
#include <utility>
#include <functional>
using namespace std;


unsigned long long customhash(const string &key){
    //sdbm 
     unsigned long long hash = 0;
    for (char c : key) {
        // Example: SDBM hash
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

template <typename KeyType, typename ValueType>


class HashMap {
private:
    static const int DEFAULT_CAPACITY = 10007;
    vector<list<pair<KeyType, ValueType>>> table;
    int size;

    int getIndex(const KeyType& key) const {
        return hash<KeyType>{}(key) % DEFAULT_CAPACITY;
    }

public:
    HashMap() : table(DEFAULT_CAPACITY), size(0) {}

    void put(const KeyType& key, const ValueType& value) {
        int index = getIndex(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        size++;
    }

    void increment(const KeyType& key) {
        int index = getIndex(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second++;
                return;
            }
        }
        table[index].emplace_back(key, 1);
        size++;
    }

    bool get(const KeyType& key, ValueType& result) const {
        int index = getIndex(key);
        for (const auto& entry : table[index]) {
            if (entry.first == key) {
                result = entry.second;
                return true;
            }
        }
        return false;
    }

    bool remove(const KeyType& key) {
        int index = getIndex(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                size--;
                return true;
            }
        }
        return false;
    }

    void printAll() const {
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                cout << entry.first << ": " << entry.second << endl;
            }
        }
    }

    int getSize() const {
        return size;
    }

    vector<pair<KeyType, ValueType>> getTable() const {
        vector<pair<KeyType, ValueType>> result;
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                result.push_back(entry);
            }
        }
        return result;
    }
};

#endif // MY_HASH_MAP_H
