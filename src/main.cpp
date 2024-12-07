#include <QApplication>
#include "mainwindow.h"
#include "login.h"
#include "class/admin.h"
#include "class/book.h"
#include "data/AVLTree.h"
#include "data/list.h"

int main(int argc, char *argv[]) {
    Book b;

    QApplication a(argc, argv);
    Login l;
    auto result = l.exec();
    while (result == -1) {
        //如果密码错误，重新输入
        result = l.exec();
    }
    if (result == QDialog::Accepted) {
        //如果密码正确，进入主界面
        MainWindow w; //创建主界面
        w.show();
        return QApplication::exec();
    }
    if (result == QDialog::Rejected) {
        //如果点击取消，退出程序
        QApplication::exit(0);
    }
    return 0;
}
