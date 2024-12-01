//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookManage.h" resolved

#include "bookmanage.h"
#include "Forms/ui_bookmanage.h"


BookManage::BookManage(QWidget *parent) :
        QWidget(parent), ui(new Ui::BookManage) {
    ui->setupUi(this);
}

BookManage::~BookManage() {
    delete ui;
}
