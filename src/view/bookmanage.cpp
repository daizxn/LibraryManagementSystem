//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookManage.h" resolved

#include "bookmanage.h"

#include "Forms/ui_bookmanage.h"


BookManage::BookManage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::BookManage),
    bookDB("../resource/book/bookInfo.json")
{
    ui->setupUi(this);
    init();
}

BookManage::~BookManage()
{
    delete ui;
}

void BookManage::init()
{
    const QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>> bookData = normUtil::normByField(
        "bookName", bookDB.queryAll());
    loadTable(bookData);
}

void BookManage::loadTable(const QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>>& bookData) const
{
    //清空表格
    ui->bookTable->clearContents();
    ui->bookTable->horizontalHeader()->setVisible(false);
    ui->bookTable->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bookTable->horizontalHeader()->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->bookTable->setColumnCount(1);
    ui->bookTable->setRowCount(0);

    for (auto& book : bookData)
    {
        int row = ui->bookTable->rowCount();
        ui->bookTable->insertRow(row);

        auto* schemeDialog = new SchemeDialog(book.second);
        ui->bookTable->setCellWidget(row, 0, schemeDialog);
        ui->bookTable->resizeRowsToContents();

        connect(schemeDialog, &SchemeDialog::folded, [this, row]()
        {
            ui->bookTable->resizeRowToContents(row);
            ui->bookTable->resizeRowToContents(row);
        });
    }
}
