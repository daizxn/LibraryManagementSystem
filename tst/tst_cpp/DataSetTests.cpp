//
// Created by dai on 24-12-7.
//
#include <gtest/gtest.h>
#include "data/DataSet.h"
#include "class/book.h"

TEST(DataSetTests, GetById) {
    DataSet<Book> dataSet(":book/book/bookInfo.json", BookEnum::BOOK_ENUM_COUNT);
    Book *book = dataSet.getById(1);
    ASSERT_EQ(book->getId(), 1);
    ASSERT_EQ(book->getInfo(BookEnum::BOOK_NAME), "C++ Primer");
    ASSERT_EQ(book->getInfo(BookEnum::BOOK_AUTHOR), "Stanley B. Lippman");
    ASSERT_EQ(book->getInfo(BookEnum::BOOK_ISBN), "978-7-121-15535-2");
    ASSERT_EQ(book->getInfo(BookEnum::BOOK_ISBORROWED), "false");
}

TEST(DataSetTests, GetIdsByField) {
    DataSet<Book> dataSet(":book/book/bookInfo.json", BookEnum::BOOK_ENUM_COUNT);
    std::vector<int> ids = dataSet.getIdsByField(BookEnum::BOOK_ISBORROWED, "false");
    ASSERT_EQ(ids.size(), 3);
    ASSERT_EQ(ids[0], 1);
}

TEST(DataSetTests, Insert) {
    DataSet<Book> dataSet(":book/book/bookInfo.json", BookEnum::BOOK_ENUM_COUNT);
    Book book(4, "C++ Primer", "Stanley B. Lippman", "978-7-121-15535-2", false);
    dataSet.insert(book);
    Book *book1 = dataSet.getById(4);
    ASSERT_EQ(book1->getId(), 4);
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_NAME), "C++ Primer");
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_AUTHOR), "Stanley B. Lippman");
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_ISBN), "978-7-121-15535-2");
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_ISBORROWED), "false");
    QList<Book> books = dataSet.getByField(BookEnum::BOOK_ISBORROWED, "false");
    ASSERT_EQ(books.size(), 4);
    QList<Book> books1 = dataSet.getByField(BookEnum::BOOK_NAME, "C++ Primer");
    ASSERT_EQ(books1.size(), 2);

}

TEST(DataSetTests, Remove) {
    DataSet<Book> dataSet(":book/book/bookInfo.json", BookEnum::BOOK_ENUM_COUNT);
    dataSet.remove(1);
    Book book1(4, "C++ Primer", "Stanley B. Lippman", "978-7-121-15535-2", false);
    dataSet.insert(book1);
    Book *book = dataSet.getById(1);
    ASSERT_EQ(book, nullptr);
    std::vector<int> ids = dataSet.getIdsByField(BookEnum::BOOK_ISBORROWED, "false");
    ASSERT_EQ(ids.size(), 3);
    QList<Book> books = dataSet.getByField(BookEnum::BOOK_NAME, "C++ Primer");
    ASSERT_EQ(books.size(), 1);
    dataSet.removeByField(BookEnum::BOOK_ISBORROWED, "false");
    QList<Book> books1 = dataSet.getByField(BookEnum::BOOK_ISBORROWED, "false");
    ASSERT_EQ(books1.size(), 0);
}

TEST(DataSetTests, Update) {
    DataSet<Book> dataSet(":book/book/bookInfo.json", BookEnum::BOOK_ENUM_COUNT);
    Book book(1, "bool", "Stanley B. Lippman", "978-7-121-15535-2", true);
    dataSet.update(book.getId(),book);
    Book *book1 = dataSet.getById(1);
    ASSERT_EQ(book1->getId(), 1);
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_NAME), "bool");
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_AUTHOR), "Stanley B. Lippman");
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_ISBN), "978-7-121-15535-2");
    ASSERT_EQ(book1->getInfo(BookEnum::BOOK_ISBORROWED), "true");
}


