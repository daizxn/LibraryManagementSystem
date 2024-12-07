#ifndef LIBRARYMANAGEMENTSYSTEM_AVLTREE_H
#define LIBRARYMANAGEMENTSYSTEM_AVLTREE_H

#include <algorithm>

template<typename K, typename V> // K为键，V为值
class AVLTree {
private:
    struct Node {
        K key;    // 键
        V data;   // 存储对象，而非指针
        Node *left;
        Node *right;
        int height;

        // 构造函数
        Node(const K &key, const V &data) : key(key), data(data), left(nullptr), right(nullptr), height(1) {}

        // 不需要析构函数，因为对象会自动销毁
    };

    Node *root;

    int getHeight(Node *node); // 获取节点高度

    void updateHeight(Node *node); // 更新节点高度

    int getBalanceFactor(Node *node); // 获取节点平衡因子

    Node *getMinNode(Node *node); // 获取最小节点

    Node *leftRotate(Node *node); // 左旋

    Node *rightRotate(Node *node); // 右旋

    Node *balance(Node *node); // 平衡节点

    Node *insert(Node *node, const K &key, const V &data); // 插入节点

    Node *remove(Node *node, const K &key); // 删除节点

    void destroyTree(Node *node); // 删除树

public:
    AVLTree();

    ~AVLTree();

    void insert(const K &key, const V &data); // 插入节点
    void remove(const K &key); // 删除节点
    V *search(const K &key); // 查找节点
    void clear(); // 清空树
};

template<typename K, typename V>
int AVLTree<K, V>::getHeight(Node *node) {
    return node == nullptr ? 0 : node->height;
}

template<typename K, typename V>
void AVLTree<K, V>::updateHeight(Node *node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template<typename K, typename V>
int AVLTree<K, V>::getBalanceFactor(Node *node) {
    return getHeight(node->left) - getHeight(node->right);
}

template<typename K, typename V>
typename AVLTree<K, V>::Node *AVLTree<K, V>::getMinNode(Node *node) {
    return node->left == nullptr ? node : getMinNode(node->left);
}

template<typename K, typename V>
typename AVLTree<K, V>::Node *AVLTree<K, V>::leftRotate(Node *node) {
    Node *newNode = node->right;
    node->right = newNode->left;
    newNode->left = node;
    updateHeight(node);
    updateHeight(newNode);
    return newNode;
}

template<typename K, typename V>
typename AVLTree<K, V>::Node *AVLTree<K, V>::rightRotate(Node *node) {
    Node *newNode = node->left;
    node->left = newNode->right;
    newNode->right = node;
    updateHeight(node);
    updateHeight(newNode);
    return newNode;
}

template<typename K, typename V>
typename AVLTree<K, V>::Node *AVLTree<K, V>::balance(Node *node) {
    // 平衡节点
    if (node == nullptr) {
        return nullptr;
    }
    const int balanceFactor = getBalanceFactor(node); // 获取平衡因子
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left); // 左旋
        }
        return rightRotate(node); // 右旋
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right); // 右旋
        }
        return leftRotate(node); // 左旋
    }
    return node;
}

template<typename K, typename V>
typename AVLTree<K, V>::Node *AVLTree<K, V>::insert(Node *node, const K &key, const V &data) {
    if (node == nullptr) {
        // 空节点，创建新节点
        return new Node(key, data);
    }
    if (key < node->key) {
        // 插入左子树
        node->left = insert(node->left, key, data);
    } else if (key > node->key) {
        // 插入右子树
        node->right = insert(node->right, key, data);
    } else {
        // key == node->key，更新数据
        node->data = data;
        return node;
    }
    updateHeight(node);
    return balance(node); // 平衡节点
}

template<typename K, typename V>
typename AVLTree<K, V>::Node *AVLTree<K, V>::remove(Node *node, const K &key) {
    if (node == nullptr) return nullptr;
    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        // 找到要删除的节点
        if (node->left == nullptr || node->right == nullptr) {
            Node *temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                // 只有一个子节点
                *node = *temp;  // 直接将子节点的数据赋值给当前节点
                temp->left = temp->right = nullptr; // 清空子节点
            }
            delete temp; // 删除节点
        } else {
            // 找右子树的最小节点
            Node *temp = getMinNode(node->right);
            node->key = temp->key;
            node->data = temp->data;
            node->right = remove(node->right, temp->key);
        }
    }
    if (node == nullptr) return nullptr;
    updateHeight(node);
    return balance(node); // 平衡树
}

template<typename K, typename V>
void AVLTree<K, V>::destroyTree(Node *node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template<typename K, typename V>
AVLTree<K, V>::AVLTree() : root(nullptr) {}

template<typename K, typename V>
AVLTree<K, V>::~AVLTree() {
    clear();
}

template<typename K, typename V>
void AVLTree<K, V>::insert(const K &key, const V &data) {
    root = insert(root, key, data);
}

template<typename K, typename V>
void AVLTree<K, V>::remove(const K &key) {
    root = remove(root, key);
}

template<typename K, typename V>
V *AVLTree<K, V>::search(const K &key) {
    Node *node = root;
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return &node->data;
        }
    }
    return nullptr;
}

template<typename K, typename V>
void AVLTree<K, V>::clear() {
    destroyTree(root);
    root = nullptr;
}

#endif // LIBRARYMANAGEMENTSYSTEM_AVLTREE_H
