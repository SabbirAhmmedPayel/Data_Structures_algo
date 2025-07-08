#include <iostream>
#include <vector>
#include <list>
#include <functional> // for std::hash
#include <utility>    // for std::pair

using namespace std;

template <typename KeyType, typename ValueType>
class HashMap {
private:
    static const int DEFAULT_CAPACITY = 10007; // A prime number
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
};


#include <string>

int main() {
    HashMap<string, int> map;
    map.increment("ATC");
    map.increment("ATC");
    map.increment("GGA");

    map.put("TAA", 10);
    map.put("ATC",44) ; 

    int val;
    if (map.get("ATC", val)) {
        cout << "ATC count: " << val << endl;
    }

    map.printAll();

    // HashMap<pair<string, string>, int> pairMap;

    // pairMap.put({"A", "B"}, 1);
    // pairMap.increment({"A", "B"});
    // pairMap.increment({"A", "C"});

    // pairMap.printAll();


    return 0;
}
