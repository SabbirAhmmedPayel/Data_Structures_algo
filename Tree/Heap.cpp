#include <iostream>
using namespace std;

class Heap {
private:
    int* heap;        // Pointer to the dynamic array
    int capacity;     // Maximum capacity of the heap
    int size;         // Current size of the heap
    bool isMinHeap;   // True for Min-Heap, False for Max-Heap

    // Compare function for heap type
    bool compare(int parent, int child) {
        return isMinHeap ? parent > child : parent < child;
    }

    // Resize the dynamic array
    void resize() {
        capacity *= 2;
        int* newHeap = new int[capacity];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
    }

    // Heapify-up to maintain heap property after insertion
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && compare(heap[parent], heap[index])) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }

    // Heapify-down to maintain heap property after deletion
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallestOrLargest = index;

        if (left < size && compare(heap[smallestOrLargest], heap[left])) {
            smallestOrLargest = left;
        }

        if (right < size && compare(heap[smallestOrLargest], heap[right])) {
            smallestOrLargest = right;
        }

        if (smallestOrLargest != index) {
            swap(heap[index], heap[smallestOrLargest]);
            heapifyDown(smallestOrLargest);
        }
    }

    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }


public:
    // Constructor to initialize heap type and default capacity
    Heap(bool minHeap = false, int initialCapacity = 10)
        : isMinHeap(minHeap), capacity(initialCapacity), size(0) {
        heap = new int[capacity];
    }

    // Destructor to clean up the dynamic array
    ~Heap() {
        delete[] heap;
    }

    // Insert an element into the heap
    void insert(int value) {
        if (size == capacity) {
            resize();
        }
        heap[size++] = value;
        heapifyUp(size - 1);
    }

    // Get the maximum or minimum element
    int getExtreme() {
        if (size == 0) {
            throw runtime_error("Heap is empty!");
        }
        return heap[0];
    }

    // Delete the maximum or minimum element
    void deleteExtreme() {
        if (size == 0) {
            throw runtime_error("Heap is empty!");
        }
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    // Check if a value is in a given range
    bool inRange(int low, int high) {
        for (int i = 0; i < size; i++) {
            if (heap[i] >= low && heap[i] <= high) {
                return true;
            }
        }
        return false;
    }

     void heapSort() {
        buildHeap(); // Step 1: Build the heap
        for (int i = size - 1; i >= 1; i--) {
            swap(heap[0], heap[i]); // Swap the root (max or min) with the last element
            size--; // Decrease heap size
            heapifyDown(0); // Restore heap property
        }
    }

    // Delete a specific value from the heap
    void deleteValue(int value) {
        for (int i = 0; i < size; i++) {
            if (heap[i] == value) {
                heap[i] = heap[size - 1];
                size--;
                heapifyDown(i);
                heapifyUp(i);
                return;
            }
        }
    }

    // Print the heap
    void printHeap() {
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create a Max-Heap
    Heap maxHeap(false);

    cout << "Inserting values into the Max-Heap...\n";
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(15);
    maxHeap.insert(30);
    maxHeap.insert(40);

    cout << "Heap after insertions: ";
    maxHeap.printHeap();

    cout << "Maximum element: " << maxHeap.getExtreme() << endl;

    cout << "Deleting the maximum element...\n";
    maxHeap.deleteExtreme();
    cout << "Heap after deleting the maximum element: ";
    maxHeap.printHeap();

    cout << "Checking if value is in range (10 to 25): ";
    cout << (maxHeap.inRange(10, 25) ? "Yes" : "No") << endl;

    cout << "Deleting a specific value (15)...\n";
    maxHeap.deleteValue(15);
    cout << "Heap after deleting the value: ";
    maxHeap.printHeap();

    // Create a Min-Heap
    Heap minHeap(true);

    cout << "\nInserting values into the Min-Heap...\n";
    minHeap.insert(50);
    minHeap.insert(60);
    minHeap.insert(40);
    minHeap.insert(70);
    minHeap.insert(30);

    cout << "Heap after insertions: ";
    minHeap.printHeap();

    cout << "Minimum element: " << minHeap.getExtreme() << endl;

    cout << "Deleting the minimum element...\n";
    minHeap.deleteExtreme();
    cout << "Heap after deleting the minimum element: ";
    minHeap.printHeap();

    return 0;
}
