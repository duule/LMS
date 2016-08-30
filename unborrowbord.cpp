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
        QSqlQuery query;
        query.exec("SELECT * FROM books WHERE id = \'" + borrowBookId + "\' ;");

        if(query.next()){
            int left = query.value(query.record().indexOf("left")).toInt();

            query.exec("SELECT * FROM readers WHERE id = \'" + this->readerId + "\' ;");
            query.next();
            int hasBorrow = query.value(query.record().indexOf("hasBorrow")).toInt();

            query.exec("SELECT * FROM borrow WHERE readerid = \'" + this->readerId + "\' AND bookid = \'" + borrowBookId + "\' ;");
            if(query.next()){
                int newLeft = left + 1;
                int newHasBorrow = hasBorrow - 1;
                query.exec("UPDATE books SET `left` = " + QString("%1").arg(newLeft) + " WHERE id = \'" + borrowBookId + "\' ;");
                query.exec("UPDATE readers SET `hasBorrow` = " + QString("%1").arg(newHasBorrow) + " WHERE id = \'" + this->readerId + "\' ;");
                query.exec("DELETE FROM borrow WHERE readerid = \'" + this->readerId + "\' AND bookid = \'" + borrowBookId + "\' LIMIT 1;");
                QMessageBox::information(NULL,"提示","还书成功");

                QSqlQuery query2;
                QString sql = "SELECT * FROM booking WHERE bookid =\'" + borrowBookId + "\' AND bookingStartDate = \'0\' ;";
                qDebug()<<sql;
                query2.exec(sql);
                QString bookingReaderId,
                        bookingStartDate = QDate::currentDate().toString("yyyy-MM-dd"),
                        bookingEndDate = Tools::addDaysOnDate(QDate::currentDate(),15).toString("yyyy-MM-dd");
                while(query2.next()){
                    bookingReaderId = query2.value(query2.record().indexOf("readerid")).toString();
                }
                sql = "UPDATE booking SET bookingStartDate = \'" + bookingStartDate + "\' , bookingEndDate = \'" + bookingEndDate + "\' WHERE readerid = \'" + bookingReaderId + "\' AND bookid = \'" + borrowBookId + "\' ; ";
                qDebug()<<sql;
                qDebug()<<query.exec(sql);
                rb->init();
                return;
            }
            else{
                QMessageBox::information(NULL,"提示","在您已借阅书籍中未查询到相应书籍。");
                return;
            }
        }
        QMessageBox::information(NULL,"提示","未查询到该书籍");
    }
}

UnBorrowBord::~UnBorrowBord()
{
    delete ui;
}
