//
// Created by dai on 24-12-9.
//

#ifndef SCHEMEDIALOG_H
#define SCHEMEDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QDate>
#include <QDateEdit>


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
    SchemeDialog(const QList<QSharedPointer<QJsonObject>>& data, QWidget* parent = nullptr);
    ~SchemeDialog() override;

    void init();
    void loadUI();
    void loadTable();

private:
    Ui::SchemeDialog* ui;
    QList<QSharedPointer<QJsonObject>> dataLists;
};


#endif //SCHEMEDIALOG_H
