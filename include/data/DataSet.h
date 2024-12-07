#ifndef LIBRARYMANAGEMENTSYSTEM_DATASET_H
#define LIBRARYMANAGEMENTSYSTEM_DATASET_H

#include <QFile>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <stdexcept>
#include <map>
#include <vector>
#include "AVLTree.h"

// 假设数据类 T 有一个构造函数，该构造函数接受一个 QJsonObject 来构造数据对象。
template <typename T>
class DataSet
{
private:
    int infoCount;
    AVLTree<int, T> tree; // 存储id为键的数据
    std::multimap<QString, int>* reverseLookup; // 根据其他字段反查多个id

public:
    DataSet(const QString& filePath, const int infoCount);

    void insert(const T& data);

    void remove(int id);

    void update(int id, const T& data);

    void removeByField(int field, const QString& value);

    //void updateByField(int field, const QString& value, const T& data);


    T* getById(int id);
    std::vector<int> getIdsByField(int field, const QString& value) const; // 查找所有匹配的id

    QList<T> getByField(int field, const QString& value);
};

template <typename T>
DataSet<T>::DataSet(const QString& filePath, const int infoCount)
{
    this->infoCount = infoCount;
    this->reverseLookup = new std::multimap<QString, int>[infoCount]; // 创建反查表
    // 打开并读取文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw std::runtime_error("File not found");
    }

    QTextStream reader(&file);
    reader.setEncoding(QStringConverter::Encoding::Utf8);
    QString fileData = reader.readAll();
    file.close();

    // 解析json数据
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileData.toUtf8());
    if (jsonError.error != QJsonParseError::NoError)
    {
        throw std::runtime_error("Failed to parse JSON data");
    }

    QJsonObject jsonObject = jsonDocument.object();
    if (jsonObject.contains("data") && jsonObject["data"].isArray())
    {
        QJsonArray dataArray = jsonObject["data"].toArray();

        for (auto dataValue : dataArray)
        {
            QJsonObject dataObj = dataValue.toObject();

            // 从数据对象中提取id
            int id = dataObj["id"].toInt();

            // 构造数据对象 T
            T data = T(dataObj);

            // 将数据插入到树中
            tree.insert(id, data);

            for (int i = 0; i < infoCount; i++)
            {
                // 将其他字段的值插入到反查表中
                reverseLookup[i].insert({data.getInfo(i), id});
            }
        }
    }
}

template <typename T>
T* DataSet<T>::getById(int id)
{
    return tree.search(id); // 从树中查找 id 对应的数据
}

template <typename T>
std::vector<int> DataSet<T>::getIdsByField(const int field, const QString& value) const
{
    std::vector<int> ids;

    const auto [fst, snd] = reverseLookup[field].equal_range(value); // 获取所有匹配的 id
    for (auto it = fst; it != snd; ++it)
    {
        ids.push_back(it->second); // 将所有找到的id存入vector
    }

    return ids; // 返回所有匹配的id
}

template <typename T>
QList<T> DataSet<T>:: getByField(int field, const QString& value)
{
    std::vector<int> ids = getIdsByField(field, value);
    QList<T> result;
    for (int id : ids) {
        result.append(*getById(id));
    }
    return result;
}

template <typename T>
void DataSet<T>::insert(const T& data)
{
    int id = data.getId();
    tree.insert(id, data); // 将数据插入到树中

    for (int i = 0; i < infoCount; i++)
    {
        reverseLookup[i].insert({data.getInfo(i), id}); // 将其他字段的值插入到反查表中
    }
}

template <typename T>
void DataSet<T>::remove(int id)
{
    T* data = tree.search(id); // 从树中查找 id 对应的数据
    if (data == nullptr)
    {
        return;
    }

    tree.remove(id); // 从树中删除数据

    for (int i = 0; i < infoCount; i++)
    {
        // 从反查表中删除数据
        auto range = reverseLookup[i].equal_range(data->getInfo(i));
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == id)
            {
                reverseLookup[i].erase(it);
                break;
            }
        }
    }
}

template <typename T>
void DataSet<T>::update(int id, const T& data)
{
    T* oldData = tree.search(id); // 从树中查找 id 对应的数据
    if (oldData == nullptr)
    {
        return;
    }

    tree.remove(id); // 从树中删除旧数据
    tree.insert(id, data); // 将新数据插入到树中

    for (int i = 0; i < infoCount; i++)
    {
        // 从反查表中删除旧数据
        auto range = reverseLookup[i].equal_range(oldData->getInfo(i));
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == id)
            {
                reverseLookup[i].erase(it);
                break;
            }
        }

        // 将新数据插入到反查表中
        reverseLookup[i].insert({data.getInfo(i), id});
    }
}

template <typename T>
void DataSet<T>::removeByField(int field, const QString& value)
{
    std::vector<int> ids = getIdsByField(field, value); // 获取所有匹配的id
    for (int id : ids)
    {
        remove(id); // 删除所有匹配的数据
    }
}

template <typename T>
/*void DataSet<T>::updateByField(int field, const QString& value, const T& data)
{
    std::vector<int> ids = getIdsByField(field, value); // 获取所有匹配的id
    for (int id : ids)
    {
        update(id, data); // 更新所有匹配的数据
    }
}*/
#endif // LIBRARYMANAGEMENTSYSTEM_DATASET_H
