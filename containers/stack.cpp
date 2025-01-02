#include <iostream>
using namespace std;

// Node structure for the singly linked list
struct Node {
    int data;
    Node* next;

    // Constructor
    Node(int val) : data(val), next(nullptr) {}
};

// Stack class using a singly linked list
class Stack {
private:
    Node* top;  // Pointer to the top of the stack
    int count;  // Count to keep track of the number of elements

public:
    // Constructor
    Stack() : top(nullptr), count(0) {}

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Function to get the size of the stack
    int size() {
        return count;
    }

    // Function to push an element onto the stack
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    // Function to pop the top element from the stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow! No elements to pop." << endl;
            return -1; // Return an invalid value when stack is empty
        }

        Node* temp = top;
        int poppedValue = top->data;
        top = top->next;
        delete temp;
        count--;
        return poppedValue;
    }

    // Function to get the top element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;  // Return an invalid value when stack is empty
        }
        return top->data;
    }

    // Function to print all elements in the stack
    void printStack() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }

        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Destructor to clear all memory when the stack is destroyed
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};
int main() {
    Stack stack;

    // Push elements into the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);

    // Print the stack
    cout << "Stack contents: ";
    stack.printStack();

    // Check the top element using peek
    cout << "Top element (peek): " << stack.peek() << endl;

    // Pop an element from the stack
    cout << "Popped element: " << stack.pop() << endl;

    // Print the stack after popping
    cout << "Stack contents after pop: ";
    stack.printStack();

    // Check the size of the stack
    cout << "Current size of the stack: " << stack.size() << endl;

    // Check if the stack is empty
    if (stack.isEmpty()) {
        cout << "The stack is empty!" << endl;
    } else {
        cout << "The stack is not empty!" << endl;
    }

    return 0;
}
