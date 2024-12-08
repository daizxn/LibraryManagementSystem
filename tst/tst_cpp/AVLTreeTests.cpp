#include <gtest/gtest.h>
#include "data/AVLTree.h"

TEST(AVLTreeTests, InsertSingleNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    ASSERT_EQ(*tree.search(1), "data1");
}

TEST(AVLTreeTests, InsertMultipleNodes) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    ASSERT_EQ(*tree.search(1), "data1");
    ASSERT_EQ(*tree.search(2), "data2");
    ASSERT_EQ(*tree.search(3), "data3");
}

TEST(AVLTreeTests, InsertDuplicateKey) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(1, "data2");
    ASSERT_EQ(*tree.search(1), "data2");
}

TEST(AVLTreeTests, RemoveSingleNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.remove(1);
    ASSERT_EQ(tree.search(1), nullptr);
}

TEST(AVLTreeTests, RemoveNonExistentNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.remove(2);
    ASSERT_EQ(*tree.search(1), "data1");
}

TEST(AVLTreeTests, RemoveNodeWithOneChild) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.remove(1);
    ASSERT_EQ(*tree.search(2), "data2");
    ASSERT_EQ(tree.search(1), nullptr);
}

TEST(AVLTreeTests, RemoveNodeWithTwoChildren) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    tree.remove(2);
    ASSERT_EQ(*tree.search(1), "data1");
    ASSERT_EQ(*tree.search(3), "data3");
    ASSERT_EQ(tree.search(2), nullptr);
}

TEST(AVLTreeTests, ClearTree) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.clear();
    ASSERT_EQ(tree.search(1), nullptr);
    ASSERT_EQ(tree.search(2), nullptr);
}

TEST(AVLTreeTests, SearchEmptyTree) {
    AVLTree<int, std::string> tree;
    ASSERT_EQ(tree.search(1), nullptr);
}

TEST(AVLTreeTests, InsertAndRemoveMultipleNodes) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    tree.remove(2);
    ASSERT_EQ(*tree.search(1), "data1");
    ASSERT_EQ(tree.search(2), nullptr);
    ASSERT_EQ(*tree.search(3), "data3");
}

TEST(AVLTreeTests, InsertAndSearchLargeNumberOfNodes) {
    AVLTree<int, std::string> tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i, "data" + std::to_string(i));
    }
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(*tree.search(i), "data" + std::to_string(i));
    }
}

TEST(AVLTreeTests, RemoveAllNodes) {
    AVLTree<int, std::string> tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(i, "data" + std::to_string(i));
    }
    for (int i = 0; i < 100; ++i) {
        tree.remove(i);
        ASSERT_EQ(tree.search(i), nullptr);
    }
}

TEST(AVLTreeTests, SearchNonExistentNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    ASSERT_EQ(tree.search(999), nullptr);
}


TEST(AVLTreeTests, RemoveRootNode) {
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    tree.remove(1);
    ASSERT_EQ(tree.search(1), nullptr);
    ASSERT_EQ(*tree.search(2), "data2");
    ASSERT_EQ(*tree.search(3), "data3");
}

TEST(AVLTreeTests,GetAllData){
    AVLTree<int, std::string> tree;
    tree.insert(1, "data1");
    tree.insert(2, "data2");
    tree.insert(3, "data3");
    std::vector<std::string> data = tree.getAllData();
    ASSERT_EQ(data.size(), 3);
    ASSERT_EQ(data[0], "data1");
    ASSERT_EQ(data[1], "data2");
    ASSERT_EQ(data[2], "data3");
}