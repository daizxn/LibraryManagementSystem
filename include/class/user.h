//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_USER_H
#define LIBRARYMANAGEMENTSYSTEM_USER_H

#include <QJsonObject>

#include "enum/UserEnum.h"

class User
{
private:
    int id;
    QString info[UserEnum::USER_ENUM_COUNT];

public:
    //constructor
    User();

    User(QJsonObject obj);

    User(int id, const QString& username, const QString& password);

    //getter and setter
    [[nodiscard]] int getId() const;
    void setId(int id);

    [[nodiscard]] QString getInfo(int index) const;
    void setInfo(UserEnum index, const QString& info);


    //operator overload
    friend bool operator==(const User& lhs, const User& rhs);
};


#endif //LIBRARYMANAGEMENTSYSTEM_USER_H
