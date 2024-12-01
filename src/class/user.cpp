//
// Created by dai on 24-12-1.
//

#include "user.h"

User::User() {
    this->id = -1;
    this->username = "null";
    this->password = "null";
}

User::User(int id, const QString &username, const QString &password) {
    this->id = id;
    this->username = username;
    this->password = password;
}

int User::getId() const {
    return this->id;
}

void User::setId(int id) {
    this->id = id;
}

const QString &User::getUsername() const {
    return this->username;
}

void User::setUsername(const QString &username) {
    this->username = username;
}

const QString &User::getPassword() const {
    return this->password;
}

void User::setPassword(const QString &password) {
    this->password = password;
}

void User::set(const QString &username, const QString &password) {
    this->username = username;
    this->password = password;
}

bool operator==(const User &lhs, const User &rhs) {
    return lhs.username == rhs.username && lhs.password == rhs.password;
}