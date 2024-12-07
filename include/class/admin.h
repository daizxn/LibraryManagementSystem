//
// Created by dai on 24-11-29.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_ADMIN_H
#define LIBRARYMANAGEMENTSYSTEM_ADMIN_H

#include "enum/AdminEnum.h"

class Admin
{
private:
    int id;
    QString info[AdminEnum::ADMIN_ENUM_COUNT];

public:
    Admin();

    Admin(int id,const QString& username, const QString& password);

    [[nodiscard]] int getId() const;

    void setId(int id);

    [[nodiscard]] QString getInfo(AdminEnum index) const;

    void setInfo(AdminEnum index, const QString& info);

    friend bool operator==(const Admin& lhs, const Admin& rhs);
};


#endif //LIBRARYMANAGEMENTSYSTEM_ADMIN_H
