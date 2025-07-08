#include <iostream>
#include <string>
#include "MyHashMap.h"  // your custom HashMap template header

using namespace std;

int main() {
    string dna;
    int k;

    cout << "Enter DNA sequence: ";
    getline(cin, dna);

    cout << "Enter k: ";
    cin >> k;

    HashMap<string, int> kmerCounts;

    int n = (int)dna.size();

    for (int i = 0; i <= n - k; ++i) {
        string kmer = dna.substr(i, k);
        kmerCounts.increment(kmer);  // increment count for this k-mer
    }

    cout << "K-mer counts:\n";
    kmerCounts.printAll();

    return 0;
}
