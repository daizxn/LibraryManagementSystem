//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_BORROWHISTORY_H
#define LIBRARYMANAGEMENTSYSTEM_BORROWHISTORY_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class BorrowHistory; }
QT_END_NAMESPACE

class BorrowHistory : public QWidget {
Q_OBJECT

public:
    explicit BorrowHistory(QWidget *parent = nullptr);

    ~BorrowHistory() override;

private:
    Ui::BorrowHistory *ui;
};


#endif //LIBRARYMANAGEMENTSYSTEM_BORROWHISTORY_H
