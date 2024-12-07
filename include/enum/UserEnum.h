//
// Created by dai on 24-12-3.
//

#ifndef USERENUM_H
#define USERENUM_H


#include <QString>

enum UserEnum
{
    USER_ID = 0,
    USER_NAME,
    USER_PASSWORD,
    USER_ENUM_COUNT
};

extern const QString UserEnumString[USER_ENUM_COUNT];


#endif //USERENUM_H
