//
// Created by dai on 24-12-9.
//

#ifndef SCHEMEDIALOG_H
#define SCHEMEDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QDate>
#include <QDateEdit>
#include "modifyinfo.h"
#include "data/DataBase.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class SchemeDialog;
}

QT_END_NAMESPACE

class SchemeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SchemeDialog(QWidget* parent = nullptr);
    SchemeDialog(const QList<QSharedPointer<QJsonObject>>& data, Database* bookDB=nullptr,QWidget* parent = nullptr, ModifyIngo* modifyIngo = nullptr);
    ~SchemeDialog() override;

    void init();
    void loadUI();
    void loadTable();

    void setFold();

private:
    Ui::SchemeDialog* ui;
    Database* bookDB;
    ModifyIngo* modifyIngo;
    QList<QSharedPointer<QJsonObject>> dataLists;

signals:
    void folded(bool);
    void bookChanged(bool);

private slots:
    void foldButton();


};


#endif //SCHEMEDIALOG_H
