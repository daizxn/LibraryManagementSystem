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
#include <memory>
#include <QSharedPointer>
#include "data/RBTree.h"

class Database {
private:
    RedBlackTree<int, QSharedPointer<QJsonObject>> idIndex;  // ID索引：ID -> 数据
    QMap<QString, RedBlackTree<QString, int>> fieldIndexes;  // 字段索引：字段 -> 值 -> ID
    QString dbFile;  // 数据文件路径
    int currentId;  // 当前ID，保证唯一递增

    // 读取当前数据库文件中的数据并构建索引
    void loadDatabase() {
        QFile file(dbFile);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Error opening database file:" << dbFile;
            return;
        }

        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (const auto& item : array) {
                if (item.isObject()) {
                    QJsonObject obj = item.toObject();
                    if (obj.contains("id") && obj["id"].isDouble()) {
                        int id = obj["id"].toInt();
                        QSharedPointer<QJsonObject> dataPtr = QSharedPointer<QJsonObject>::create(obj);
                        idIndex.insert(id, dataPtr);  // ID索引

                        // 为每个字段建立索引
                        for (const QString& key : obj.keys()) {
                            if (!fieldIndexes.contains(key)) {
                                fieldIndexes[key] = RedBlackTree<QString, int>();
                            }
                            fieldIndexes[key].insert(obj[key].toString(), id);
                        }

                        currentId = std::max(currentId, id);  // 更新当前ID
                    }
                }
            }
        }
        file.close();
    }

    // 保存索引到文件
    void saveDatabase() {
        QFile file(dbFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qWarning() << "Error opening database file for writing:" << dbFile;
            return;
        }

        QJsonArray jsonArray;
        QList<QPair<int, QSharedPointer<QJsonObject>>> dataList;
        idIndex.inOrderTraversal(dataList);
        for (const auto& data : dataList) {
            jsonArray.append(*data.second);
        }
        QJsonDocument finalDoc(jsonArray);
        file.write(finalDoc.toJson());
        file.close();
    }

public:
    // 构造函数：初始化时加载数据库
    Database(const QString& databaseFile)
        : dbFile(databaseFile), currentId(0) {
        loadDatabase();
    }

    // 插入数据
    int insertData(const QJsonObject& data) {
        currentId++;  // 递增ID
        QJsonObject newData = data;
        newData["id"] = currentId;  // 设置id字段

        // 将数据插入ID索引
        QSharedPointer<QJsonObject> dataPtr = QSharedPointer<QJsonObject>::create(newData);
        idIndex.insert(currentId, dataPtr);

        // 为每个字段建立索引
        for (const QString& key : newData.keys()) {
            if (!fieldIndexes.contains(key)) {
                fieldIndexes[key] = RedBlackTree<QString, int>();
            }
            fieldIndexes[key].insert(newData[key].toString(), currentId);
        }

        // 保存更新后的数据库文件
        saveDatabase();

        return currentId;  // 返回生成的ID
    }

    // 根据字段查询数据
    QList<QSharedPointer<QJsonObject>> queryByField(const QString& field, const QString& value) {
        QList<QSharedPointer<QJsonObject>> results;
        if (fieldIndexes.contains(field)) {
            std::vector<int> ids = fieldIndexes[field].search(value);
            for (int id : ids) {
                if (idIndex.contains(id)) {
                    results.append(idIndex.search(id).front());
                }
            }
        }
        return results;
    }

    // 根据ID查询数据
    QSharedPointer<QJsonObject> queryById(int id) {
        if (idIndex.contains(id)) {
            return idIndex.search(id).front();
        }
        return nullptr;  // 如果没有找到数据，返回空
    }

    // 修改数据
    bool modifyData(int id, const QJsonObject& newData) {
        if (!idIndex.contains(id)) {
            return false;  // 如果没有找到数据，返回失败
        }

        // 更新ID索引
        QSharedPointer<QJsonObject> updatedDataPtr = QSharedPointer<QJsonObject>::create(newData);
        idIndex.remove(id, idIndex.search(id).front());
        idIndex.insert(id, updatedDataPtr);

        // 更新字段索引
        for (const QString& key : newData.keys()) {
            fieldIndexes[key].remove(newData[key].toString(), id);
            fieldIndexes[key].insert(newData[key].toString(), id);
        }

        // 保存更新后的数据库文件
        saveDatabase();
        return true;
    }

    // 删除数据
    bool deleteData(int id) {
        if (!idIndex.contains(id)) {
            return false;  // 如果没有找到数据，返回失败
        }

        // 删除ID索引
        auto dataPtr = idIndex.search(id).front();
        idIndex.remove(id, dataPtr);

        // 删除字段索引
        for (const QString& key : dataPtr->keys()) {
            fieldIndexes[key].remove((*dataPtr)[key].toString(), id);
        }

        // 保存更新后的数据库文件
        saveDatabase();
        return true;
    }

    // 获取当前数据库的 ID
    int getCurrentId() const {
        return currentId;
    }
};


#endif //DATA_H
