#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Singly Linked List class
class SinglyLinkedList {
private:
    Node* head;
public:
    // Constructor to initialize head
    SinglyLinkedList() : head(nullptr) {}

    // Function to check if the list is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Function to insert a node at the front
    void insertAtFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // Function to insert a node at the end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    
    void deleteNodeByValue(int val) {
    if (isEmpty()) {
        cout << "List is empty!" << endl;
        return;
    }

    // If the head is the node to be deleted
    if (head->data == val) {
        Node* temp = head;
        head = head->next; // Move head to the next node
        delete temp;       // Free the memory of the deleted node
        return;
    }

    // Traverse the list to find the node with the given value
    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != val) {
        temp = temp->next;
    }

    // If the value was not found
    if (temp->next == nullptr) {
        cout << "Value " << val << " not found in the list!" << endl;
        return;
    }

    // Delete the node
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next; // Bypass the node to be deleted
    delete nodeToDelete;           // Free memory
}
    void deleteNodeByPosition(int position) {
    if (position <= 0) {
        cout << "Invalid position!" << endl;
        return;
    }

    if (isEmpty()) {
        cout << "List is empty!" << endl;
        return;
    }

    // If the head needs to be removed
    if (position == 1) {
        Node* temp = head;
        head = head->next; // Move head to the next node
        delete temp;       // Free the memory of the deleted node
        return;
    }

    // Traverse the list to find the node at the specified position
    Node* temp = head;
    int currentPosition = 1;
    while (temp != nullptr && currentPosition < position - 1) {
        temp = temp->next;
        currentPosition++;
    }

    // If position is out of range
    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position out of range!" << endl;
        return;
    }

    // Delete the node
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next; // Bypass the node to be deleted
    delete nodeToDelete;           // Free memory
}


    // Function to insert a node before a given value
    void insertBeforeValue(int val, int beforeVal) {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->data == beforeVal) {
            insertAtFront(val);
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != beforeVal) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Value " << beforeVal << " not found in the list!" << endl;
        } else {
            Node* newNode = new Node(val);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Function to insert a node at the nth position
    void insertAtNthPosition(int val, int position) {
        if (position <= 0) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (position == 1) {
            insertAtFront(val);
            return;
        }

        Node* newNode = new Node(val);
        Node* temp = head;
        int currentPosition = 1;

        while (temp != nullptr && currentPosition < position - 1) {
            temp = temp->next;
            currentPosition++;
        }

        if (temp == nullptr) {
            cout << "Position out of range!" << endl;
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Function to reverse the linked list
    void reverseList() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;  // store next
            curr->next = prev;  // reverse the current node's pointer
            prev = curr;        // move pointers one position ahead
            curr = next;
        }
        head = prev;
    }

    // Function to count the number of nodes
    int numberOfNodes() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Function to print the list
    void printList() {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    SinglyLinkedList list;

    // Insert nodes at the front
    list.insertAtFront(10);
    list.insertAtFront(20);
    list.insertAtFront(30);

    // Insert nodes at the end
    list.insertAtEnd(40);
    list.insertAtEnd(50);

    // Print list
    cout << "List: ";
    list.printList();

    // Insert before a given value
    list.insertBeforeValue(25, 40);

    cout << "List after inserting 25 before 40: ";
    list.printList();

    // Insert at nth position
    list.insertAtNthPosition(5, 3);
    cout << "List after inserting 5 at position 3: ";
    list.printList();

    // Reverse the list
    list.reverseList();
    cout << "List after reversal: ";
    list.printList();

    // Print number of nodes
    cout << "Number of nodes in the list: " << list.numberOfNodes() << endl;

    // Check if the list is empty
    cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
