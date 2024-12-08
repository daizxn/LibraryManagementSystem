//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BORROWINFO_H
#define LIBRARYMANAGEMENTSYSTEM_BORROWINFO_H


#include <QJsonObject>

#include "enum/BorrowInfoEnum.h"

class BorrowInfo
{
private:
    int id;
    QString info[BorrowInfoEnum::BORROWINFO_ENUM_COUNT];

public:
    // constructor
    BorrowInfo();

    BorrowInfo(QJsonObject obj);

    BorrowInfo(int id, int bookId, int userId, const QString& borrowDate, const QString& returnDate, bool isReturned);

    // getter and setter
    [[nodiscard]] int getId() const;
    void setId(int id);

    [[nodiscard]] QString getInfo(int index) const;
    void setInfo(BorrowInfoEnum index, const QString& info);

    // operator overload
    friend bool operator==(const BorrowInfo& lhs, const BorrowInfo& rhs);
};

#endif // LIBRARYMANAGEMENTSYSTEM_BORROWINFO_H
