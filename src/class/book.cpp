//
// Created by dai on 24-12-1.
//

#include "class/book.h"

Book::Book() {
    this->id = -1;
    for (auto i : this->info) {
        i = "null";
    }
}

Book::Book(QJsonObject obj)
{
    this->id=obj["id"].toInt();
    this->info[BookEnum::BOOK_NAME]=obj["name"].toString();
    this->info[BookEnum::BOOK_AUTHOR]=obj["author"].toString();
    this->info[BookEnum::BOOK_ISBN]=obj["isbn"].toString();
    this->info[BookEnum::BOOK_ISBORROWED]=obj["isBorrowed"].toBool()?"true":"false";


}


Book::Book(int id, const QString &name, const QString &author, const QString &isbn, bool isBorrowed) {
    this->id = id;
    this->info[BookEnum::BOOK_NAME] = name;
    this->info[BookEnum::BOOK_AUTHOR] = author;
    this->info[BookEnum::BOOK_ISBN] = isbn;
    this->info[BookEnum::BOOK_ISBORROWED] = isBorrowed ? "true" : "false";

}

QJsonObject Book::toJsonObject() const {
    QJsonObject obj;
    obj["id"]=this->id;
    obj["name"]=this->info[BookEnum::BOOK_NAME];
    obj["author"]=this->info[BookEnum::BOOK_AUTHOR];
    obj["isbn"]=this->info[BookEnum::BOOK_ISBN];
    obj["isBorrowed"]=this->info[BookEnum::BOOK_ISBORROWED]=="true";
    return obj;
}

int Book::getId() const {
    return this->id;
}

void Book::setId(int id) {
    this->id = id;
}

QString Book::getInfo(int index) const
{
    return this->info[index];
}
void Book::setInfo(BookEnum index, const QString &info)  {
     this->info[index]=info;
}

bool operator==(const Book &lhs, const Book &rhs) {
    if (lhs.id != rhs.id) {
        return false;
    }
    for (int i = 0; i < BookEnum::BOOK_ENUM_COUNT; i++) {
        if (lhs.info[i] != rhs.info[i]) {
            return false;
        }
    }
    return true;
}

