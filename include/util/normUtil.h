//
// Created by dai on 24-12-9.
//

#ifndef NORMUTIL_H
#define NORMUTIL_H

#include <QJsonObject>

class normUtil {
public:
  static QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>> normByField(const QString& field, QList<QSharedPointer<QJsonObject>> data);//数据规范化函数
};



#endif //NORMUTIL_H
