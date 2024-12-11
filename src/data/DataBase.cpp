//
// Created by dai on 24-12-9.
//

#include "data/DataBase.h"

Database::Database(QString databaseFile)
    : dbFile(std::move(databaseFile)), currentId(0)
{
    loadDatabase();
}

void Database::loadDatabase()
{
    QFile file(dbFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Error opening database file:" << dbFile;
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isArray())
    {
        QJsonArray array = doc.array();
        for (const auto& item : array)
        {
            if (item.isObject())
            {
                QJsonObject obj = item.toObject();
                if (obj.contains("id") && obj["id"].isDouble())
                {
                    int id = obj["id"].toInt();
                    QSharedPointer<QJsonObject> dataPtr = QSharedPointer<QJsonObject>::create(obj);
                    idIndex.insert(id, dataPtr); // ID索引

                    // 为每个字段建立索引
                    for (const QString& key : obj.keys())
                    {
                        if (!fieldIndexes.contains(key))
                        {
                            fieldIndexes[key] = RedBlackTree<QString, int>();
                        }
                        fieldIndexes[key].insert(obj[key].toString(), id);
                    }

                    currentId = std::max(currentId, id); // 更新当前ID
                }
            }
        }
    }
    file.close();
}

void Database::saveDatabase()
{
    QFile file(dbFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qWarning() << "Error opening database file for writing:" << dbFile;
        return;
    }

    QJsonArray jsonArray;
    QList<QPair<int, QSharedPointer<QJsonObject>>> dataList;
    idIndex.inOrderTraversal(dataList);
    for (const auto& data : dataList)
    {
        jsonArray.append(*data.second);
    }
    QJsonDocument finalDoc(jsonArray);
    file.write(finalDoc.toJson());
    file.close();
}

int Database::insertData(const QJsonObject& data)
{
    currentId++; // 递增ID
    QJsonObject newData = data;
    newData["id"] = currentId; // 设置id字段

    // 将数据插入ID索引
    QSharedPointer<QJsonObject> dataPtr = QSharedPointer<QJsonObject>::create(newData);
    idIndex.insert(currentId, dataPtr);

    // 为每个字段建立索引
    for (const QString& key : newData.keys())
    {
        if (!fieldIndexes.contains(key))
        {
            fieldIndexes[key] = RedBlackTree<QString, int>();
        }
        fieldIndexes[key].insert(newData[key].toString(), currentId);
    }

    // 保存更新后的数据库文件
    saveDatabase();

    return currentId; // 返回生成的ID
}

QList<QSharedPointer<QJsonObject>> Database::queryByField(const QString& field, const QString& value)
{
    QList<QSharedPointer<QJsonObject>> results;
    if (fieldIndexes.contains(field))
    {
        std::vector<int> ids = fieldIndexes[field].search(value);
        for (int id : ids)
        {
            results.append(idIndex.search(id).front());
        }
    }
    return results;
}

QSharedPointer<QJsonObject> Database::queryById(const int id)
{
    auto result = idIndex.search(id);
    if (result.empty())
    {
        return nullptr;
    }
    return result.front();
}

QList<QSharedPointer<QJsonObject>> Database::queryAll()
{
    QList<QSharedPointer<QJsonObject>> results;
    QList<QPair<int, QSharedPointer<QJsonObject>>> dataList;
    idIndex.inOrderTraversal(dataList);
    for (const auto& [fst, snd] : dataList)
    {
        results.append(snd);
    }
    return results;
}

QList<QSharedPointer<QJsonObject>> Database::queryByValue(const QString& value)
{
    QList<QSharedPointer<QJsonObject>> results;
    std::vector<int> resultIds;
    for (auto& tree : fieldIndexes)
    {

            std::vector<int> ids = tree.search(value);
            resultIds.insert(resultIds.end(), ids.begin(), ids.end());

    }
    std::unique(resultIds.begin(), resultIds.end());
    for (auto id : resultIds)
    {
        results.append(idIndex.search(id).front());
    }
    return results;
}


bool Database::modifyData(const int id, const QJsonObject& newData)
{
    if (!idIndex.contains(id))
    {
        return false; // 如果没有找到数据，返回失败
    }

    // 更新ID索引
    QSharedPointer<QJsonObject> updatedDataPtr = QSharedPointer<QJsonObject>::create(newData);
    idIndex.remove(id, idIndex.search(id).front());
    idIndex.insert(id, updatedDataPtr);

    // 更新字段索引
    for (const QString& key : newData.keys())
    {
        fieldIndexes[key].remove(newData[key].toString(), id);
        fieldIndexes[key].insert(newData[key].toString(), id);
    }

    // 保存更新后的数据库文件
    saveDatabase();
    return true;
}

bool Database::deleteData(const int id)
{
    if (!idIndex.contains(id))
    {
        return false; // 如果没有找到数据，返回失败
    }

    // 删除ID索引
    auto dataPtr = idIndex.search(id).front();
    idIndex.remove(id, dataPtr);

    // 删除字段索引
    for (const QString& key : dataPtr->keys())
    {
        fieldIndexes[key].remove((*dataPtr)[key].toString(), id);
    }

    // 保存更新后的数据库文件
    saveDatabase();
    return true;
}

int Database::getCurrentId() const
{
    return currentId;
}
