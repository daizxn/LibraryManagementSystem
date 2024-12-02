//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_USER_H
#define LIBRARYMANAGEMENTSYSTEM_USER_H

#include <QString>

class User {
private:
    int id;
    QString username;
    QString password;

public:
    //constructor
    User();

    User(int id, const QString &username, const QString &password);

    //getter and setter
    int getId() const;

    void setId(int id);

    const QString &getUsername() const;

    void setUsername(const QString &username);

    const QString &getPassword() const;

    void setPassword(const QString &password);

    void set(const QString &username, const QString &password);

    //operator overload
    friend bool operator==(const User &lhs, const User &rhs);
};


#endif //LIBRARYMANAGEMENTSYSTEM_USER_H
