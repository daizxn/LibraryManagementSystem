//
// Created by dai on 24-12-3.
//

#ifndef ADMINENUM_H
#define ADMINENUM_H

#include <QString>

enum AdminEnum
{
    ADMIN_NAME = 0,
    ADMIN_PASSWORD,
    ADMIN_ENUM_COUNT
};

extern const QString AdminEnumString[ADMIN_ENUM_COUNT];


#endif //ADMINENUM_H