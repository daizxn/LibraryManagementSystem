//
// Created by dai on 24-12-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BookInfoDialog.h" resolved

#include "Headers/bookinfodialog.h"
#include "Forms/ui_bookinfodialog.h"


BookInfoDialog::BookInfoDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::BookInfoDialog) {
    ui->setupUi(this);
}

BookInfoDialog::~BookInfoDialog() {
    delete ui;
}
