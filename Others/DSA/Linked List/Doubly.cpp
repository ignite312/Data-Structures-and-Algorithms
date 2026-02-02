#include <iostream>

using namespace std;

struct Node {
  int val;
  Node * prev;
  Node * next;

  Node(int v): val(v), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
  private: 
    Node * head;
    Node * tail;

  public: 
    DoublyLinkedList(): head(nullptr), tail(nullptr) {}

  // Insert at front
  void insertFront(int val) {
    Node * node = new Node(val);

    if (!head) {
      head = tail = node;
      return;
    }

    node -> next = head;
    head -> prev = node;
    head = node;
  }

  // Insert at back
  void insertBack(int val) {
    Node * node = new Node(val);

    if (!tail) {
      head = tail = node;
      return;
    }

    tail -> next = node;
    node -> prev = tail;
    tail = node;
  }

  // Delete first occurrence of a value
  void deleteValue(int val) {
    Node * curr = head;

    while (curr && curr -> val != val)
      curr = curr -> next;

    if (!curr) return;

    if (curr == head)
      head = curr -> next;

    if (curr == tail)
      tail = curr -> prev;

    if (curr -> prev)
      curr -> prev -> next = curr -> next;

    if (curr -> next)
      curr -> next -> prev = curr -> prev;

    delete curr;
  }

  // Traverse forward
  void displayForward() {
    Node * curr = head;
    while (curr) {
      cout << curr -> val << " ";
      curr = curr -> next;
    }
    cout << endl;
  }

  // Traverse backward
  void displayBackward() {
    Node * curr = tail;
    while (curr) {
      cout << curr -> val << " ";
      curr = curr -> prev;
    }
    cout << endl;
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while (tt--) {
    DoublyLinkedList dll;

    dll.insertFront(2);
    dll.insertFront(1);
    dll.insertBack(3);
    dll.insertBack(4);

    dll.displayForward(); // 1 2 3 4
    dll.displayBackward(); // 4 3 2 1

    dll.deleteValue(3);
    dll.displayForward(); // 1 2 4
  }
  return 0;
}