#include <iostream>

using namespace std;

struct Node {
  int data;
  Node * next;

  Node(int value): data(value), next(nullptr) {}
};

class CircularLinkedList {
  private: Node * head;

  public: CircularLinkedList(): head(nullptr) {}

  void traverse() {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    Node * temp = head;
    do {
      cout << temp -> data << " ";
      temp = temp -> next;
    } while (temp != head);
    cout << endl;
  }

  void insertAtBeginning(int value) {
    Node * newNode = new Node(value);

    if (!head) {
      newNode -> next = newNode; // Point to itself
      head = newNode;
    } else {
      Node * temp = head;
      while (temp -> next != head) {
        temp = temp -> next;
      }
      newNode -> next = head;
      temp -> next = newNode;
      head = newNode;
    }
  }

  void insertAtEnd(int value) {
    Node * newNode = new Node(value);

    if (!head) {
      newNode -> next = newNode;
      head = newNode;
    } else {
      Node * temp = head;
      while (temp -> next != head) {
        temp = temp -> next;
      }
      temp -> next = newNode;
      newNode -> next = head;
    }
  }

  // Delete a node by value
  void deleteNode(int value) {
    if (!head) return;

    Node * curr = head;
    Node * prev = nullptr;

    // If head is to be deleted
    if (head -> data == value) {
      if (head -> next == head) {
        delete head;
        head = nullptr;
      } else {
        Node * temp = head;
        while (temp -> next != head) temp = temp -> next;

        Node * toDelete = head;
        temp -> next = head -> next;
        head = head -> next;
        delete toDelete;
      }
      return;
    }

    // Deleting other nodes
    prev = head;
    curr = head -> next;
    while (curr != head) {
      if (curr -> data == value) {
        prev -> next = curr -> next;
        delete curr;
        return;
      }
      prev = curr;
      curr = curr -> next;
    }

    cout << "Node not found." << endl;
  }
};

int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    CircularLinkedList cll;

    cll.insertAtEnd(10);
    cll.insertAtEnd(20);
    cll.insertAtEnd(30);

    cout << "List after inserting at end: ";
    cll.traverse();

    cll.insertAtBeginning(5);
    cout << "List after inserting at beginning: ";
    cll.traverse();

    cll.deleteNode(20);
    cout << "List after deleting 20: ";
    cll.traverse();

    cll.deleteNode(5);
    cout << "List after deleting 5: ";
    cll.traverse();

    cll.deleteNode(100);
  }
  return 0;
}