//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BORROWINFO_H
#define LIBRARYMANAGEMENTSYSTEM_BORROWINFO_H


#include "enum/BorrowInfoEnum.h"

class BorrowInfo
{
private:
    int id;
    int bookId;
    int userId;
    QString borrowDate;
    QString returnDate;
    bool isReturned;
    QString info[BorrowInfoEnum::BORROWINFO_ENUM_COUNT];

public:
    // constructor
    BorrowInfo();

    BorrowInfo(int id, int bookId, int userId, const QString& borrowDate, const QString& returnDate, bool isReturned);

    // getter and setter
    int getId() const;

    void setId(int id);

    int getBookId() const;

    void setBookId(int bookId);

    int getUserId() const;

    void setUserId(int userId);

    QString getBorrowDate() const;

    void setBorrowDate(const QString& borrowDate);

    QString getReturnDate() const;

    void setReturnDate(const QString& returnDate);

    bool getIsReturned() const;

    void setIsReturned(bool isReturned);

    void set(int bookId, int userId, const QString& borrowDate, const QString& returnDate, bool isReturned);

    // operator overload
    friend bool operator==(const BorrowInfo& lhs, const BorrowInfo& rhs);
};

#endif // LIBRARYMANAGEMENTSYSTEM_BORROWINFO_H
