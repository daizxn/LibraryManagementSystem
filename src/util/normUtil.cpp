//
// Created by dai on 24-12-9.
//

#include "util/normUtil.h"

 QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>> normUtil:: normByField(const QString& field,
                                                                      QList<QSharedPointer<QJsonObject>> data)
{
    QMap<QString, QList<QSharedPointer<QJsonObject>>> temp;
    for (const auto& obj : data)
    {
        if (obj->contains(field))
        {
            QString value = obj->value(field).toString();
            if (!temp.contains(value))
            {
                temp[value] = QList<QSharedPointer<QJsonObject>>();
            }
            temp[value].append(obj);
        }
    }
    QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>> result;
    for (auto it = temp.begin(); it != temp.end(); ++it)
    {
        result.append(qMakePair(it.key(), it.value()));
    }

    return result;
}
