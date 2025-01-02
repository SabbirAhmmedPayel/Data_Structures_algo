#include <iostream>
#include <stdexcept>

class Stack {
private:
    int* arr;        // Dynamic array to store stack elements
    int capacity;    // Maximum number of elements stack can hold
    int top;         // Index of the top element in the stack

public:
    // Constructor to initialize the stack
    Stack(int size = 10) {
        capacity = size;
        arr = new int[capacity]; // Allocate memory for stack
        top = -1; // Stack is initially empty
    }

    // Destructor to free allocated memory
    ~Stack() {
        delete[] arr;
    }

    // Function to add an item to stack
    void push(int item) {
        if (top == capacity - 1) { // Check if stack is full
            // Resize the array if necessary
            resize();
        }
        arr[++top] = item; // Increment top and add item
    }

    // Function to remove and return the top item from the stack
    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack Underflow: Attempt to pop from an empty stack.");
        }
        return arr[top--]; // Return top item and decrement top
    }

    // Function to return the top item without removing it
    int peek() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty: No top element.");
        }
        return arr[top]; // Return top item
    }

    // Function to check if the stack is empty
    bool isEmpty() const {
        return top == -1; // Stack is empty if top is -1
    }

    // Function to return the current size of the stack
    int size() const {
        return top + 1; // Size is top index + 1
    }

private:
    // Function to resize the stack when full
    void resize() {
        capacity *= 2; // Double the capacity
        int* newArr = new int[capacity]; // Allocate new array
        for (int i = 0; i <= top; i++) {
            newArr[i] = arr[i]; // Copy old elements to new array
        }
        delete[] arr; // Free old array memory
        arr = newArr; // Update the stack array to new array
    }
};

// Example usage
int main() {
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Top element is: " << stack.peek() << std::endl; // Should print 3
    std::cout << "Stack size is: " << stack.size() << std::endl; // Should print 3

    std::cout << "Popped element is: " << stack.pop() << std::endl; // Should print 3
    std::cout << "Stack size is: " << stack.size() << std::endl; // Should print 2

    return 0;
}
