//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookManage.h" resolved

#include "bookmanage.h"

#include <QMessageBox>

#include "Forms/ui_bookmanage.h"


BookManage::BookManage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::BookManage),
    bookModel(new QStandardItemModel(this)),
    bookInfoDialog(new BookInfoDialog(this)),
    bookDataSet(DataSet<Book>(":book/book/bookInfo.json", 4))
{
    ui->setupUi(this);
    ui->bookTable->setModel(bookModel);
    initTable();
    queryLoad();

    connect(ui->addButton, &QPushButton::clicked, this, &BookManage::addBtnClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &BookManage::saveBtnClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &BookManage::editBtnClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &BookManage::deleteBtnClicked);
    connect(ui->searchLine,&QLineEdit::returnPressed,this,&BookManage::query);
}

BookManage::~BookManage()
{
    delete ui;
}

void BookManage::initTable()
{
    //设置表格选中时为整行选中
    ui->bookTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置表头
    bookModel->setHorizontalHeaderLabels(QStringList() << "ID" << "书名" << "作者" << "ISBN" << "是否借出" << "操作");
    //设置表格数据
    QList<Book> bookList = bookDataSet.getAll();
    for (int i = 0; i < bookList.size(); i++)
    {
        const Book& book = bookList.at(i);
        QStandardItem* idItem = new QStandardItem(QString::number(book.getId()));
        QStandardItem* nameItem = new QStandardItem(book.getInfo(BookEnum::BOOK_NAME));
        QStandardItem* authorItem = new QStandardItem(book.getInfo(BookEnum::BOOK_AUTHOR));
        QStandardItem* isbnItem = new QStandardItem(book.getInfo(BookEnum::BOOK_ISBN));
        QStandardItem* isBorrowedItem = new QStandardItem(book.getInfo(BookEnum::BOOK_ISBORROWED));

        bookModel->setItem(i, 0, idItem);
        bookModel->setItem(i, 1, nameItem);
        bookModel->setItem(i, 2, authorItem);
        bookModel->setItem(i, 3, isbnItem);
        bookModel->setItem(i, 4, isBorrowedItem);


        QPushButton* delBtn = new QPushButton("删除");
        QPushButton* editBtn = new QPushButton("编辑");

        delBtn->setProperty("id", book.getId());
        editBtn->setProperty("id", book.getId());

        delBtn->setFixedSize(60, 25);
        editBtn->setFixedSize(60, 25);

        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addWidget(delBtn);
        hLayout->addWidget(editBtn);
        hLayout->setAlignment(Qt::AlignCenter);
        hLayout->setContentsMargins(5, 0, 5, 0);
        QWidget* widget = new QWidget();
        widget->setLayout(hLayout);
        widget->setContentsMargins(0, 0, 0, 0);
        ui->bookTable->setIndexWidget(bookModel->index(i, 5), widget);

        connect(delBtn, &QPushButton::clicked, this, [=]
        {
            deleteBook(delBtn->property("id").toInt());
        });
        connect(editBtn, &QPushButton::clicked, this, [=]
        {
            editBook(editBtn->property("id").toInt(), book);
        });
    }


    //设置表格的列宽
    QHeaderView* header = ui->bookTable->horizontalHeader();
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    for (int i = 0; i < 5; i++)
    {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    header->setFixedHeight(40);
}

void BookManage::loadTable()
{
    bookModel->clear();
    initTable();
}

void BookManage::queryLoad()
{
    ui->searchLine->clear();
}

void BookManage::addBtnClicked()
{
    bookInfoDialog->setFlag(false);
    bookInfoDialog->init(&bookDataSet);
    bookInfoDialog->exec();
    this->loadTable();
}

void BookManage::saveBtnClicked() const
{
    bookDataSet.saveToFile("../resource/book/bookInfo.json");
}

void BookManage::deleteBook(const int id)
{
    bookDataSet.remove(id);
    this->loadTable();
}

void BookManage::editBook(const int id, const Book& book)
{
    bookInfoDialog->setFlag(true);
    bookInfoDialog->setParam(book);
    bookInfoDialog->init(&bookDataSet);
    bookInfoDialog->exec();
    this->loadTable();
}

void BookManage::editBtnClicked()
{
    QItemSelectionModel* selections = ui->bookTable->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if (selected.empty())
    {
        QMessageBox::warning(this, "警告", "请选择一行");
        return;
    }
    int row = selected.at(0).row();
    int id = bookModel->item(row, 0)->text().toInt();
    Book param = *bookDataSet.getById(id);
    bookInfoDialog->setFlag(true);
    bookInfoDialog->setParam(param);
    bookInfoDialog->init(&bookDataSet);
    bookInfoDialog->exec();
    this->loadTable();
}

void BookManage::deleteBtnClicked()
{
    QItemSelectionModel* selections = ui->bookTable->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if (selected.empty())
    {
        QMessageBox::warning(this, "警告", "请选择一行");
        return;
    }
    int row = selected.at(0).row();
    int id = bookModel->item(row, 0)->text().toInt();
    bookDataSet.remove(id);
    this->loadTable();
}

void BookManage::query()
{
    QString queryStr = ui->searchLine->text();
    if (queryStr=="")//如果查询字符串为空 则显示所有数据
    {
        for (int i = 0; i < bookModel->rowCount(); i++)
        {
            ui->bookTable->setRowHidden(i, false);
        }
        return;
    }

    //将数据设置不可见
    for (int i = 0; i < bookModel->rowCount(); i++)
    {
        ui->bookTable->setRowHidden(i, true);
    }
    //获取查询字符串

    //判断是否为数字
    bool isNum;
    int id = queryStr.toInt(&isNum);

    QList<Book> bookList;
    if (isNum)//如果是数字
    {
        Book* book = bookDataSet.getById(id);
        if (book != nullptr)
        {
            bookList.append(*book);
        }
    }
    for (int i = 0; i < BookEnum::BOOK_ENUM_COUNT; i++)//遍历所有字段
    {
        bookList.append(bookDataSet.getByField(i, queryStr));
    }
    //将查询到的数据设置为可见
    for (const Book& book : bookList)
    {
        int row = bookModel->findItems(QString::number(book.getId()), Qt::MatchExactly).at(0)->row();
        ui->bookTable->setRowHidden(row, false);
    }
}


