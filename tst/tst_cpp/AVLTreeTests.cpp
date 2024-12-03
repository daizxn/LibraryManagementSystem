#include <gtest/gtest.h>
#include "AVLTree.h"

TEST(AVLTreeTests, InsertAndSearchLargeNumberOfNodes) {
    AVLTree<int, std::string> tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i, new std::string("data" + std::to_string(i)));
    }
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(*tree.search(i), "data" + std::to_string(i));
    }
}

TEST(AVLTreeTests, RemoveAllNodes) {
    AVLTree<int, std::string> tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(i, new std::string("data" + std::to_string(i)));
    }
    for (int i = 0; i < 100; ++i) {
        tree.remove(i);
        ASSERT_EQ(tree.search(i), nullptr);
    }
}

TEST(AVLTreeTests, SearchNonExistentNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, new std::string("data1"));
    ASSERT_EQ(tree.search(999), nullptr);
}

TEST(AVLTreeTests, InsertNullValue) {
    AVLTree<int, std::string> tree;
    tree.insert(1, nullptr);
    ASSERT_EQ(tree.search(1), nullptr);
}

TEST(AVLTreeTests, RemoveRootNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, new std::string("data1"));
    tree.insert(2, new std::string("data2"));
    tree.insert(3, new std::string("data3"));
    tree.remove(1);
    ASSERT_EQ(tree.search(1), nullptr);
    ASSERT_EQ(*tree.search(2), "data2");
    ASSERT_EQ(*tree.search(3), "data3");
}

TEST(AVLTreeTests, InsertAndRemoveMultipleNodes) {
    AVLTree<int, std::string> tree;
    tree.insert(1, new std::string("data1"));
    tree.insert(2, new std::string("data2"));
    tree.insert(3, new std::string("data3"));
    tree.remove(2);
    ASSERT_EQ(*tree.search(1), "data1");
    ASSERT_EQ(tree.search(2), nullptr);
    ASSERT_EQ(*tree.search(3), "data3");
}

TEST(AVLTreeTests, InsertDuplicateKey) {
    AVLTree<int, std::string> tree;
    tree.insert(1, new std::string("data1"));
    tree.insert(1, new std::string("data2"));
    ASSERT_EQ(*tree.search(1), "data2");
}

TEST(AVLTreeTests, ClearTree) {
    AVLTree<int, std::string> tree;
    tree.insert(1, new std::string("data1"));
    tree.insert(2, new std::string("data2"));
    tree.clear();
    ASSERT_EQ(tree.search(1), nullptr);
    ASSERT_EQ(tree.search(2), nullptr);
}

TEST(AVLTreeTests, MulitpleInsertAndRemoveNodes) {
    AVLTree<int, std::string> tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i, new std::string("data" + std::to_string(i)));
    }
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(*tree.search(i), "data" + std::to_string(i));
    }

    tree.remove(76);
    tree.remove(876);
    tree.remove(999);
    ASSERT_EQ(*tree.search(1), "data"+std::to_string(1));
    ASSERT_EQ(*tree.search(2), "data"+std::to_string(2));
    ASSERT_EQ(*tree.search(100), "data"+std::to_string(100));
    ASSERT_EQ(tree.search(876), nullptr);
    ASSERT_EQ(tree.search(76), nullptr);
    ASSERT_EQ(tree.search(999), nullptr);
}
