//
// Created by dai on 24-12-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookInfoDialog.h" resolved

#include "Headers/bookinfodialog.h"

#include <QMessageBox>
#include <sys/socket.h>

#include "Forms/ui_bookinfodialog.h"


BookInfoDialog::BookInfoDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::BookInfoDialog),
    bookDataSet(nullptr)
{
    flag = false;

    ui->setupUi(this);

    connect(ui->confirmBtn, &QPushButton::clicked, this, &BookInfoDialog::saveBtnClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &BookInfoDialog::cancelBtnClicked);
}

BookInfoDialog::~BookInfoDialog()
{
    delete ui;
}

void BookInfoDialog::setParam(const Book& book)
{
    this->book = book;
}

void BookInfoDialog::setFlag(const bool flag)
{
    this->flag = flag;
}

void BookInfoDialog::init(DataSet<Book>* bookDataSet)
{
    if (!flag)
    {
        this->bookDataSet = bookDataSet;
        ui->bookNameLine->clear();
        ui->bookAuthorLine->clear();
        ui->bookISBNLine->clear();
        ui->bookIsBorrowedBox->setCurrentIndex(0);
    }
    else
    {
        this->bookDataSet = bookDataSet;
        ui->bookNameLine->setText(book.getInfo(BookEnum::BOOK_NAME));
        ui->bookAuthorLine->setText(book.getInfo(BookEnum::BOOK_AUTHOR));
        ui->bookISBNLine->setText(book.getInfo(BookEnum::BOOK_ISBN));
        ui->bookIsBorrowedBox->setCurrentIndex(book.getInfo(BookEnum::BOOK_ISBORROWED)== "true" ? 0 : 1);
    }

}


void BookInfoDialog::saveBtnClicked()
{
    //验证是否输入数据
    if (ui->bookNameLine->text().isEmpty() || ui->bookAuthorLine->text().isEmpty() || ui->bookISBNLine->text().
        isEmpty())
    {
        QMessageBox::warning(this, "警告", "请填写完整信息");
        return;
    }

    QString bookName = ui->bookNameLine->text();
    QString bookAuthor = ui->bookAuthorLine->text();
    QString bookISBN = ui->bookISBNLine->text();
    QString bookIsBorrowed = ui->bookIsBorrowedBox->currentText();

    if (!flag)
    {
        Book book(-1, bookName, bookAuthor, bookISBN, bookIsBorrowed == "true" ? true : false);

        bookDataSet->addNewData(book);
    }
    if (flag)
    {
        Book book(this->book.getId(), bookName, bookAuthor, bookISBN, bookIsBorrowed == "true" ? true : false);
        bookDataSet->update(book.getId(), book);
    }

    this->hide();
}

void BookInfoDialog::cancelBtnClicked()
{
    this->hide();
}
