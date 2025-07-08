#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "hashstorage_tree.h"
#include "HashOpenadd.h"

using namespace std;
using namespace std::chrono;

int hashmode = 1;      // 1 = SDBM, 2 = Polynomial Rolling
int probingMode = 1;   // 1 = Linear Probing, 2 = Double Hashing

vector<string> getdata(const string& filename) {
    vector<string> result;
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return result;
    }
    string line;
    while (getline(infile, line)) {
        if (!line.empty())
            result.push_back(line);
    }
    infile.close();
    return result;
}

int main() {
    int numberofdata = 10000;
    int searchcount = 1000;
    double load_factor = 0.9;

    hashmode = 2;     // 1 = SDBM, 2 = Polynomial Rolling
    probingMode = 2;  // 1 = Linear, 2 = Double Hashing

    vector<string> alldata = getdata("alldata.txt");
    vector<string> preSearch = getdata("searchdata.txt");

    int tablesize = static_cast<int>(numberofdata / load_factor);
    OpenHashtable openTable(tablesize);
    HashTable chainTable(tablesize);

    for (const string& key : alldata) {
        openTable.insert(key);
        chainTable.insert(key);
    }

    cout << "Load Factor: " << load_factor << endl;

    if (hashmode == 1)
        cout << "Hash mode: SDBM" << endl;
    else if (hashmode == 2)
        cout << "Hash mode: POLYNOMIAL ROLLING" << endl;

    // === CHAINING BEFORE DELETION ===
    cout << "Collisions (Chaining): " << chainTable.getCollisionCount() << endl;
    auto start1 = high_resolution_clock::now();
    for (const string& key : preSearch)
        chainTable.search(key);
    auto end1 = high_resolution_clock::now();

    cout << "Before Deletion:\n";
    cout << "  Avg search time: (chaining) "
         << duration_cast<nanoseconds>(end1 - start1).count() / searchcount << " ns" << endl;

    // === OPEN ADDRESSING BEFORE DELETION ===
    if (probingMode == 1)
        cout << "Probing mode: LINEAR" << endl;
    else if (probingMode == 2)
        cout << "Probing mode: DOUBLE HASHING" << endl;

    cout << "Collisions: " << openTable.getCollisionCount() << endl;

    openTable.resetStats();
    auto start2 = high_resolution_clock::now();
    for (const string& key : preSearch)
        openTable.search(key);
    auto end2 = high_resolution_clock::now();

    cout << "Before Deletion:\n";
    cout << "  Avg search time: (open addressing) "
         << duration_cast<nanoseconds>(end2 - start2).count() / searchcount << " ns" << endl;
    cout << "  Avg probes: "
         << (double)openTable.getTotalProbes() / searchcount << endl;

    // === DELETION ===
    int deleteCount = numberofdata * 0.1;
    vector<string> toDelete;
    vector<string> stillExists;
    vector<string> afterSearch;

   
    random_device rd;
    mt19937 gen(rd());
    shuffle(alldata.begin(), alldata.end(), gen);

   
    for (int i = 0; i < numberofdata; ++i) {
        if (i < deleteCount)
            toDelete.push_back(alldata[i]);
        else
            stillExists.push_back(alldata[i]);
    }

    for (const string& key : toDelete) {
        openTable.remove(key);
        chainTable.remove(key);
    }


    for (int i = 0; i < searchcount / 2; ++i)
        afterSearch.push_back(toDelete[i % toDelete.size()]);
    for (int i = 0; i < searchcount / 2; ++i)
        afterSearch.push_back(stillExists[i % stillExists.size()]);

    // CHAINING AFTER DELETION
    auto start3 = high_resolution_clock::now();
    for (const string& key : afterSearch)
        chainTable.search(key);
    auto end3 = high_resolution_clock::now();

    cout << "After Deletion:\n";
    cout << "  Avg search time: (chaining) "
         << duration_cast<nanoseconds>(end3 - start3).count() / searchcount << " ns" << endl;

    // OPEN ADDRESSING AFTER DELETION
    openTable.resetStats();
    auto start4 = high_resolution_clock::now();
    for (const string& key : afterSearch)
        openTable.search(key);
    auto end4 = high_resolution_clock::now();

    cout << "After Deletion:\n";
    cout << "  Avg search time: (open addressing) "
         << duration_cast<nanoseconds>(end4 - start4).count() / searchcount << " ns" << endl;
    cout << "  Avg probes: "
         << (double)openTable.getTotalProbes() / searchcount << endl;

    return 0;
}
