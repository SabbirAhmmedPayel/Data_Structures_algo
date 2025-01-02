#include <iostream>
#include <stdexcept>

// Node structure for the linked list
struct Node {
    int data;        // Data stored in the node
    Node* next;     // Pointer to the next node

    Node(int value) : data(value), next(nullptr) {} // Node constructor
};

// Queue class using a singly linked list
class Queue {
private:
    Node* front;     // Pointer to the front of the queue
    Node* tail;      // Pointer to the tail of the queue

public:
    // Constructor to initialize the queue
    Queue() : front(nullptr), tail(nullptr) {}

    // Destructor to free allocated memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue(); // Dequeue all elements
        }
    }

    // Function to add an item to the end of the queue
    void enqueue(int item) {
        Node* newNode = new Node(item); // Create a new node
        if (tail) { // If the queue is not empty
            tail->next = newNode; // Link the new node to the end of the queue
        }
        tail = newNode; // Update the tail pointer
        if (!front) { // If the queue was empty
            front = newNode; // Set the front pointer to the new node
        }
    }

    // Function to remove and return the front item from the queue
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue Underflow: Attempt to dequeue from an empty queue.");
        }
        Node* temp = front; // Store the front node
        int value = front->data; // Get the value to return
        front = front->next; // Move the front pointer to the next node
        if (!front) { // If the queue is now empty
            tail = nullptr; // Reset tail pointer
        }
        delete temp; // Free the memory of the dequeued node
        return value; // Return the dequeued value
    }

    // Function to return the front item without removing it
    int peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty: No front element.");
        }
        return front->data; // Return the front value
    }

    // Function to check if the queue is empty
    bool isEmpty() const {
        return front == nullptr; // Queue is empty if front is nullptr
    }
};

// Example usage
int main() {
    Queue queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Front element is: " << queue.peek() << std::endl; // Should print 1
    std::cout << "Dequeued element is: " << queue.dequeue() << std::endl; // Should print 1
    std::cout << "Front element after dequeue is: " << queue.peek() << std::endl; // Should print 2
    std::cout << "Dequeued element is: " << queue.dequeue() << std::endl; // Should print 2

    return 0;
}
