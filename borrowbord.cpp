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
        QSqlQuery query,query2,query3;
        query.exec("SELECT * FROM books WHERE id = \'" + borrowBookId + "\' ;");
        query2.exec("SELECT * FROM readers WHERE id = \'" + this->readerId + "\' ;");
        query3.exec("SELECT * FROM borrow WHERE readerid = \'" + this->readerId + "\' ;");
        if(query.next()&&query2.next()){
            int leftPos = query.record().indexOf("left");
            int left = query.value(leftPos).toInt();
            int hasBorrowPos = query2.record().indexOf("hasBorrow");
            int canBorrowPos = query2.record().indexOf("maxBorrow");
            int daylongPos = query2.record().indexOf("daylong");
            int hasBorrow = query2.value(hasBorrowPos).toInt();
            int canBorrow = query2.value(canBorrowPos).toInt();
            int daylong = query2.value(daylongPos).toInt();
            query3.next();
            QString backDateString = query3.value(query3.record().indexOf("shouldbackDate")).toString();
            QDate backDate = QDate(backDateString.left(4).toInt(),backDateString.mid(5,2).toInt(),backDateString.right(2).toInt());
            QDate currentDate = QDate::currentDate();
            if(Tools::largerYearIsInLeft(backDate,currentDate)){
                if(left > 0){
                    if(hasBorrow < canBorrow){
                        int newLeft = left - 1;
                        int newHasBorrow = hasBorrow + 1;
                        QString borrowDate = QDate::currentDate().toString("yyyy-MM-dd");
                        QString backDate = Tools::addDaysOnDate(QDate::currentDate(),daylong).toString("yyyy-MM-dd");
                        QString sql = "INSERT INTO borrow(readerid,bookid,borrowDate,shouldbackDate) VALUES(\'" + this->readerId + "\',\'" + borrowBookId + "\',\'" + borrowDate + "\',\'" + backDate + "\')";
                        if(query.exec(sql)){
                            QMessageBox::information(NULL,"提示","借阅成功");
                            query.exec("UPDATE books SET `left` = " + QString("%1").arg(newLeft) + " WHERE id = \'" + borrowBookId + "\' ;");
                            query.exec("UPDATE readers SET `hasBorrow` = " + QString("%1").arg(newHasBorrow) + " WHERE id = \'" + this->readerId + "\' ;");
                            rb->init();
                            return;
                        }
                        else{
                            QMessageBox::information(NULL,"提示","借阅失败");
                            qDebug()<<sql;
                            return;
                        }
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
            else{
                QMessageBox::information(NULL,"提示","您还有逾期的书籍没有还，请先还书后再进行借阅操作。");
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
