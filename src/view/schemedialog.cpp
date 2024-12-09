//
// Created by dai on 24-12-9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SchemeDialog.h" resolved

#include "Headers/schemedialog.h"
#include "Forms/ui_schemedialog.h"


SchemeDialog::SchemeDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SchemeDialog) {
    ui->setupUi(this);
}

SchemeDialog::~SchemeDialog() {
    delete ui;
}
