//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BOOK_H
#define LIBRARYMANAGEMENTSYSTEM_BOOK_H


#include "enum/BookEnum.h"

class Book
{
private:
    /*book base info*/
    int id;
    QString name;
    QString author;
    QString isbn;

    /*book borrow info*/
    bool isBorrowed;
    QString info[BookEnum::BOOK_ENUM_COUNT];

public:
    //constructor
    Book();

    Book(int id, const QString& name, const QString& author, const QString& isbn, bool isBorrowed);

    //getter and setter
    int getId() const;

    void setId(int id);

    const QString& getName() const;

    void setName(const QString& name);

    const QString& getAuthor() const;

    void setAuthor(const QString& author);

    const QString& getIsbn() const;

    void setIsbn(const QString& isbn);

    bool getIsBorrowed() const;

    void setIsBorrowed(bool isBorrowed);

    void set(const QString& name, const QString& author, const QString& isbn, bool isBorrowe = false);

    //operator overload
    friend bool operator==(const Book& lhs, const Book& rhs);
};


#endif //LIBRARYMANAGEMENTSYSTEM_BOOK_H
