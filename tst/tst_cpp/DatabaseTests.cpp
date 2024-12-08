//
// Created by dai on 24-12-8.
//

#include <gtest/gtest.h>
#include "data/DataBase.h"

TEST(DatabaseTests, InsertData) {
    Database db("test_db.json");
    QJsonObject data;
    data["name"] = "John Doe";
    int id = db.insertData(data);
    auto result = db.queryById(id);
    ASSERT_TRUE(result != nullptr);
    ASSERT_EQ(result->value("name").toString(), "John Doe");
}

TEST(DatabaseTests, QueryByField) {
    Database db("test_db.json");
    QJsonObject data1;
    data1["name"] = "John Doe";
    db.insertData(data1);
    QJsonObject data2;
    data2["name"] = "Jane Doe";
    db.insertData(data2);
    auto results = db.queryByField("name", "Jane Doe");
    ASSERT_EQ(results.size(), 1);
    ASSERT_EQ(results[0]->value("name").toString(), "Jane Doe");
}

TEST(DatabaseTests, ModifyData) {
    Database db("test_db.json");
    QJsonObject data;
    data["name"] = "John Doe";
    int id = db.insertData(data);
    QJsonObject newData;
    newData["name"] = "John Smith";
    bool modified = db.modifyData(id, newData);
    ASSERT_TRUE(modified);
    auto result = db.queryById(id);
    ASSERT_TRUE(result != nullptr);
    ASSERT_EQ(result->value("name").toString(), "John Smith");
}

TEST(DatabaseTests, DeleteData) {
    Database db("test_db.json");
    QJsonObject data;
    data["name"] = "John Doe";
    int id = db.insertData(data);
    bool deleted = db.deleteData(id);
    ASSERT_TRUE(deleted);
    auto result = db.queryById(id);
    ASSERT_TRUE(result == nullptr);
}

TEST(DatabaseTests, InsertAndQueryMultipleData) {
    Database db("test_db.json");
    QJsonObject data1;
    data1["name"] = "John Doe";
    int id1 = db.insertData(data1);
    QJsonObject data2;
    data2["name"] = "Jane Doe";
    int id2 = db.insertData(data2);
    auto result1 = db.queryById(id1);
    auto result2 = db.queryById(id2);
    ASSERT_TRUE(result1 != nullptr);
    ASSERT_EQ(result1->value("name").toString(), "John Doe");
    ASSERT_TRUE(result2 != nullptr);
    ASSERT_EQ(result2->value("name").toString(), "Jane Doe");
}

TEST(DatabaseTests, QueryNonExistentField) {
    Database db("test_db.json");
    auto results = db.queryByField("nonexistent", "value");
    ASSERT_TRUE(results.isEmpty());
}

TEST(DatabaseTests, ModifyNonExistentData) {
    Database db("test_db.json");
    QJsonObject newData;
    newData["name"] = "John Smith";
    bool modified = db.modifyData(999, newData);
    ASSERT_FALSE(modified);
}

TEST(DatabaseTests, DeleteNonExistentData) {
    Database db("test_db.json");
    bool deleted = db.deleteData(999);
    ASSERT_FALSE(deleted);
}