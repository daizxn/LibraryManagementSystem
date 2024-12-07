//
// Created by dai on 24-12-3.
//
#include <gtest/gtest.h>
#include "data/list.h"

TEST(LinkedListTests, InsertSingleNode) {
    list::LinkedList<int> linkedList;
    linkedList.insert(1);
    ASSERT_EQ(linkedList.head->next->getData(), 1);
}

TEST(LinkedListTests, InsertMultipleNodes) {
    list::LinkedList<int> linkedList;
    linkedList.insert(1);
    linkedList.insert(2);
    linkedList.insert(3);
    ASSERT_EQ(linkedList.head->next->getData(), 1);
    ASSERT_EQ(linkedList.head->next->next->getData(), 2);
    ASSERT_EQ(linkedList.head->next->next->next->getData(), 3);
}

TEST(LinkedListTests, InsertAndRemoveNodes) {
    list::LinkedList<int> linkedList;
    linkedList.insert(1);
    linkedList.insert(2);
    linkedList.insert(3);
    delete linkedList.head->next->next; // Remove node with data 2
    ASSERT_EQ(linkedList.head->next->getData(), 1);
    ASSERT_EQ(linkedList.head->next->next->getData(), 3);
}

TEST(LinkedListTests, InsertNullValue) {
    list::LinkedList<int*> linkedList;
    linkedList.insert(nullptr);
    ASSERT_EQ(linkedList.head->next->getData(), nullptr);
}

TEST(LinkedListTests, InsertAndRemoveAllNodes) {
    list::LinkedList<int> linkedList;
    for (int i = 0; i < 100; ++i) {
        linkedList.insert(i);
    }
    for (int i = 0; i < 100; ++i) {
        delete linkedList.head->next;
    }
    ASSERT_EQ(linkedList.head->next, nullptr);
}