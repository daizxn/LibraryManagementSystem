//
// Created by dai on 24-11-29.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_ADMIN_H
#define LIBRARYMANAGEMENTSYSTEM_ADMIN_H

#include <QString>

class Admin {


private:
    QString username;
    QString password;

public:
    Admin();

    Admin(const QString &username, const QString &password);

    QString getUsername() const;

    void setUsername(const QString &username);

    QString getPassword() const;

    void setPassword(const QString &password);

    friend bool operator==(const Admin &lhs, const Admin &rhs);

};


#endif //LIBRARYMANAGEMENTSYSTEM_ADMIN_H
