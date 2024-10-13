#include "DoublyLinkedList.hpp"
#include <gtest/gtest.h>

TEST(DllTest, ShouldInitializeEmpty) {
  DoublyLinkedList dll;

  ASSERT_EQ(dll.front(), nullptr);
  ASSERT_EQ(dll.back(), nullptr);
  ASSERT_EQ(dll.size(), 0);
}

TEST(DllTest, ShouldInsertElementAtEnd) {
  DoublyLinkedList dll;

  dll.push_back(1);

  ASSERT_EQ(dll.size(), 1);
  ASSERT_NE(dll.back(), nullptr);
  ASSERT_EQ(dll.back(), dll.front());
  ASSERT_EQ(dll.back()->value, 1);
}

TEST(DllTest, ShouldInsertElementAtEndTwice) {
  DoublyLinkedList dll;

  dll.push_back(1);
  dll.push_back(2);

  ASSERT_EQ(dll.size(), 2);
  ASSERT_NE(dll.back(), nullptr);
  ASSERT_NE(dll.back(), dll.front());
  ASSERT_EQ(dll.back()->value, 2);
  ASSERT_EQ(dll.front()->value, 1);
}

TEST(DllTest, ShouldInsertElementAtBeggining) {
  DoublyLinkedList dll;

  dll.push_front(1);

  ASSERT_EQ(dll.size(), 1);
  ASSERT_NE(dll.front(), nullptr);
  ASSERT_EQ(dll.back(), dll.front());
  ASSERT_EQ(dll.front()->value, 1);
}

TEST(DllTest, ShouldInsertElementAtBegginingTwice) {
  DoublyLinkedList dll;

  dll.push_front(1);
  dll.push_front(2);

  ASSERT_EQ(dll.size(), 2);
  ASSERT_NE(dll.front(), nullptr);
  ASSERT_NE(dll.back(), dll.front());
  ASSERT_EQ(dll.front()->value, 2);
  ASSERT_EQ(dll.back()->value, 1);
}

TEST(DllTest, ShouldSwapElementsWhenNeeded) {
  DoublyLinkedList dll;

  dll.push_back(1);
  dll.push_back(2);
  dll.push_back(3);
  dll.push_back(4);
  dll.push_back(5);

  Node *first_el = dll.front()->next;
  Node *second_el = dll.back()->prev;

  dll.swap(first_el, second_el);

  ASSERT_EQ(dll.front()->value, 1);
  ASSERT_EQ(dll.front()->next->value, 4);
  ASSERT_EQ(dll.front()->next->next->value, 3);
  ASSERT_EQ(dll.back()->prev->value, 2);
  ASSERT_EQ(dll.back()->value, 5);
}

TEST(DllTest, ShouldReinsertAtBackElementsWhenNeeded) {
  DoublyLinkedList dll;

  dll.push_back(1);
  dll.push_back(2);
  dll.push_back(3);
  dll.push_back(4);
  dll.push_back(5);

  // Index 2
  Node *position_to_reinsert = dll.front()->next->next;
  Node *node_to_replace = dll.front();

  dll.reinsert_before(position_to_reinsert, node_to_replace);

  ASSERT_EQ(dll.front()->value, 2);
  ASSERT_EQ(dll.front()->next->value, 1);
  ASSERT_EQ(dll.front()->next->next->value, 3);
  ASSERT_EQ(dll.back()->prev->value, 4);
  ASSERT_EQ(dll.back()->value, 5);
}

TEST(DllTest, ShouldReinsertAtFrontElementsWhenNeeded) {
  DoublyLinkedList dll;

  dll.push_back(1);
  dll.push_back(2);
  dll.push_back(3);
  dll.push_back(4);
  dll.push_back(5);

  // Index 2
  Node *position_to_reinsert = dll.front()->next->next;
  Node *node_to_replace = dll.front();

  dll.reinsert_after(position_to_reinsert, node_to_replace);

  ASSERT_EQ(dll.front()->value, 2);
  ASSERT_EQ(dll.front()->next->value, 3);
  ASSERT_EQ(dll.front()->next->next->value, 1);
  ASSERT_EQ(dll.back()->prev->value, 4);
  ASSERT_EQ(dll.back()->value, 5);
}

TEST(DllTest, ShouldReverseElementsWhenNeeded) {
  DoublyLinkedList dll;

  dll.push_back(1);
  dll.push_back(2);
  dll.push_back(3);
  dll.push_back(4);
  dll.push_back(5);

  Node *position_to_begin = dll.front();
  Node *position_to_end = dll.back();

  dll.reverse(position_to_begin, position_to_end);

  ASSERT_EQ(dll.front()->value, 4);
  ASSERT_EQ(dll.front()->next->value, 3);
  ASSERT_EQ(dll.front()->next->next->value, 2);
  ASSERT_EQ(dll.back()->prev->value, 1);
  ASSERT_EQ(dll.back()->value, 5);
}

TEST(DllTest, ShouldPopBack) {
  DoublyLinkedList dll;

  dll.push_back(1);
  dll.push_back(2);
  dll.push_back(3);
  dll.push_back(4);
  dll.push_back(5);

  dll.pop_back();

  ASSERT_EQ(dll.size(), 4);

  ASSERT_EQ(dll.front()->value, 1);
  ASSERT_EQ(dll.front()->next->value, 2);
  ASSERT_EQ(dll.front()->next->next->value, 3);
  ASSERT_EQ(dll.back()->value, 4);
}