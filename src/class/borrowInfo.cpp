//
// Created by dai on 24-12-1.
//

#include "borrowInfo.h"

BorrowInfo::BorrowInfo() {
    this->id = -1;
    this->bookId = -1;
    this->userId = -1;
    this->borrowDate = "null";
    this->returnDate = "null";
    this->isReturned = false;
}

BorrowInfo::BorrowInfo(int id, int bookId, int userId, const QString &borrowDate, const QString &returnDate,
                       bool isReturned) {
    this->id = id;
    this->bookId = bookId;
    this->userId = userId;
    this->borrowDate = borrowDate;
    this->returnDate = returnDate;
    this->isReturned = isReturned;
}

int BorrowInfo::getId() const {
    return this->id;
}

void BorrowInfo::setId(int id) {
    this->id = id;
}

int BorrowInfo::getBookId() const {
    return this->bookId;
}

void BorrowInfo::setBookId(int bookId) {
    this->bookId = bookId;
}

int BorrowInfo::getUserId() const {
    return this->userId;
}

void BorrowInfo::setUserId(int userId) {
    this->userId = userId;
}

QString BorrowInfo::getBorrowDate() const {
    return this->borrowDate;
}

void BorrowInfo::setBorrowDate(const QString &borrowDate) {
    this->borrowDate = borrowDate;
}

QString BorrowInfo::getReturnDate() const {
    return this->returnDate;
}

void BorrowInfo::setReturnDate(const QString &returnDate) {
    this->returnDate = returnDate;
}

bool BorrowInfo::getIsReturned() const {
    return this->isReturned;
}

void BorrowInfo::setIsReturned(bool isReturned) {
    this->isReturned = isReturned;
}

void BorrowInfo::set(int bookId, int userId, const QString &borrowDate, const QString &returnDate, bool isReturned) {
    this->bookId = bookId;
    this->userId = userId;
    this->borrowDate = borrowDate;
    this->returnDate = returnDate;
    this->isReturned = isReturned;
}

bool operator==(const BorrowInfo &lhs, const BorrowInfo &rhs) {
    return lhs.id == rhs.id && lhs.bookId == rhs.bookId && lhs.userId == rhs.userId &&
           lhs.borrowDate == rhs.borrowDate && lhs.returnDate == rhs.returnDate && lhs.isReturned == rhs.isReturned;
}
