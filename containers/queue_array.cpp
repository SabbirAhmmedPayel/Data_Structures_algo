#include <iostream>
using namespace std;

class CircularQueue {
private:
    int* arr;       // Array to store queue elements
    int front;      // Index to the front element
    int rear;       // Index to the rear element
    int maxSize;    // Maximum capacity of the queue
    int count;      // Number of elements currently in the queue

public:
    // Constructor to initialize the queue
    CircularQueue(int size) {
        arr = new int[size];
        maxSize = size;
        front = 0;
        rear = -1;
        count = 0;
    }

    // Destructor to free the dynamically allocated memory
    ~CircularQueue() {
        delete[] arr;
    }

    // Function to check if the queue is full
    bool isFull() {
        return count == maxSize;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return count == 0;
    }

    // Function to get the size of the queue
    int size() {
        return count;
    }

    // Function to add an element to the rear of the queue (enqueue)
    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue overflow! Cannot enqueue " << val << "." << endl;
            return;
        }

        // Move rear to the next position in a circular manner
        rear = (rear + 1) % maxSize;
        arr[rear] = val;
        count++;
    }

    // Function to remove and return the front element from the queue (dequeue)
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue underflow! No elements to dequeue." << endl;
            return -1; // Return an invalid value when the queue is empty
        }

        int removedValue = arr[front];
        front = (front + 1) % maxSize; // Move front to the next position in a circular manner
        count--;
        return removedValue;
    }

    // Function to get the front element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;  // Return an invalid value when the queue is empty
        }
        return arr[front];
    }

    // Function to print the queue
    void printQueue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }

        int i = front;
        for (int elements = 0; elements < count; elements++) {
            cout << arr[i] << " ";
            i = (i + 1) % maxSize;  // Move to the next index in a circular manner
        }
        cout << endl;
    }
};
int main() {
    CircularQueue queue(5);  // Create a queue with a capacity of 5

    // Enqueue elements
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    // Print the queue
    cout << "Queue contents: ";
    queue.printQueue();

    // Try to enqueue when the queue is full
    queue.enqueue(60);

    // Dequeue elements
    cout << "Dequeued: " << queue.dequeue() << endl;
    cout << "Dequeued: " << queue.dequeue() << endl;

    // Print the queue after dequeuing
    cout << "Queue contents after dequeuing: ";
    queue.printQueue();

    // Enqueue new elements after dequeuing
    queue.enqueue(60);
    queue.enqueue(70);

    // Print the queue after enqueueing new elements
    cout << "Queue contents after enqueueing new elements: ";
    queue.printQueue();

    // Get the front element
    cout << "Front element: " << queue.peek() << endl;

    // Check if the queue is empty
    if (queue.isEmpty()) {
        cout << "The queue is empty!" << endl;
    } else {
        cout << "The queue is not empty!" << endl;
    }

    return 0;
}
