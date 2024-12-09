//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookManage.h" resolved

#include "bookmanage.h"

#include "Forms/ui_bookmanage.h"


BookManage::BookManage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::BookManage),
    bookDB("../resources/book/bookInfo.json")
{
    ui->setupUi(this);
}

BookManage::~BookManage()
{
    delete ui;
}

void BookManage::init()
{
    QList<QPair<QString,QList<QSharedPointer<QJsonObject>>>> bookData = normUtil::normByField("bookName",bookDB.queryAll());
    loadTable(bookData);
}

void BookManage::loadTable(const QList<QPair<QString,QList<QSharedPointer<QJsonObject>>>>& bookData)
{
    //清空表格
    ui->bookTable->clearContents();
    ui->bookTable->horizontalHeader()->setVisible(false);
    ui->bookTable->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bookTable->horizontalHeader()->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->bookTable->setColumnCount(1);
    ui->bookTable->setRowCount(0);

    for (auto &book : bookData)
    {
        
    }

}
