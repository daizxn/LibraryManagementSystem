//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BOOKMANAGE_H
#define LIBRARYMANAGEMENTSYSTEM_BOOKMANAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class BookManage; }
QT_END_NAMESPACE

class BookManage : public QWidget {
Q_OBJECT

public:
    explicit BookManage(QWidget *parent = nullptr);

    ~BookManage() override;

private:
    Ui::BookManage *ui;
};


#endif //LIBRARYMANAGEMENTSYSTEM_BOOKMANAGE_H
