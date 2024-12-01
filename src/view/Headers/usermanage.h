//
// Created by dai on 24-12-1.
//

#ifndef LIBRARYMANAGEMENTSYSTEM_USERMANAGE_H
#define LIBRARYMANAGEMENTSYSTEM_USERMANAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class UserManage; }
QT_END_NAMESPACE

class UserManage : public QWidget {
Q_OBJECT

public:
    explicit UserManage(QWidget *parent = nullptr);

    ~UserManage() override;

private:
    Ui::UserManage *ui;
};


#endif //LIBRARYMANAGEMENTSYSTEM_USERMANAGE_H
