//
// Created by dai on 24-12-9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SchemeDialog.h" resolved

#include "Headers/schemedialog.h"
#include "Forms/ui_schemedialog.h"


SchemeDialog::SchemeDialog(QWidget* parent) :
    QDialog(parent), ui(new Ui::SchemeDialog)
{
    ui->setupUi(this);


}

SchemeDialog::SchemeDialog(const QList<QSharedPointer<QJsonObject>>& data, QWidget* parent) :
    QDialog(parent), ui(new Ui::SchemeDialog), dataLists(data)
{
    ui->setupUi(this);


    init();

    ui->groupBox->setVisible(false);

    connect(ui->pushButton, &QPushButton::clicked, this, &SchemeDialog::foldButton);
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
    header << "ID" << "书名" << "是否借阅" << "借阅者" << "借阅时间" << "预计归还时间" << "操作"<<"";

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

            QDate borrpwDate = QDate::fromString(data->value("borrowDate").toString(), "yyyy-MM-dd");
            QDateEdit* borrowDateEdit = new QDateEdit(borrpwDate);
            borrowDateEdit->setEnabled(false);
            ui->detailBookInfo->setCellWidget(row, 4, borrowDateEdit);
            QDate returnDate = QDate::fromString(data->value("returnDate").toString(), "yyyy-MM-dd");
            QDateEdit* returnDateEdit = new QDateEdit(returnDate);
            returnDateEdit->setEnabled(false);
            ui->detailBookInfo->setCellWidget(row, 5, returnDateEdit);
        }
        else
        {
            ui->detailBookInfo->setItem(row,3,new QTableWidgetItem(""));
            ui->detailBookInfo->setItem(row,4,new QTableWidgetItem(""));
            ui->detailBookInfo->setItem(row,5,new QTableWidgetItem(""));
        }


        QPushButton* returnBtn = new QPushButton("归还");
        returnBtn->setProperty("id", data->value("id").toInt());
        QPushButton* borrowBtn = new QPushButton("借阅");
        borrowBtn->setProperty("id", data->value("id").toInt());
        QPushButton* deleteBtn = new QPushButton("删除");
        deleteBtn->setProperty("id", data->value("id").toInt());
        QPushButton* modifyBtn = new QPushButton("修改");
        modifyBtn->setProperty("id", data->value("id").toInt());

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

        ui->detailBookInfo->setColumnWidth(1,150);
    }
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
