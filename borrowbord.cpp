#include "borrowbord.h"
#include "ui_borrowbord.h"
#include "readerbord.h"

BorrowBord::BorrowBord(ReaderBord* rb, QString readerId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrowBord)
{
    ui->setupUi(this);
    this->rb = rb;
    this->readerId = readerId;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(buttonBoxAcceptOnClicked()));
}

void BorrowBord::buttonBoxAcceptOnClicked(){
    QString borrowBookId = ui->lineEdit->text();
    if(borrowBookId == NULL || borrowBookId == ""){
        QMessageBox::information(NULL,"提示","输入为空！");
    }
    else{
        QSqlQuery query,query2;
        query.exec("SELECT * FROM books WHERE id = \'" + borrowBookId + "\' ;");
        query2.exec("SELECT * FROM readers WHERE id = \'" + this->readerId + "\' ;");
        if(query.next()&&query2.next()){
            int leftPos = query.record().indexOf("left");
            int left = query.value(leftPos).toInt();
            int hasBorrowPos = query2.record().indexOf("hasBorrow");
            int canBorrowPos = query2.record().indexOf("maxBorrow");
            int hasBorrow = query2.value(hasBorrowPos).toInt();
            int canBorrow = query2.value(canBorrowPos).toInt();
            if(left > 0){
                if(hasBorrow < canBorrow){
                    int newLeft = left - 1;
                    int newHasBorrow = hasBorrow + 1;
                    query.exec("UPDATE books SET `left` = " + QString("%1").arg(newLeft) + " WHERE id = \'" + borrowBookId + "\' ;");
                    query.exec("UPDATE readers SET `hasBorrow` = " + QString("%1").arg(newHasBorrow) + " WHERE id = \'" + this->readerId + "\' ;");
                    query.exec("INSERT INTO borrow(readerid,bookid) VALUES(\'" + this->readerId + "\',\'" + borrowBookId + "\')");
                    QMessageBox::information(NULL,"提示","借阅成功");
                    rb->init();
                    return;
                }
                else{
                    QMessageBox::information(NULL,"提示","您已达到最大借阅数量，无法继续借阅，请先还书。");
                    return;
                }
            }
            else{
                QMessageBox::information(NULL,"提示","书籍可借剩余量不足！");
                return;
            }
        }
        QMessageBox::information(NULL,"提示","未查询到相应书籍！");
    }
}

BorrowBord::~BorrowBord()
{
    delete ui;
}
