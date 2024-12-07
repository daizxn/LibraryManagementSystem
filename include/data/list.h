//
// Created by dai on 24-12-3.
//

#ifndef LIST_H
#define LIST_H
#include "data/list.h"

namespace list {
    template<typename T>
    class ListNode;
    template<typename T>
    class LinkedList;
}


template<typename T>
class list::ListNode {
//private:
public:
    T data;
    ListNode<T> *next;
    ListNode<T> *prev;

public:
    explicit ListNode(T data);

    ~ListNode();

    T getData();

    friend class list::LinkedList<T>;
};

template<typename T>
list::ListNode<T>::ListNode(T data) : data(data), next(nullptr), prev(nullptr) {
}

template<typename T>
list::ListNode<T>::~ListNode() {
    if (prev != nullptr) {
        prev->next = next;
    }
    if (next != nullptr) {
        next->prev = prev;
    }
}

template<typename T>
T list::ListNode<T>::getData() {
    return data;
}


template<typename T>
class list::LinkedList {
//private:
public:
    list::ListNode<T> *head;
    list::ListNode<T> *tail;

public:
    LinkedList();

    ~LinkedList();

    void insert(T data);

    list::ListNode<T> *getHead() {
        return head;
    }
};

template<typename T>
list::LinkedList<T>::LinkedList() {
    head = new list::ListNode<T>(T());
    tail = head;
}

template<typename T>
list::LinkedList<T>::~LinkedList() {
    list::ListNode<T> *temp = head;
    while (temp != nullptr) {
        list::ListNode<T> *next = temp->next;
        delete temp;
        temp = next;
    }
}

template<typename T>
void list::LinkedList<T>::insert(T data) {
    auto *node = new list::ListNode<T>(data);
    tail->next = node;
    node->prev = tail;
    tail = node;
}


#endif //LIST_H
