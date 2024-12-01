//
// Created by daizxn on 24-11-29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved
#include "admin.h"
#include "login.h"
#include "Forms/ui_login.h"

#include <QMessageBox>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>

Login::Login(QWidget *parent) :
        QDialog(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    initLogin();


    connect(ui->loginBtn, &QPushButton::clicked, this, &Login::login);
    connect(ui->exitBtn, &QPushButton::clicked, this, &Login::exit);
}

Login::~Login() {
    delete ui;
    delete admin;
}

void Login::login() {
    QString username = ui->lgUsername->text();
    QString password = ui->lgPassword->text();

    Admin inputAccount;
    inputAccount.setUsername(username);
    inputAccount.setPassword(password);

    if (inputAccount == *admin) {
        //QMessageBox::information(this, "Login", "Login successful");
        //qDebug()<<"Login successful";
        setResult(QDialog::Accepted);
        hide();
        return;
    } else {
        QMessageBox::warning(this, "Login", "Login failed");
        setResult(-1);
        return;
    }
}
void Login::exit() {
    setResult(QDialog::Rejected);
    this->close();
}

void Login::initLogin() {

    /*设置页面基本信息*/
    this->setFixedSize(400, 280); //设置窗口大小 由于驱动问题，这里固定大小无效
    this->setWindowTitle("Login"); //设置窗口标题

    /*读取文件*/
    QFile adminFile = QFile(":account/account/admin.json"); //读取admin.json文件
    if (!adminFile.open(QIODevice::ReadOnly | QIODevice::Text)) {  //如果文件打开失败
        QMessageBox::warning(this, "File", "File not found");
        return;
    }
    QTextStream adminReader(&adminFile); //读取文件
    adminReader.setEncoding(QStringConverter::Encoding::Utf8); //设置编码
    QString adminData = adminReader.readAll(); //读取所有数据
    adminFile.close();

    /*解析json数据*/
    QJsonParseError jsonError; //json解析错误
    QJsonDocument adminDoc = QJsonDocument::fromJson(adminData.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << jsonError.errorString();
        QMessageBox::warning(this, "Json", "Json parse error");
        return;
    }
    QJsonObject adminObj = adminDoc.object();
    this->admin = new Admin(adminObj["username"].toString(), adminObj["password"].toString());
//    qDebug() << admin->getUsername() << admin->getPassword();
}
