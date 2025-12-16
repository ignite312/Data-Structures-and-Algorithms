#include <iostream>
using namespace std;

class Node {
  public: int data;
  Node * next;

  Node(int value): data(value),
  next(nullptr) {}
};
class LinkedList {
  private: Node * head;
  public: LinkedList(): head(nullptr) {}

  // Insert at the front
  void insertFront(int value) {
    Node * newNode = new Node(value);
    newNode -> next = head;
    head = newNode;
  }

  // Insert after a given node
  void insertAfter(Node * prevNode, int value) {
    if (!prevNode) return;
    Node * newNode = new Node(value);
    newNode -> next = prevNode -> next;
    prevNode -> next = newNode;
  }

  // Insert at the end
  void insertBack(int value) {
    Node * newNode = new Node(value);
    if (!head) {
      head = newNode;
      return;
    }
    Node * last = head;
    while (last -> next) last = last -> next;
    last -> next = newNode;
  }

  // Search for a value
  bool search(int key) {
    Node * current = head;
    while (current) {
      if (current -> data == key) return true;
      current = current -> next;
    }
    return false;
  }

  // Delete a node by value
  void deleteNode(int key) {
    if (!head) return;

    if (head -> data == key) {
      Node * temp = head;
      head = head -> next;
      delete temp;
      return;
    }

    Node * current = head;
    Node * prev = nullptr;
    while (current && current -> data != key) {
      prev = current;
      current = current -> next;
    }

    if (!current) return;

    prev -> next = current -> next;
    delete current;
  }

  // Sort the linked list
  void sort() {
    if (!head || !head -> next) return;
    for (Node * i = head; i != nullptr; i = i -> next) {
      for (Node * j = head; j -> next != nullptr; j = j -> next) {
        if (j -> data > j -> next -> data) {
          swap(j -> data, j -> next -> data);
        }
      }
    }
  }

  // Reverse the list
  void reverse() {
    Node * prev = nullptr;
    Node * curr = head;
    Node * next = nullptr;

    while (curr != nullptr) {
      next = curr -> next;
      curr -> next = prev;
      prev = curr;
      curr = next;
    }

    head = prev;
  }

  // Display the list
  void display() {
    Node * current = head;
    while (current) {
      cout << current -> data << " ";
      current = current -> next;
    }
    cout << "\n";
  }

  // Getter for head
  Node * getHead() {
    return head;
  }
};
int main() {
  int tt;
  tt = 1;
  // cin >> tt;
  while (tt--) {
    LinkedList list;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      list.insertBack(x);
    }

    list.display();

    cin >> n;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      list.insertFront(x);
    }

    list.display();
    list.sort();
    list.reverse();
    list.display();

    cout << list.search(4) << "\n";
    list.deleteNode(4);
    cout << list.search(4) << "\n";
  }
  return 0;
}