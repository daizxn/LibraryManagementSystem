//
// Created by dai on 24-12-9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SchemeDialog.h" resolved

#include "Headers/schemedialog.h"

#include <QMessageBox>

#include "Forms/ui_schemedialog.h"


SchemeDialog::SchemeDialog(QWidget* parent) :
    QDialog(parent), ui(new Ui::SchemeDialog)
{
    ui->setupUi(this);
}

SchemeDialog::SchemeDialog(const QList<QSharedPointer<QJsonObject>>& data, Database* bookDB, QWidget* parent,
                           ModifyIngo* modifyIngo) :
    QDialog(parent), ui(new Ui::SchemeDialog), dataLists(data), bookDB(bookDB), modifyIngo(modifyIngo)
{
    ui->setupUi(this);


    init();

    ui->groupBox->setVisible(false);

    connect(ui->pushButton, &QPushButton::clicked, this, &SchemeDialog::foldButton);
    disconnect(modifyIngo, &ModifyIngo::modifyInfo, nullptr, nullptr);
    connect(SchemeDialog::modifyIngo, &ModifyIngo::modifyInfo, [this]()
    {
        emit bookChanged();
    });
}

SchemeDialog::~SchemeDialog()
{
    delete ui;
}

void SchemeDialog::init()
{
    loadUI();
    loadTable();
}

void SchemeDialog::loadUI()
{
    //显示书本的基本信息
    if (dataLists[0]->contains("bookName"))
    {
        ui->bookNameLabel->setText(dataLists[0]->value("bookName").toString());
        ui->bookNameLabel->setAlignment(Qt::AlignCenter);
    }
    if (dataLists[0]->contains("author"))
    {
        ui->authorLabel->setText(dataLists[0]->value("author").toString());
        ui->authorLabel->setAlignment(Qt::AlignCenter);
    }
    if (dataLists[0]->contains("isbn"))
    {
        ui->isbnLabel->setText(dataLists[0]->value("isbn").toString());
        ui->isbnLabel->setAlignment(Qt::AlignCenter);
    }
    ui->countLabel->setText("共" + QString::number(dataLists.size()) + "本");
}

void SchemeDialog::loadTable()
{
    setWindowFlags(Qt::FramelessWindowHint); // 设置无边框样式
    ui->detailBookInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->detailBookInfo->horizontalHeader()->setSelectionBehavior(QAbstractItemView::SelectRows); // 选择行为：行
    ui->detailBookInfo->horizontalHeader()->setSelectionMode(QAbstractItemView::SingleSelection); // 选择模式：单选
    ui->detailBookInfo->horizontalHeader()->setStretchLastSection(true);
    ui->detailBookInfo->setRowCount(0);

    QStringList header;
    header << "ID" << "书名" << "是否借阅" << "借阅者" << "借阅时间" << "预计归还时间" << "操作" << "";

    ui->detailBookInfo->setColumnCount(header.size());
    ui->detailBookInfo->setHorizontalHeaderLabels(header);

    ui->groupBox->setTitle("详细信息");


    for (const auto& data : dataLists)
    {
        int row = ui->detailBookInfo->rowCount();
        ui->detailBookInfo->insertRow(row);

        ui->detailBookInfo->setItem(row, 0, new QTableWidgetItem(QString::number(data->value("id").toInt())));
        ui->detailBookInfo->setItem(row, 1, new QTableWidgetItem(data->value("bookName").toString()));
        ui->detailBookInfo->setItem(row, 2, new QTableWidgetItem(data->value("isBorrowed").toBool() ? "是" : "否"));
        if (data->value("isBorrowed").toBool())
        {
            ui->detailBookInfo->setItem(row, 3, new QTableWidgetItem(data->value("borrower").toString()));

            QDate borrpwDate;
            if (!data->value("borrowDate").toString().isEmpty())
                borrpwDate = QDate::fromString(data->value("borrowDate").toString(), "yyyy-MM-dd");
            QDateEdit* borrowDateEdit = new QDateEdit(borrpwDate);
            borrowDateEdit->setEnabled(false);
            ui->detailBookInfo->setCellWidget(row, 4, borrowDateEdit);
            QDate returnDate;
            if (!data->value("returnDate").toString().isEmpty())
                returnDate = QDate::fromString(data->value("returnDate").toString(), "yyyy-MM-dd");
            QDateEdit* returnDateEdit = new QDateEdit(returnDate);
            returnDateEdit->setEnabled(false);
            ui->detailBookInfo->setCellWidget(row, 5, returnDateEdit);
        }
        else
        {
            ui->detailBookInfo->setItem(row, 3, new QTableWidgetItem(""));
            ui->detailBookInfo->setItem(row, 4, new QTableWidgetItem(""));
            ui->detailBookInfo->setItem(row, 5, new QTableWidgetItem(""));
        }

        //操作按钮
        QPushButton* returnBtn = new QPushButton("归还");
        returnBtn->setProperty("id", data->value("id").toInt());
        connect(returnBtn, &QPushButton::clicked, [this,data]()
        {
            if (!data->value("isBorrowed").toBool())
            {
                QMessageBox::warning(this, "警告", "该书未被借阅");
                return;
            }

            QJsonObject returnData = *data;
            returnData["isBorrowed"] = false; //修改借阅状态
            returnData["borrower"] = ""; //重置借阅者
            returnData["borrowDate"] = ""; //重置借阅时间
            returnData["returnDate"] = ""; //重置归还时间
            bookDB->modifyData(returnData["id"].toInt(), returnData); //修改数据库
            emit bookChanged();
        }); //归还函数
        QPushButton* borrowBtn = new QPushButton("借阅");
        borrowBtn->setProperty("id", data->value("id").toInt());
        connect(borrowBtn, &QPushButton::clicked, [this,data]()
        {
            if (data->value("isBorrowed").toBool())
            {
                QMessageBox::warning(this, "警告", "该书已被借阅");
                return;
            }

            QJsonObject borrowData = *data;
            borrowData["isBorrowed"] = true; //修改借阅状态
            borrowData["borrower"] = "借阅者"; //设置借阅者
            borrowData["borrowDate"] = QDate::currentDate().toString("yyyy-MM-dd"); //设置借阅时间
            borrowData["returnDate"] = QDate::currentDate().addDays(14).toString("yyyy-MM-dd"); //设置归还时间
            modifyIngo->setParam(borrowData); //设置参数
            modifyIngo->init(ModifyIngo::BorrowModel); //设置模式
            modifyIngo->show(); //显示归还窗口
        }); //借阅函数
        QPushButton* deleteBtn = new QPushButton("删除");
        deleteBtn->setProperty("id", data->value("id").toInt());
        connect(deleteBtn, &QPushButton::clicked, [this,data]()
        {
            bookDB->deleteData(data->value("id").toInt());
            emit bookChanged();
        }); //删除函数
        QPushButton* modifyBtn = new QPushButton("修改");
        modifyBtn->setProperty("id", data->value("id").toInt());
        connect(modifyBtn, &QPushButton::clicked, [this,data]()
        {
            modifyIngo->setParam(*data);
            modifyIngo->init(ModifyIngo::ModifyModel);
            modifyIngo->show();
        }); //修改函数

        QLayout* layout = new QHBoxLayout();
        layout->addWidget(returnBtn);
        layout->addWidget(borrowBtn);
        layout->addWidget(deleteBtn);
        layout->addWidget(modifyBtn);

        layout->setSpacing(8);

        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(5, 0, 5, 0);

        QWidget* widget = new QWidget();
        widget->setLayout(layout);
        widget->setFixedWidth(300);
        ui->detailBookInfo->setCellWidget(row, 6, widget);

        ui->detailBookInfo->resizeColumnsToContents();

        ui->detailBookInfo->setColumnWidth(1, 150);
    }

    ui->groupBox->setFixedHeight(ui->detailBookInfo->rowHeight(0)*dataLists.size() + 150);
}

void SchemeDialog::setFold()
{
    bool isFold = !(ui->groupBox->isVisible());
    ui->groupBox->setVisible(isFold);
}

void SchemeDialog::foldButton()
{
    setFold();
    emit folded(ui->groupBox->isVisible());
}
