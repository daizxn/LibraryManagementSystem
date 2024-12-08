//
// Created by dai on 24-12-8.
//

#ifndef BOOKINFODIALOG_H
#define BOOKINFODIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class BookInfoDialog; }
QT_END_NAMESPACE

class BookInfoDialog : public QDialog {
Q_OBJECT

public:
    explicit BookInfoDialog(QWidget *parent = nullptr);
    ~BookInfoDialog() override;

private:
    Ui::BookInfoDialog *ui;
};


#endif //BOOKINFODIALOG_H
