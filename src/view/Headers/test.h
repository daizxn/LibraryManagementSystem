//
// Created by daizxn on 24-11-26.
//

#ifndef TEST_H
#define TEST_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class test; }
QT_END_NAMESPACE

class test : public QWidget {
Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test() override;

private:
    Ui::test *ui;
};


#endif //TEST_H
