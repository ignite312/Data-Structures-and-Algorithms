#include <bits/stdc++.h>

using namespace std;

class MaxHeap {
  private: vector < int > heap;

  // Heapify Down (used in delete or build)
  void heapifyDown(int idx, int n) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < n && heap[left] > heap[largest])
      largest = left;

    if (right < n && heap[right] > heap[largest])
      largest = right;

    if (largest != idx) {
      swap(heap[idx], heap[largest]);
      heapifyDown(largest, n);
    }
  }

  // Heapify Up (used in insert)
  void heapifyUp(int idx) {
    if (idx == 0) return;

    int parent = (idx - 1) / 2;
    if (heap[idx] > heap[parent]) {
      swap(heap[idx], heap[parent]);
      heapifyUp(parent);
    }
  }

  public: MaxHeap() {}

  // Construct heap from array
  MaxHeap(vector < int > & arr) {
    heap = arr;
    buildMaxHeap();
  }

  // Insert a value
  void insert(int val) {
    heap.push_back(val);
    heapifyUp(heap.size() - 1);
  }

  // Get maximum element
  int getMax() {
    if (!heap.empty())
      return heap[0];
    throw runtime_error("Heap is empty");
  }

  // Delete maximum element
  void deleteMax() {
    int n = heap.size();
    if (n == 0) return;

    swap(heap[0], heap[n - 1]);
    heap.pop_back();
    if (!heap.empty())
      heapifyDown(0, heap.size());
  }

  // Build max heap from current heap array (bottom-up)
  void buildMaxHeap() {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; i--) { // from last leaf node
      heapifyDown(i, n);
    }
  }

  // Heap Sort: sorts heap array in ascending order
  vector < int > heapSort() {
    vector < int > sorted = heap; // copy original heap
    int n = sorted.size();

    // Build max heap on the copied array
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapifyDownArray(sorted, i, n);
    }

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
      swap(sorted[0], sorted[i]); // move max to end
      heapifyDownArray(sorted, 0, i); // heapify reduced heap
    }

    return sorted;
  }

  // Helper for heap sort (heapify a given array)
  void heapifyDownArray(vector < int > & arr, int idx, int n) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < n && arr[left] > arr[largest])
      largest = left;
    if (right < n && arr[right] > arr[largest])
      largest = right;
    if (largest != idx) {
      swap(arr[idx], arr[largest]);
      heapifyDownArray(arr, largest, n);
    }
  }

  void printHeap() {
    for (int val: heap) cout << val << " ";
    cout << "\n";
  }
};

int main() {
  vector < int > arr = {
    30,
    20,
    15,
    10,
    8,
    50,
    16
  };
  MaxHeap h(arr); // Build heap from array

  cout << "Max Heap: ";
  h.printHeap(); // heap after build

  cout << "Max: " << h.getMax() << "\n";

  h.deleteMax();
  cout << "After deleting max: ";
  h.printHeap();

  // Heap sort
  vector < int > sorted = h.heapSort();
  cout << "Heap sorted array: ";
  for (int val: sorted) cout << val << " ";
  cout << "\n";

  return 0;
}