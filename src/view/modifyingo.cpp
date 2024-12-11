//
// Created by dai on 24-12-10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ModifyIngo.h" resolved

#include <QMessageBox>

#include "Headers/modifyinfo.h"
#include "Forms/ui_modifyinfo.h"


ModifyIngo::ModifyIngo(QWidget* parent, Database* bookDB) :
    QDialog(parent), ui(new Ui::ModifyIngo), bookDB(bookDB)
{
    ui->setupUi(this);

    connect(ui->isBorrowedBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &ModifyIngo::changeIsBorrowed);
    connect(ui->confirmButton, &QPushButton::clicked, this, &ModifyIngo::confirmButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ModifyIngo::cancelButtonClicked);
}

ModifyIngo::~ModifyIngo()
{
    delete ui;
}

void ModifyIngo::setParam(const QJsonObject& param)
{
    this->param = param;
}

void ModifyIngo::init(const int model)
{
    this->model = model;
    if (this->model & addFlag)
    {
        ui->bookNameLine->clear();
        ui->authorLine->clear();
        ui->ISBNLine->clear();
        ui->isBorrowedBox->setCurrentIndex(0);
        ui->borrowerLine->clear();
        ui->borrowerLine->setEnabled(false);
        ui->borrowDate->clear();
        ui->borrowDate->setEnabled(false);
        ui->borrowDate->clear();
        ui->returnDate->setEnabled(false);
    }
    else
    {
        //设置控件的可用性
        //先将所有控件设置为不可用
        ui->bookNameLine->setText(param.value("bookName").toString());
        ui->bookNameLine->setEnabled(false);
        ui->authorLine->setText(param.value("author").toString());
        ui->authorLine->setEnabled(false);
        ui->isBorrowedBox->setCurrentIndex(param.value("isBorrowed").toBool() == true ? 1 : 0);
        ui->ISBNLine->setEnabled(false);
        ui->ISBNLine->setText(param.value("isbn").toString());
        ui->isBorrowedBox->setEnabled(false);
        ui->borrowerLine->setText(param.value("borrower").toString());
        ui->borrowerLine->setEnabled(false);

        //设置日期
        if (!param.value("borrowDate").toString().isEmpty()) //如果借阅日期不为空
            ui->borrowDate->setDate(QDate::fromString(param.value("borrowDate").toString(), "yyyy-MM-dd"));
        else ui->borrowDate->clear();
        ui->borrowDate->setEnabled(false);
        if (!param.value("returnDate").toString().isEmpty()) //如果归还日期不为空
            ui->returnDate->setDate(QDate::fromString(param.value("returnDate").toString(), "yyyy-MM-dd"));
        else ui->returnDate->clear();
        ui->returnDate->setEnabled(false);

        //根据model设置控件的可用性
        if (this->model & BookNameEnabel)
        {
            ui->bookNameLine->setEnabled(true);
        }
        if (this->model & AuthorEnabel)
        {
            ui->authorLine->setEnabled(true);
        }
        if (this->model & ISBNEnabel)
        {
            ui->ISBNLine->setEnabled(true);
        }
        if (this->model & IsBorrowed)
        {
            ui->isBorrowedBox->setEnabled(true);
        }
        if (this->model & Borrower)
        {
            ui->borrowerLine->setEnabled(true);
        }
        if (this->model & BorrowDate)
        {
            ui->borrowDate->setEnabled(true);
        }
        if (this->model & ReturnDate)
        {
            ui->returnDate->setEnabled(true);
        }
    }

    changeIsBorrowed();
}

void ModifyIngo::changeIsBorrowed()
{
    if (ui->isBorrowedBox->currentIndex())
    {
        ui->borrowerLine->setEnabled(true);
        ui->borrowDate->setEnabled(true);
        ui->returnDate->setEnabled(true);
    }
    else
    {
        ui->borrowerLine->setEnabled(false);
        ui->borrowerLine->clear();
        ui->borrowDate->setEnabled(false);
        ui->borrowDate->setDate(QDate::currentDate());
        ui->returnDate->setEnabled(false);
        ui->returnDate->setDate(QDate::currentDate().addDays(14));
    }
}

void ModifyIngo::confirmButtonClicked()
{
    //校验数据合法性
    if (ui->bookNameLine->text().isEmpty())
    {
        QMessageBox::warning(this, "警告", "书名不能为空");
        return;
    }
    if (ui->authorLine->text().isEmpty())
    {
        QMessageBox::warning(this, "警告", "作者不能为空");
        return;
    }
    if (ui->ISBNLine->text().isEmpty())
    {
        QMessageBox::warning(this, "警告", "ISBN不能为空");
        return;
    }
    if (ui->isBorrowedBox->currentText() == "是")
    {
        if (ui->borrowerLine->text().isEmpty())
        {
            QMessageBox::warning(this, "警告", "借阅者不能为空");
            return;
        }
        if (ui->borrowDate->date().daysTo(ui->returnDate->date()) < 0)
        {
            QMessageBox::warning(this, "警告", "归还日期不能早于借阅日期");
            return;
        }
    }

    //获取参数
    QJsonObject param;
    param.insert("id", this->param.value("id").toInt());
    param.insert("bookName", ui->bookNameLine->text());
    param.insert("author", ui->authorLine->text());
    param.insert("isbn", ui->ISBNLine->text());
    param.insert("isBorrowed", ui->isBorrowedBox->currentText() == "是" ? true : false);


    //格式化数据
    if (param.value("isBorrowed").toBool())
    {
        param.insert("borrower", ui->borrowerLine->text());
        param.insert("borrowDate", ui->borrowDate->date().toString("yyyy-MM-dd"));
        param.insert("returnDate", ui->returnDate->date().toString("yyyy-MM-dd"));
    }
    else
    {
        param.insert("borrower", "");
        param.insert("borrowDate", "");
        param.insert("returnDate", "");
    }

    //修改数据库
    //如果是添加
    if (this->model & addFlag)
        bookDB->insertData(param);
    else if (this->model & ModifyModel)
        bookDB->modifyData(param.value("id").toInt(), param);
    emit modifyInfo();

    close();
}

void ModifyIngo::cancelButtonClicked()
{
    emit modifyInfo();
    close();
}
