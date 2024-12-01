//
// Created by dai on 24-11-29.
//

#include "admin.h"

Admin::Admin() {
    this->username = "";
    this->password = "";
}

Admin::Admin(const QString &username, const QString &password) {
    this->username = username;
    this->password = password;
}

QString Admin::getUsername() const {
    return this->username;
}

void Admin::setUsername(const QString &username) {
    this->username = username;
}

QString Admin::getPassword() const {
    return this->password;
}

void Admin::setPassword(const QString &password) {
    this->password = password;
}

bool operator==(const Admin &lhs, const Admin &rhs) {
    return lhs.username == rhs.username && lhs.password == rhs.password;
}