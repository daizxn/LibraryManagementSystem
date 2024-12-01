//
// Created by dai on 24-12-1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BorrowHistory.h" resolved

#include "borrowhistory.h"
#include "Forms/ui_borrowhistory.h"


BorrowHistory::BorrowHistory(QWidget *parent) :
        QWidget(parent), ui(new Ui::BorrowHistory) {
    ui->setupUi(this);
}

BorrowHistory::~BorrowHistory() {
    delete ui;
}
