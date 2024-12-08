#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <QList>

enum Color { RED, BLACK };

template <typename KeyType, typename ValueType>
class RedBlackTree
{
private:
    struct Node
    {
        KeyType key;
        std::vector<ValueType> values; // 支持一个键对应多个值
        Color color;
        std::shared_ptr<Node> left, right, parent;

        Node(KeyType k, ValueType v) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr)
        {
            values.push_back(v);
        }
    };

    std::shared_ptr<Node> root;

    // 辅助函数
    void leftRotate(std::shared_ptr<Node> x);
    void rightRotate(std::shared_ptr<Node> x);
    void insertFixup(std::shared_ptr<Node> z);
    void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
    void deleteNode(std::shared_ptr<Node> z);
    void deleteFixup(std::shared_ptr<Node> x, std::shared_ptr<Node> parent, bool isLeftChild);
    void clearHelper(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> treeMinimum(std::shared_ptr<Node> node);
    void inOrderTraversalHelper(std::shared_ptr<Node> node, QList<QPair<KeyType, ValueType>>& result);

public:
    RedBlackTree() : root(nullptr)
    {
    }

    void insert(const KeyType& key, const ValueType& value); // 插入一个键值对
    bool remove(const KeyType& key, const ValueType& value); // 删除特定键值对
    std::vector<ValueType> search(const KeyType& key) const; // 查询键对应的所有值
    void clear(); // 清空红黑树
    void printInOrder() const; // 中序遍历打印红黑树
    void printInOrderHelper(const std::shared_ptr<Node>& node) const;
    void inOrderTraversal(QList<QPair<KeyType, ValueType>>& result);
    bool contains(KeyType key);
};


template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::leftRotate(std::shared_ptr<Node> x)
{
    auto y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::rightRotate(std::shared_ptr<Node> x)
{
    auto y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v)
{
    if (!u->parent)
    {
        root = v; // 如果 u 是根节点，则更新根节点
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v; // 如果 u 是左孩子，替换为 v
    }
    else
    {
        u->parent->right = v; // 如果 u 是右孩子，替换为 v
    }
    if (v)
    {
        v->parent = u->parent; // 更新 v 的父节点
    }
}

template <typename KeyType, typename ValueType>
std::shared_ptr<typename RedBlackTree<KeyType, ValueType>::Node>
RedBlackTree<KeyType, ValueType>::treeMinimum(std::shared_ptr<Node> node)
{
    while (node->left)
    {
        node = node->left; // 不断向左子节点移动
    }
    return node;
}


template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    std::shared_ptr<Node> y = nullptr;
    auto x = root;

    // 查找插入位置
    while (x)
    {
        y = x;
        if (key == x->key)
        {
            // 如果键已存在，将值加入节点的值列表
            x->values.push_back(value);
            return;
        }
        x = key < x->key ? x->left : x->right;
    }

    // 创建新节点
    auto z = std::make_shared<Node>(key, value);
    z->parent = y;
    if (!y)
        root = z; // 树为空时作为根节点
    else if (key < y->key)
        y->left = z;
    else
        y->right = z;

    // 修复红黑树性质
    insertFixup(z);
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::insertFixup(std::shared_ptr<Node> z)
{
    while (z->parent && z->parent->color == RED)
    {
        auto gp = z->parent->parent;
        if (z->parent == gp->left)
        {
            auto uncle = gp->right;
            if (uncle && uncle->color == RED)
            {
                // Case 1: 叔叔节点是红色
                z->parent->color = BLACK;
                uncle->color = BLACK;
                gp->color = RED;
                z = gp;
            }
            else
            {
                if (z == z->parent->right)
                {
                    // Case 2: z 是右孩子
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: z 是左孩子
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(gp);
            }
        }
        else
        {
            auto uncle = gp->left;
            if (uncle && uncle->color == RED)
            {
                // Case 1: 叔叔节点是红色
                z->parent->color = BLACK;
                uncle->color = BLACK;
                gp->color = RED;
                z = gp;
            }
            else
            {
                if (z == z->parent->left)
                {
                    // Case 2: z 是左孩子
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: z 是右孩子
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(gp);
            }
        }
    }
    root->color = BLACK;
}

template <typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::remove(const KeyType& key, const ValueType& value)
{
    auto z = root;

    // 查找目标节点
    while (z && z->key != key)
    {
        z = key < z->key ? z->left : z->right;
    }

    if (!z) return false; // 未找到键

    // 删除值
    auto it = std::find(z->values.begin(), z->values.end(), value);
    if (it != z->values.end())
    {
        z->values.erase(it); // 从值列表中移除值
        if (z->values.empty())
            deleteNode(z);// 如果值列表为空，删除节点
        return true;
    }
    return false;
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::deleteNode(std::shared_ptr<Node> z) {
    auto y = z; // 要删除的节点或其后继
    auto yOriginalColor = y->color;
    std::shared_ptr<Node> x;
    std::shared_ptr<Node> xParent;

    if (!z->left) {
        x = z->right;
        transplant(z, z->right); // 用右子树替换 z
    } else if (!z->right) {
        x = z->left;
        transplant(z, z->left); // 用左子树替换 z
    } else {
        y = treeMinimum(z->right); // 找到后继节点
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        if (x) {
            xParent = x->parent; // 更新 xParent 为 x 的父节点
        } else {
            xParent = y->parent; // 如果 x 为空，xParent 就是 y 的父节点
        }

        bool isLeftChild = (xParent && x == xParent->left);
        deleteFixup(x, xParent, isLeftChild); // 修复树的平衡性
    }
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::deleteFixup(std::shared_ptr<Node> x, std::shared_ptr<Node> parent,
                                                   bool isLeftChild)
{
    while (x != root && (!x || x->color == BLACK))
    {
        if (isLeftChild)
        {
            auto w = parent->right; // 兄弟节点
            if (w->color == RED)
            {
                // Case 1: 兄弟节点是红色
                w->color = BLACK;
                parent->color = RED;
                leftRotate(parent);
                w = parent->right;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK))
            {
                // Case 2: 兄弟节点的子节点全是黑色
                w->color = RED;
                x = parent;
                parent = x->parent;
                isLeftChild = (parent && x == parent->left);
            }
            else
            {
                if (!w->right || w->right->color == BLACK)
                {
                    // Case 3: 兄弟节点的右子节点是黑色，左子节点是红色
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = parent->right;
                }
                // Case 4: 兄弟节点的右子节点是红色
                w->color = parent->color;
                parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                leftRotate(parent);
                x = root;
            }
        }
        else
        {
            auto w = parent->left; // 兄弟节点
            if (w->color == RED)
            {
                // Case 1: 兄弟节点是红色
                w->color = BLACK;
                parent->color = RED;
                rightRotate(parent);
                w = parent->left;
            }
            if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK))
            {
                // Case 2: 兄弟节点的子节点全是黑色
                w->color = RED;
                x = parent;
                parent = x->parent;
                isLeftChild = (parent && x == parent->left);
            }
            else
            {
                if (!w->left || w->left->color == BLACK)
                {
                    // Case 3: 兄弟节点的左子节点是黑色，右子节点是红色
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = parent->left;
                }
                // Case 4: 兄弟节点的左子节点是红色
                w->color = parent->color;
                parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rightRotate(parent);
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
}

template <typename KeyType, typename ValueType>
std::vector<ValueType> RedBlackTree<KeyType, ValueType>::search(const KeyType& key) const
{
    auto x = root;
    while (x)
    {
        if (key == x->key)
        {
            return x->values; // 返回所有值
        }
        x = key < x->key ? x->left : x->right;
    }
    return std::vector<ValueType>(); // 未找到键
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::printInOrder() const
{
    printInOrderHelper(root);
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::printInOrderHelper(const std::shared_ptr<Node>& node) const
{
    if (!node) return;
    printInOrderHelper(node->left); // 递归打印左子树
    std::cout << "Key: " << node->key << " | Values: ";
    for (const auto& value : node->values)
    {
        std::cout << value << " ";
    }
    std::cout << "| Color: " << (node->color == RED ? "Red" : "Black") << std::endl;
    printInOrderHelper(node->right); // 递归打印右子树
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::inOrderTraversalHelper(std::shared_ptr<Node> node, QList<QPair<KeyType, ValueType>>& result)
{
    if (!node) return;
    inOrderTraversalHelper(node->left, result); // 递归遍历左子树
    for (const auto& value : node->values)
    {
        result.append(qMakePair(node->key, value)); // 将键值对添加到结果列表
    }
    inOrderTraversalHelper(node->right, result); // 递归遍历右子树
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::inOrderTraversal(QList<QPair<KeyType, ValueType>>& result)
{
    inOrderTraversalHelper(root, result);
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::clear()
{
    clearHelper(root); // 递归释放节点
    root = nullptr; // 设置根节点为空
}

template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::clearHelper(std::shared_ptr<Node>& node)
{
    if (!node) return; // 如果节点为空，直接返回
    clearHelper(node->left); // 递归清空左子树
    clearHelper(node->right); // 递归清空右子树
    node.reset(); // 释放当前节点
}

template <typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::contains(KeyType key)
{
    auto x = root;
    while (x)
    {
        if (key == x->key)
        {
            return true;
        }
        x = key < x->key ? x->left : x->right;
    }
    return false;
}
