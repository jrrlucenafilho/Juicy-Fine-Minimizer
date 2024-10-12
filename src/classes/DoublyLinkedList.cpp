#include "DoublyLinkedList.hpp"

#include <cstdlib>
#include <iostream>

DoublyLinkedList::DoublyLinkedList() {
  this->head = nullptr;
  this->tail = nullptr;

  this->length = 0;
}

// DoublyLinkedList::~DoublyLinkedList() {
//   while (this->head) {
//     this->pop_back();
//   }
// }

Node *DoublyLinkedList::front() { return this->head; }

Node *DoublyLinkedList::back() { return this->tail; }

size_t DoublyLinkedList::size() { return this->length; }

void DoublyLinkedList::clear() {
  while (this->head) {
    this->pop_back();
  }
}

bool DoublyLinkedList::find(size_t value) {
  for (Node *i = this->head; i != nullptr; i = i->next) {
    if (i->value == value) {
      return true;
    }
  }

  return false;
}

void DoublyLinkedList::push_back(size_t value) {
  Node *node = (Node *)malloc(sizeof(Node));

  if (!node) {
    std::cerr << "Error allocating memory to new node\n";
    exit(EXIT_FAILURE);
  }

  node->prev = this->tail;
  node->next = nullptr;
  node->value = value;

  if (this->tail) {
    this->tail->next = node;
  }

  this->tail = node;

  if (!this->head) {
    this->head = this->tail;
  }

  this->length++;
}

void DoublyLinkedList::push_front(size_t value) {
  Node *node = (Node *)malloc(sizeof(Node));

  if (!node) {
    std::cerr << "Error allocating memory to new node\n";
    exit(EXIT_FAILURE);
  }

  node->prev = nullptr;
  node->next = this->head;
  node->value = value;

  if (this->head) {
    this->head->prev = node;
  }

  this->head = node;

  if (!this->tail) {
    this->tail = this->head;
  }

  this->length++;
}

void DoublyLinkedList::swap(Node *first_el, Node *second_el) {
  if (first_el == nullptr || second_el == nullptr) {
    return;
  }

  size_t temp = first_el->value;
  first_el->value = second_el->value;
  second_el->value = temp;
}

void DoublyLinkedList::reinsert_before(Node *before_of,
                                       Node *node_to_reinsert) {
  if (before_of == node_to_reinsert)
    return;

  if (node_to_reinsert == this->head)
    this->head = node_to_reinsert->next;

  if (node_to_reinsert == this->tail)
    this->tail = node_to_reinsert->prev;

  if (before_of == this->head)
    this->head = node_to_reinsert;

  if (node_to_reinsert->prev)
    node_to_reinsert->prev->next = node_to_reinsert->next;

  if (node_to_reinsert->next)
    node_to_reinsert->next->prev = node_to_reinsert->prev;

  node_to_reinsert->next = before_of;
  node_to_reinsert->prev = before_of->prev;

  before_of->prev = node_to_reinsert;
  if (node_to_reinsert->prev)
    node_to_reinsert->prev->next = node_to_reinsert;
}

void DoublyLinkedList::reinsert_after(Node *after_of, Node *node_to_reinsert) {
  if (after_of == node_to_reinsert)
    return;

  if (node_to_reinsert == this->head) {
    this->head = node_to_reinsert->next;
  }

  if (node_to_reinsert == this->tail) {
    this->tail = node_to_reinsert->prev;
  }

  if (after_of == this->tail) {
    this->tail = node_to_reinsert;
  }

  if (node_to_reinsert->prev) {
    node_to_reinsert->prev->next = node_to_reinsert->next;
  }

  if (node_to_reinsert->next) {
    node_to_reinsert->next->prev = node_to_reinsert->prev;
  }

  node_to_reinsert->prev = after_of;
  node_to_reinsert->next = after_of->next;

  after_of->next = node_to_reinsert;
  if (node_to_reinsert->next)
    node_to_reinsert->next->prev = node_to_reinsert;
}

void DoublyLinkedList::reverse(Node *begin, Node *end) {
  Node *node_to_begin = begin;
  Node *node_to_end = end->prev;

  while (true) {
    swap(node_to_begin, node_to_end);

    if (node_to_begin == node_to_end || (node_to_begin->next == node_to_end &&
                                         node_to_end->prev == node_to_begin)) {
      break;
    }

    node_to_begin = node_to_begin->next;
    node_to_end = node_to_end->prev;
  }
}

void DoublyLinkedList::pop_back() {
  Node *old_head = this->tail;

  if (!this->tail)
    return;

  if (this->tail == this->head) {
    this->head = nullptr;
    this->tail = nullptr;
  } else {
    this->tail = old_head->prev;
  }

  this->length--;

  free(old_head);
}

void DoublyLinkedList::operator=(DoublyLinkedList const &obj) {
  this->clear();

  for (Node *i = obj.head; i != nullptr; i = i->next) {
    this->push_back(i->value);
  }
}
