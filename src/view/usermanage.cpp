//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserManage.h" resolved

#include "usermanage.h"
#include "Forms/ui_usermanage.h"


UserManage::UserManage(QWidget *parent) :
        QWidget(parent), ui(new Ui::UserManage) {
    ui->setupUi(this);
}

UserManage::~UserManage() {
    delete ui;
}
