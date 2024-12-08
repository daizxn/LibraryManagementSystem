//
// Created by dai on 24-12-8.
//


#include <gtest/gtest.h>
#include "data/RBTree.h"

TEST(RedBlackTreeTests, InsertSingleNode) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    auto values = tree.search(1);
    ASSERT_EQ(values.size(), 1);
    ASSERT_EQ(values[0], "data1");
}

TEST(RedBlackTreeTests, InsertMultipleNodes) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    auto values1 = tree.search(1);
    auto values2 = tree.search(2);
    auto values3 = tree.search(3);
    ASSERT_EQ(values1.size(), 1);
    ASSERT_EQ(values1[0], "data1");
    ASSERT_EQ(values2.size(), 1);
    ASSERT_EQ(values2[0], "data2");
    ASSERT_EQ(values3.size(), 1);
    ASSERT_EQ(values3[0], "data3");
}

TEST(RedBlackTreeTests, InsertDuplicateKey) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(1, "data2");
    auto values = tree.search(1);
    ASSERT_EQ(values.size(), 2);
    ASSERT_EQ(values[0], "data1");
    ASSERT_EQ(values[1], "data2");
}

TEST(RedBlackTreeTests, RemoveSingleNode) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.remove(1, "data1");
    auto values = tree.search(1);
    ASSERT_TRUE(values.empty());
}

TEST(RedBlackTreeTests, RemoveNonExistentNode) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.remove(2, "data2");
    auto values = tree.search(1);
    ASSERT_EQ(values.size(), 1);
    ASSERT_EQ(values[0], "data1");
}

TEST(RedBlackTreeTests, RemoveNodeWithOneChild) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.remove(1, "data1");
    auto values = tree.search(2);
    ASSERT_EQ(values.size(), 1);
    ASSERT_EQ(values[0], "data2");
    ASSERT_TRUE(tree.search(1).empty());
}

TEST(RedBlackTreeTests, RemoveNodeWithTwoChildren) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    tree.remove(2, "data2");
    auto values1 = tree.search(1);
    auto values3 = tree.search(3);
    ASSERT_EQ(values1.size(), 1);
    ASSERT_EQ(values1[0], "data1");
    ASSERT_EQ(values3.size(), 1);
    ASSERT_EQ(values3[0], "data3");
    ASSERT_TRUE(tree.search(2).empty());
}

TEST(RedBlackTreeTests, ClearTree) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.clear();
    ASSERT_TRUE(tree.search(1).empty());
    ASSERT_TRUE(tree.search(2).empty());
}

TEST(RedBlackTreeTests, SearchEmptyTree) {
    RedBlackTree<int, std::string> tree;
    ASSERT_TRUE(tree.search(1).empty());
}

TEST(RedBlackTreeTests, InsertAndSearchLargeNumberOfNodes) {
    RedBlackTree<int, std::string> tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i, "data" + std::to_string(i));
    }
    for (int i = 0; i < 1000; ++i) {
        auto values = tree.search(i);
        ASSERT_EQ(values.size(), 1);
        ASSERT_EQ(values[0], "data" + std::to_string(i));
    }
}

TEST(RedBlackTreeTests, RemoveAllNodes) {
    RedBlackTree<int, std::string> tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(i, "data" + std::to_string(i));
    }
    for (int i = 0; i < 100; ++i) {
        tree.remove(i, "data" + std::to_string(i));
        ASSERT_TRUE(tree.search(i).empty());
    }
}

TEST(RedBlackTreeTests, SearchNonExistentNode) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    ASSERT_TRUE(tree.search(999).empty());
}


TEST(RedBlackTreeTests, RemoveRootNode) {
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    tree.remove(1, "data1");
    ASSERT_TRUE(tree.search(1).empty());
    auto values2 = tree.search(2);
    auto values3 = tree.search(3);
    ASSERT_EQ(values2.size(), 1);
    ASSERT_EQ(values2[0], "data2");
    ASSERT_EQ(values3.size(), 1);
    ASSERT_EQ(values3[0], "data3");
}