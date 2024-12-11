//
// Created by dai on 24-12-10.
//

#ifndef MODIFYINGO_H
#define MODIFYINGO_H

#include <QDialog>
#include <QJsonObject>
#include <data/DataBase.h>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class ModifyIngo;
}

QT_END_NAMESPACE

class ModifyIngo : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyIngo(QWidget* parent = nullptr, Database* bookDB = nullptr);
    ~ModifyIngo() override;

    void setParam(const QJsonObject& param);
    void init(int model);

    //控制修改信息的显示
    static const int BookNameEnabel = 1;
    static const int AuthorEnabel = 2;
    static const int ISBNEnabel = 4;
    static const int IsBorrowed = 8;
    static const int Borrower = 16;
    static const int BorrowDate = 32;
    static const int ReturnDate = 64;
    static const int addFlag = 128;

    static const int BorrowModel = Borrower | BorrowDate | ReturnDate;
    static const int ReturnModel = ReturnDate;
    static const int ModifyModel = 127;
    static const int AddModel = 255;


signals:
    void modifyInfo();

private:
    Ui::ModifyIngo* ui;
    int model;
    Database *bookDB;
    QJsonObject param;




private slots:
    void changeIsBorrowed();

    void confirmButtonClicked();

    void cancelButtonClicked();
};


#endif //MODIFYINGO_H
