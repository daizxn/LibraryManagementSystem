//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookManage.h" resolved

#include "bookmanage.h"
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
        editBtn->setProperty("row", book.getId());

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
