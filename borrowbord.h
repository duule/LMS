#ifndef BORROWBORD_H
#define BORROWBORD_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>
class ReaderBord;

namespace Ui {
class BorrowBord;
}

class BorrowBord : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowBord(ReaderBord* rb, QString readerId, QWidget *parent = 0);
    ~BorrowBord();

private:
    Ui::BorrowBord *ui;
    ReaderBord* rb;
    QString readerId;
private slots:
    void buttonBoxAcceptOnClicked();
};

#endif // BORROWBORD_H
