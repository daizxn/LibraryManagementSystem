//
// Created by dai on 24-12-1.
//

#include "class/user.h"

User::User() {
    this->id = -1;
    this->info[UserEnum::USER_NAME] = "null";
    this->info[UserEnum::USER_PASSWORD] = "null";
}

User::User(QJsonObject obj) {
    this->id = obj["id"].toInt();
    this->info[UserEnum::USER_NAME] = obj["username"].toString();
    this->info[UserEnum::USER_PASSWORD] = obj["password"].toString();
}

User::User(int id, const QString &username, const QString &password) {
    this->id = id;
    this->info[UserEnum::USER_NAME] = username;
    this->info[UserEnum::USER_PASSWORD] = password;
}

int User::getId() const {
    return this->id;
}

void User::setId(int id) {
    this->id = id;
}

QString User::getInfo(int index) const {
    return this->info[index];
}

void User::setInfo(UserEnum index, const QString &info) {
    this->info[index] = info;
}

bool operator==(const User &lhs, const User &rhs) {
    if (lhs.id != rhs.id) {
        return false;
    }
    for (int i = 0; i < UserEnum::USER_ENUM_COUNT; i++) {
        if (lhs.info[i] != rhs.info[i]) {
            return false;
        }
    }
    return true;
}