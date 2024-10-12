#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <cstddef>

typedef struct Node {
  Node *prev;

  size_t value;

  Node *next;
} Node;

class DoublyLinkedList {
public:
  DoublyLinkedList();

  ~DoublyLinkedList();

  Node *front();

  Node *back();

  size_t size();

  void push_back(size_t value);

  void push_front(size_t value);

  void swap(Node *first_el, Node *second_el);

  void reinsert_before(Node *before_of, Node *node_to_reinsert);

  void reinsert_after(Node *after_of, Node *node_to_reinsert);

  void reverse(Node *begin, Node *end);

  void pop_back();

private:
  size_t length;

  Node *head;
  Node *tail;
};

#endif