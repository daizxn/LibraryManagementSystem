//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookManage.h" resolved

#include "bookmanage.h"

#include "Forms/ui_bookmanage.h"


BookManage::BookManage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::BookManage),
    bookDB("../resource/book/bookInfo.json"),
    modifyIngo(new ModifyIngo(this, &bookDB))
{
    ui->setupUi(this);
    init();

    connect(ui->addButton, &QPushButton::clicked, this, &BookManage::addNewButtonClicked);
    connect(ui->searchLine, &QLineEdit::returnPressed, this, &BookManage::search);
    connect(ui->saveButton, &QPushButton::clicked, this, &BookManage::saveButtonClicked);
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

void BookManage::loadTable(const QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>>& bookData)
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

        auto* schemeDialog = new SchemeDialog(book.second, &bookDB, this, modifyIngo);
        ui->bookTable->setCellWidget(row, 0, schemeDialog);
        ui->bookTable->resizeRowsToContents();
        disconnect(schemeDialog, &SchemeDialog::folded, nullptr, nullptr);
        connect(schemeDialog, &SchemeDialog::folded, [this, row]()
        {
            ui->bookTable->resizeRowsToContents();

        });
        disconnect(schemeDialog, &SchemeDialog::bookChanged, nullptr, nullptr);
        connect(schemeDialog, &SchemeDialog::bookChanged, [this]()
        {
            init();
        });
    }
}

void BookManage::addNewButtonClicked()
{
    QJsonObject param;
    param.insert("id", "-1");
    modifyIngo->setParam(param);
    modifyIngo->init(ModifyIngo::AddModel);
    modifyIngo->show();
    disconnect(modifyIngo, &ModifyIngo::modifyInfo, nullptr, nullptr);
    connect(modifyIngo, &ModifyIngo::modifyInfo, [this]()
    {
        init();
    });
}

void BookManage::search()
{
    QString key = ui->searchLine->text();
    if (key.isEmpty())
    {
        init();
        return;
    }
    const QList<QPair<QString, QList<QSharedPointer<QJsonObject>>>> bookData = normUtil::normByField(
        "bookName", bookDB.queryByValue(key));
    loadTable(bookData);
}

void BookManage::saveButtonClicked()
{
    bookDB.saveDatabase();
}
