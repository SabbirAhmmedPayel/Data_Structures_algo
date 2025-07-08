#include <iostream>
#include <string>
#include "MyHashMap.h"  // your custom hashmap header

using namespace std;

// Citizen structure
struct Citizen {
    string name;
    string nid;
    string phone;
};

// Print citizen info helper
void printCitizen(const Citizen& c) {
    cout << "Match Found:\n";
    cout << "Name: " << c.name << endl;
    cout << "NID no: " << c.nid << endl;
    cout << "Phone no: " << c.phone << endl;
}

int main() {
    // HashMaps for name, nid and phone as keys
    HashMap<string, Citizen> nameMap;
    HashMap<string, Citizen> nidMap;
    HashMap<string, Citizen> phoneMap;

    while (true) {
        cout << "\nEnter choice: 1. Enter Data, 2. Search Index, 0. Exit\n";
        int choice;
        cin >> choice;
        cin.ignore(); // consume newline

        if (choice == 0)
            break;

        if (choice == 1) {
            Citizen c;
            cout << "Enter name: ";
            getline(cin, c.name);
            cout << "Enter NID no: ";
            getline(cin, c.nid);
            cout << "Enter phone no: ";
            getline(cin, c.phone);

            nameMap.put(c.name, c);
            nidMap.put(c.nid, c);
            phoneMap.put(c.phone, c);

        } else if (choice == 2) {
            string query;
            cout << "Enter search string: ";
            getline(cin, query);

            Citizen found;
            if (nameMap.get(query, found)) {
                printCitizen(found);
            } else if (nidMap.get(query, found)) {
                printCitizen(found);
            } else if (phoneMap.get(query, found)) {
                printCitizen(found);
            } else {
                cout << "No match found\n";
            }
        } else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
