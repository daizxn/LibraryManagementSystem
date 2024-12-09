//
// Created by dai on 24-12-8.
//

#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QString>
#include <QMap>
#include <QSharedPointer>
#include "data/RBTree.h"

#include "util/normUtil.h"


class Database
{
private:
    RedBlackTree<int, QSharedPointer<QJsonObject>> idIndex; // ID索引：ID -> 数据
    QMap<QString, RedBlackTree<QString, int>> fieldIndexes; // 字段索引：字段 -> 值 -> ID
    QString dbFile; // 数据文件路径
    int currentId; // 当前ID，保证唯一递增

    // 读取当前数据库文件中的数据并构建索引
    void loadDatabase();

    // 保存索引到文件
    void saveDatabase();

    friend QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>> normByField(const QString& field); //数据规范化函数

public:
    // 构造函数：初始化时加载数据库
    explicit Database(QString databaseFile);

    // 插入数据
    int insertData(const QJsonObject& data);

    // 根据字段查询数据
    QList<QSharedPointer<QJsonObject>> queryByField(const QString& field, const QString& value);

    // 根据ID查询数据
    QSharedPointer<QJsonObject> queryById(int id);

    // 查询所有数据
    QList<QSharedPointer<QJsonObject>> queryAll();

    // 修改数据
    bool modifyData(int id, const QJsonObject& newData);

    // 删除数据
    bool deleteData(int id);

    // 获取当前数据库的 ID
    int getCurrentId() const;
};
#endif //DATA_H
