//
// Created by dai on 24-12-3.
//

#ifndef BOOKENUM_H
#define BOOKENUM_H

#include <QString>

enum BookEnum {
    BOOK_ID = 0,
    BOOK_NAME,
    BOOK_AUTHOR,
    BOOK_ISBN,
    BOOK_ISBORROWED,
    BOOK_ENUM_COUNT
};

extern const QString BookEnumString[BOOK_ENUM_COUNT];


#endif //BOOKENUM_H
