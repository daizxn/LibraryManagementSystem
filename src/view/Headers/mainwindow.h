//
// Created by daizxn on 24-11-26.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bookmanage.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    BookManage *bookManage;
    /*UserManage *userManage;
    BorrowHistory *borrowHistory;*/

    void init();
    void initPage();

};


#endif //MAINWINDOW_H
