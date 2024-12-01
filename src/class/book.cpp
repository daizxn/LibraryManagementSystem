//
// Created by dai on 24-12-1.
//

#include "book.h"

Book::Book() {
    this->id = -1;
    this->name = "null";
    this->author = "null";
    this->isbn = "null";
    this->isBorrowed = false;
}

Book::Book(int id, const QString &name, const QString &author, const QString &isbn, bool isBorrowed) {
    this->id = id;
    this->name = name;
    this->author = author;
    this->isbn = isbn;
    this->isBorrowed = isBorrowed;
}

int Book::getId() const {
    return this->id;
}

void Book::setId(int id) {
    this->id = id;
}

const QString &Book::getName() const {
    return this->name;
}

void Book::setName(const QString &name) {
    this->name = name;
}

const QString &Book::getAuthor() const {
    return this->author;
}

void Book::setAuthor(const QString &author) {
    this->author = author;
}

const QString &Book::getIsbn() const {
    return this->isbn;
}

void Book::setIsbn(const QString &isbn) {
    this->isbn = isbn;
}

bool Book::getIsBorrowed() const {
    return this->isBorrowed;
}

void Book::setIsBorrowed(bool isBorrowed) {
    this->isBorrowed = isBorrowed;
}

void Book::set(const QString &name, const QString &author, const QString &isbn, bool isBorrowed) {
    this->name = name;
    this->author = author;
    this->isbn = isbn;
    this->isBorrowed = isBorrowed;
}

bool operator==(const Book &lhs, const Book &rhs) {
    return lhs.id == rhs.id && lhs.name == rhs.name && lhs.author == rhs.author && lhs.isbn == rhs.isbn;
}

