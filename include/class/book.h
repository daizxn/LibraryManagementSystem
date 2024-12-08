//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BOOK_H
#define LIBRARYMANAGEMENTSYSTEM_BOOK_H


#include <QJsonObject>

#include "enum/BookEnum.h"

class Book
{
private:
    /*book base info*/
    int id;

    QString info[BookEnum::BOOK_ENUM_COUNT];

public:
    //constructor
    Book();

    Book(QJsonObject json);

    Book(int id, const QString& name, const QString& author, const QString& isbn, bool isBorrowed);

    QJsonObject toJsonObject() const;
    //getter and setter
    [[nodiscard]] int getId() const;
    void setId(int id);

    [[nodiscard]] QString getInfo(int index) const;
    void setInfo(BookEnum index, const QString& info);

    //operator overload
    friend bool operator==(const Book& lhs, const Book& rhs);
};


#endif //LIBRARYMANAGEMENTSYSTEM_BOOK_H
