#ifndef UNBORROWBORD_H
#define UNBORROWBORD_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>

class ReaderBord;
namespace Ui {
class UnBorrowBord;
}

class UnBorrowBord : public QDialog
{
    Q_OBJECT

public:
    explicit UnBorrowBord(ReaderBord* rb, QString readerId, QWidget *parent = 0);
    ~UnBorrowBord();

private:
    Ui::UnBorrowBord *ui;
    ReaderBord* rb;
    QString readerId;
private slots:
    void buttonBoxAcceptOnClicked();
};

#endif // UNBORROWBORD_H
