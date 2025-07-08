#include <iostream>
#include <string>
#include <vector>
#include "MyHashMap.h" // your custom HashMap

using namespace std;

// Get complementary base
char complement(char base) {
    switch (base) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
    }
    return 'N'; // Should not happen for valid input
}

// Compute reverse complement of a DNA sequence
string reverseComplement(const string& seq) {
    string rc(seq.size(), 'N');
    int n = (int)seq.size();
    for (int i = 0; i < n; ++i) {
        rc[n - i - 1] = complement(seq[i]);
    }
    return rc;
}

int main() {
    int n, l;
    cin >> n >> l;
    vector<string> sequences(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> sequences[i];
    }

    HashMap<string, int> seqIndex; // Map sequence -> index
    for (int i = 0; i < n; ++i) {
        seqIndex.put(sequences[i], i);
    }

    vector<bool> printed(n, false);

    for (int i = 0; i < n; ++i) {
        string rc = reverseComplement(sequences[i]);
        int j;
        if (seqIndex.get(rc, j)) {
            // Print pair only if i < j to avoid duplicates
            if (i < j && !printed[i] && !printed[j]) {
                cout << sequences[i] << " " << sequences[j] << "\n";
                printed[i] = true;
                printed[j] = true;
            }
        }
    }

    return 0;
}
