//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BOOKMANAGE_H
#define LIBRARYMANAGEMENTSYSTEM_BOOKMANAGE_H

#include <QLabel>
#include <QWidget>
#include <QMessageBox>
#include <data/DataBase.h>
#include <util/normUtil.h>
#include "schemedialog.h"
#include "modifyinfo.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class BookManage;
}

QT_END_NAMESPACE

class BookManage : public QWidget
{
    Q_OBJECT

public:
    explicit BookManage(QWidget* parent = nullptr);

    ~BookManage() override;

private:
    Ui::BookManage* ui;
    ModifyIngo* modifyIngo;

    Database bookDB;



    void init();
    void loadTable(const QList<QPair<QString,QList<QSharedPointer<QJsonObject>>>>&);



private slots:

};


#endif //LIBRARYMANAGEMENTSYSTEM_BOOKMANAGE_H
