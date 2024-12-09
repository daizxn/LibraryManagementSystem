//
// Created by dai on 24-12-9.
//

#ifndef SCHEMEDIALOG_H
#define SCHEMEDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class SchemeDialog; }
QT_END_NAMESPACE

class SchemeDialog : public QDialog {
Q_OBJECT

public:
    explicit SchemeDialog(QWidget *parent = nullptr);
    ~SchemeDialog() override;

private:
    Ui::SchemeDialog *ui;
};


#endif //SCHEMEDIALOG_H
