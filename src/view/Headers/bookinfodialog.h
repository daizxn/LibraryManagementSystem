//
// Created by dai on 24-12-8.
//

#ifndef BOOKINFODIALOG_H
#define BOOKINFODIALOG_H

#include <QDialog>
#include <data/DataSet.h>
#include <class/book.h>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class BookInfoDialog;
}

QT_END_NAMESPACE

class BookInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookInfoDialog(QWidget* parent = nullptr);
    ~BookInfoDialog() override;
    void init(DataSet<Book>* bookDataSet);
    void setParam(const Book&);
    void setFlag(bool);

private:
    Ui::BookInfoDialog* ui;
    Book book;
    bool flag;
    DataSet<Book>* bookDataSet;

private slots:
    void saveBtnClicked();
    void cancelBtnClicked();

};


#endif //BOOKINFODIALOG_H
