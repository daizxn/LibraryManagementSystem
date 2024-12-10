//
// Created by daizxn on 24-11-26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QPushButton>
#include "mainwindow.h"
#include "Forms/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        bookManage(nullptr),
        ui(new Ui::MainWindow) {


    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::init() {
    initPage();
}

void MainWindow::initPage() {
    //初始化页面
    //this指针传入，方便子页面调用父页面的方法以及析构函数链式调用
    bookManage = new BookManage(this);
    /*userManage = new UserManage(this);
    borrowHistory = new BorrowHistory(this);*/

    //将页面添加到stackedWidget中
    ui->stackedWidget->addWidget(bookManage);
    /*ui->stackedWidget->addWidget(userManage);
    ui->stackedWidget->addWidget(borrowHistory);*/

    //设置按钮点击事件
    connect(ui->bookManageButton, &QPushButton::clicked, [this] {
        ui->stackedWidget->setCurrentWidget(bookManage);
    });

    /*connect(ui->userManageButton, &QPushButton::clicked, [this] {
        ui->stackedWidget->setCurrentWidget(userManage);
    });

    connect(ui->borrowHistoryButton, &QPushButton::clicked, [this] {
        ui->stackedWidget->setCurrentWidget(borrowHistory);
    });*/
}
