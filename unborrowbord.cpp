#include "unborrowbord.h"
#include "ui_unborrowbord.h"
#include "readerbord.h"

UnBorrowBord::UnBorrowBord(ReaderBord* rb, QString readerId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnBorrowBord)
{
    ui->setupUi(this);
    this->rb = rb;
    this->readerId = readerId;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(buttonBoxAcceptOnClicked()));
}

void UnBorrowBord::buttonBoxAcceptOnClicked(){
    QString borrowBookId = ui->lineEdit->text();
    if(borrowBookId == NULL || borrowBookId == ""){
        QMessageBox::information(NULL,"提示","输入为空！");
    }
    else{
        QSqlQuery query,query2,query3;
        query.exec("SELECT * FROM books WHERE id = \'" + borrowBookId + "\' ;");
        query2.exec("SELECT * FROM readers WHERE id = \'" + this->readerId + "\' ;");
        query3.exec("SELECT * FROM borrow WHERE readerid = \'" + this->readerId + "\' AND bookid = \'" + borrowBookId + "\' ;");
        if(query.next()&&query2.next()){
            int leftPos = query.record().indexOf("left");
            int left = query.value(leftPos).toInt();
            int hasBorrowPos = query2.record().indexOf("hasBorrow");
            int hasBorrow = query2.value(hasBorrowPos).toInt();
            if(query3.next()){
                int newLeft = left + 1;
                int newHasBorrow = hasBorrow - 1;
                query.exec("UPDATE books SET `left` = " + QString("%1").arg(newLeft) + " WHERE id = \'" + borrowBookId + "\' ;");
                query.exec("UPDATE readers SET `hasBorrow` = " + QString("%1").arg(newHasBorrow) + " WHERE id = \'" + this->readerId + "\' ;");
                query.exec("DELETE FROM borrow WHERE readerid = \'" + this->readerId + "\' AND bookid = \'" + borrowBookId + "\' LIMIT 1;");
                QMessageBox::information(NULL,"提示","还书成功");
                rb->init();
                return;
            }
            else{
                QMessageBox::information(NULL,"提示","在您已借阅书籍中未查询到相应书籍。");
                return;
            }
        }
        QMessageBox::information(NULL,"提示","未查询到该书籍或用户");
    }
}

UnBorrowBord::~UnBorrowBord()
{
    delete ui;
}
