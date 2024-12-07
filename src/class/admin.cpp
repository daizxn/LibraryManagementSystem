//
// Created by dai on 24-11-29.
//

#include "class/admin.h"

Admin::Admin()
{
    id = -1;
    this->info[AdminEnum::ADMIN_NAME] = "";
    this->info[AdminEnum::ADMIN_PASSWORD] = "";
}

Admin::Admin(const int id, const QString& username, const QString& password)
{
    this->id = id;
    this->info[AdminEnum::ADMIN_NAME] = username;
    this->info[AdminEnum::ADMIN_PASSWORD] = password;
}

QString Admin::getInfo(AdminEnum index) const
{
    return this->info[index];
}

void Admin::setInfo(AdminEnum index, const QString& info)
{
    this->info[index] = info;
}

bool operator==(const Admin& lhs, const Admin& rhs)
{
    return lhs.info[AdminEnum::ADMIN_NAME] == rhs.info[AdminEnum::ADMIN_NAME] && lhs.info[AdminEnum::ADMIN_PASSWORD] ==
        rhs.info[AdminEnum::ADMIN_PASSWORD];
}
