//
// Created by daizxn on 24-11-29.
//

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog {
Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;

private:
    Ui::Login *ui;
    Admin *admin{};

    void initLogin();


public slots:
    void login();
    void exit();
};


#endif //LOGIN_H
