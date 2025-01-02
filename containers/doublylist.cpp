#include <iostream>
using namespace std;

// Node structure for the doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List class
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor to initialize head and tail
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Function to check if the list is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Function to insert a node at the front
    void insertAtFront(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Function to insert a node at the end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Function to insert a node before a given value
    void insertBeforeValue(int val, int beforeVal) {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr && temp->data != beforeVal) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value " << beforeVal << " not found in the list!" << endl;
            return;
        }

        Node* newNode = new Node(val);
        newNode->next = temp;
        newNode->prev = temp->prev;

        if (temp->prev != nullptr) {
            temp->prev->next = newNode;
        } else {
            head = newNode;  // If inserting before the first node
        }
        temp->prev = newNode;
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
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next != nullptr) {
            temp->next->prev = newNode;
        } else {
            tail = newNode;  // If inserting at the end
        }
        temp->next = newNode;
    }

    // Function to reverse the doubly linked list
    void reverseList() {
        Node* temp = nullptr;
        Node* current = head;

        // Swap next and prev for all nodes
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        // Before changing the head, check for the non-empty list
        if (temp != nullptr) {
            head = temp->prev;
        }
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

    // Function to print the list from head to tail
    void printList() {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Function to delete a node by value
    void deleteNodeByValue(int val) {
        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;

        // If the node to be deleted is the head node
        if (head->data == val) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;  // If the list becomes empty
            }
            delete temp;
            return;
        }

        while (temp != nullptr && temp->data != val) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value " << val << " not found in the list!" << endl;
            return;
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;  // If the last node is to be deleted
        }

        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        }

        delete temp;
    }

    // Function to delete a node by position
    void deleteNodeByPosition(int position) {
        if (position <= 0) {
            cout << "Invalid position!" << endl;
            return;
        }

        if (isEmpty()) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;

        // If the head node needs to be deleted
        if (position == 1) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;  // If the list becomes empty
            }
            delete temp;
            return;
        }

        int currentPosition = 1;
        while (temp != nullptr && currentPosition < position) {
            temp = temp->next;
            currentPosition++;
        }

        if (temp == nullptr) {
            cout << "Position out of range!" << endl;
            return;
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;  // If the last node is to be deleted
        }

        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        }

        delete temp;
    }
};
int main() {
    DoublyLinkedList list;

    // Insert nodes
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtFront(40);
    list.insertAtFront(50);

    // Print the list
    cout << "List: ";
    list.printList();

    // Insert before a given value
    list.insertBeforeValue(25, 30);
    cout << "List after inserting 25 before 30: ";
    list.printList();

    // Insert at nth position
    list.insertAtNthPosition(5, 2);
    cout << "List after inserting 5 at position 2: ";
    list.printList();

    // Reverse the list
    list.reverseList();
    cout << "List after reversal: ";
    list.printList();

    // Delete node by value
    list.deleteNodeByValue(25);
    cout << "List after deleting node with value 25: ";
    list.printList();

    // Delete node by position
    list.deleteNodeByPosition(3);
    cout << "List after deleting node at position 3: ";
    list.printList();

    return 0;
}
