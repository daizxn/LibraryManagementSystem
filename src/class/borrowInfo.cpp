//
// Created by dai on 24-12-1.
//

#include "class/borrowInfo.h"

BorrowInfo::BorrowInfo()
{
    this->id = -1;
    for (auto i : this->info)
    {
        i = "null";
    }
}

BorrowInfo::BorrowInfo(int id, int bookId, int userId, const QString& borrowDate, const QString& returnDate,
                       bool isReturned)
{
    this->id = id;
    this->info[BorrowInfoEnum::BORROWINFO_BOOKID] = QString::number(bookId);
    this->info[BorrowInfoEnum::BORROWINFO_USERID] = QString::number(userId);
    this->info[BorrowInfoEnum::BORROWINFO_BORROWDATE] = borrowDate;
    this->info[BorrowInfoEnum::BORROWINFO_RETURNDATE] = returnDate;
    this->info[BorrowInfoEnum::BORROWINFO_ISRETURNED] = isReturned ? "true" : "false";
}

BorrowInfo::BorrowInfo(QJsonObject obj)
{
    this->id=obj["id"].toInt();
    this->info[BorrowInfoEnum::BORROWINFO_BOOKID]=QString::number(obj["bookId"].toInt());
    this->info[BorrowInfoEnum::BORROWINFO_USERID]=QString::number(obj["userId"].toInt());
    this->info[BorrowInfoEnum::BORROWINFO_BORROWDATE]=obj["borrowDate"].toString();
    this->info[BorrowInfoEnum::BORROWINFO_RETURNDATE]=obj["returnDate"].toString();
    this->info[BorrowInfoEnum::BORROWINFO_ISRETURNED]=obj["isReturned"].toBool()?"true":"false";

}


int BorrowInfo::getId() const
{
    return this->id;
}

void BorrowInfo::setId(int id)
{
    this->id = id;
}

QString BorrowInfo::getInfo(int index) const
{
    return this->info[index];
}

void BorrowInfo::setInfo(BorrowInfoEnum index, const QString& info)
{
    this->info[index] = info;
}

bool operator==(const BorrowInfo& lhs, const BorrowInfo& rhs)
{
    if (lhs.id!=rhs.id)
    {
        return false;
    }
    for (int i = 0; i < BorrowInfoEnum::BORROWINFO_ENUM_COUNT; i++)
    {
        if (lhs.info[i] != rhs.info[i])
        {
            return false;
        }
    }
    return true;
}

