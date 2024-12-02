//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_AVLTREE_H
#define LIBRARYMANAGEMENTSYSTEM_AVLTREE_H

#include <algorithm>
#include <list>

template<typename T1, typename T2> //T1为键值类型，T2为数据类型
class AVLTree {
private:
    struct Node {
        //AVL树的节点
        T1 key;
        T2 data;
        Node *left;
        Node *right;
        int height;

        Node(const T1 &key, const T2 &data) : key(key), data(data), left(nullptr), right(nullptr), height(1) {
        }
    };

    Node *root;

    int getHeight(Node *node); //获取节点高度

    void updateHeight(Node *node); //更新节点高度

    int getBalanceFactor(Node *node); //获取节点平衡因子

    Node *getMinNode(Node *node); //获取最小节点

    Node *leftRotate(Node *node); //左旋

    Node *rightRotate(Node *node); //右旋

    Node *insert(Node *node, const T1 &key, const T2 &data); //插入节点

    Node *remove(Node *node, const T1 &key); //删除节点

    void deleteTree(Node *node); //删除树

public:
    AVLTree();

    explicit AVLTree(std::list<T1, T2> &list); //构造函数，传入一个列表

    ~AVLTree();

    void insert(const T1 &key, const T2 &data); //插入节点
    T2 *search(const T1 &key); //查找节点
    void remove(const T1 &key); //删除节点
    void clear(); //清空树
};

template<typename T1, typename T2>
int AVLTree<T1, T2>::getHeight(Node *node) {
    return node ? node->height : 0;
}

template<typename T1, typename T2>
void AVLTree<T1, T2>::updateHeight(Node *node) {
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

template<typename T1, typename T2>
int AVLTree<T1, T2>::getBalanceFactor(Node *node) {
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T1, typename T2>
typename AVLTree<T1, T2>::Node *AVLTree<T1, T2>::getMinNode(Node *node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template<typename T1, typename T2>
typename AVLTree<T1, T2>::Node *AVLTree<T1, T2>::leftRotate(Node *node) {
    //左旋
    Node *newRoot = node->right; //新根节点
    node->right = newRoot->left; //新根节点的左子树为原根节点的右子树
    newRoot->left = node; //原根节点为新根节点的左子树
    updateHeight(node); //更新原根节点的高度
    updateHeight(newRoot); //更新新根节点的高度
    return newRoot;
}

template<typename T1, typename T2>
typename AVLTree<T1, T2>::Node *AVLTree<T1, T2>::rightRotate(Node *node) {
    //右旋
    Node *newRoot = node->left; //新根节点
    node->left = newRoot->right; //新根节点的右子树为原根节点的左子树
    newRoot->right = node; //原根节点为新根节点的右子树
    updateHeight(node); //更新原根节点的高度
    updateHeight(newRoot); //更新新根节点的高度
    return newRoot;
}

template<typename T1, typename T2>
typename AVLTree<T1, T2>::Node *AVLTree<T1, T2>::insert(Node *node, const T1 &key, const T2 &data) {
    if (node == nullptr) {
        //如果节点为空，创建新节点
        return new Node(key, data);
    }
    if (key < node->key) {
        //如果键值小于当前节点的键值，插入到左子树
        node->left = insert(node->left, key, data);
    } else if (key > node->key) {
        //如果键值大于当前节点的键值，插入到右子树
        node->right = insert(node->right, key, data);
    } else {
        //如果键值等于当前节点的键值，更新数据
        node->data = data;
        return node;
    }
    updateHeight(node); //更新节点高度
    int balanceFactor = getBalanceFactor(node); //获取平衡因子
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        //左子树高度大于右子树高度，且左子树的左子树高度大于等于左子树的右子树高度
        return rightRotate(node); //右旋
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        //右子树高度大于左子树高度，且右子树的右子树高度大于等于右子树的左子树高度
        return leftRotate(node); //左旋
    }
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        //左子树高度大于右子树高度，且左子树的右子树高度大于左子树的左子树高度
        node->left = leftRotate(node->left); //左子树左旋
        return rightRotate(node); //右旋
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        //右子树高度大于左子树高度，且右子树的左子树高度大于右子树的右子树高度
        node->right = rightRotate(node->right); //右子树右旋
        return leftRotate(node); //左旋
    }
    return node;
}

template<typename T1, typename T2>
typename AVLTree<T1, T2>::Node *AVLTree<T1, T2>::remove(Node *node, const T1 &key) {
    if (node == nullptr) {
        return node; // 如果节点为空，直接返回
    }

    // 递归查找并删除节点
    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        // 找到要删除的节点
        if (node->left == nullptr || node->right == nullptr) {
            // 只有一个子节点或没有子节点的情况
            Node *temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                // 没有子节点，直接删除当前节点
                temp = node;
                node = nullptr;
            } else {
                // 只有一个子节点，直接替换当前节点
                *node = *temp;
            }
            delete temp; // 删除节点
        } else {
            // 当前节点有两个子节点，找右子树的最小节点
            Node *temp = getMinNode(node->right);
            node->key = temp->key; // 用右子树最小节点替换当前节点的键值
            node->data = temp->data; // 用右子树最小节点替换当前节点的数据
            node->right = remove(node->right, temp->key); // 删除右子树中的最小节点
        }
    }

    // 如果当前节点为空，直接返回
    if (node == nullptr) {
        return node;
    }

    // 更新当前节点的高度
    updateHeight(node);

    // 获取当前节点的平衡因子
    int balanceFactor = getBalanceFactor(node);

    // 左子树比右子树重，可能是左左或左右情况
    if (balanceFactor > 1) {
        // 左子树的右子树重（左右情况），需要先左旋
        if (getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left); // 左旋
        }
        return rightRotate(node); // 右旋
    }

    // 右子树比左子树重，可能是右右或右左情况
    if (balanceFactor < -1) {
        // 右子树的左子树重（右左情况），需要先右旋
        if (getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right); // 右旋
        }
        return leftRotate(node); // 左旋
    }

    return node; // 返回更新后的节点
}

template<typename T1, typename T2>
void AVLTree<T1, T2>::deleteTree(Node *node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

template<typename T1, typename T2>
AVLTree<T1, T2>::AVLTree() : root(nullptr) {
}

template<typename T1, typename T2>
AVLTree<T1, T2>::AVLTree(std::list<T1, T2> &list) : root(nullptr) {
    for (auto &item: list) {
        //遍历列表，插入节点
        insert(item.first, item.second); //item.first为键值，item.second为数据
    }
}

template<typename T1, typename T2>
AVLTree<T1, T2>::~AVLTree() {
    clear();
}

// 公开接口
template<typename T1, typename T2>
void AVLTree<T1, T2>::insert(const T1 &key, const T2 &data) {
    root = insert(root, key, data);
}

template<typename T1, typename T2>
T2 *AVLTree<T1, T2>::search(const T1 &key) {
    Node *node = root;
    while (node) {
        //遍历树
        if (key < node->key) {
            //如果键值小于当前节点的键值，进入左子树
            node = node->left;
        } else if (key > node->key) {
            //如果键值大于当前节点的键值，进入右子树
            node = node->right;
        } else {
            //如果键值等于当前节点的键值，返回数据
            return &node->data;
        }
    }
    return nullptr; //如果没有找到，返回空指针
}

// 公开接口，调用删除操作
template<typename T1, typename T2>
void AVLTree<T1, T2>::remove(const T1 &key) {
    root = remove(root, key); //删除节点
}

template<typename T1, typename T2>
void AVLTree<T1, T2>::clear() {
    deleteTree(root); //删除树
    root = nullptr;
}

#endif //LIBRARYMANAGEMENTSYSTEM_AVLTREE_H
