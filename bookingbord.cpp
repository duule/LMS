#include "bookingbord.h"
#include "ui_bookingbord.h"
#include "readerbord.h"

BookingBord::BookingBord(ReaderBord* rb, QString readerId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookingBord)
{
    ui->setupUi(this);
    this->rb = rb;
    this->readerId = readerId;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(buttonBoxAcceptOnClicked()));
}

void BookingBord::buttonBoxAcceptOnClicked(){
    QString bookingBookId = ui->lineEdit->text();
    if(bookingBookId == NULL || bookingBookId == ""){
        QMessageBox::information(NULL,"提示","输入为空！");
    }
    else{
        QSqlQuery query,query2,query3;
        query.exec("SELECT * FROM books WHERE id = \'" + bookingBookId + "\' ;");
        query2.exec("SELECT * FROM readers WHERE id = \'" + this->readerId + "\' ;");
        query3.exec("SELECT * FROM borrow WHERE readerid = \'" + this->readerId + "\' ;");
        if(query.next()&&query2.next()){

            int leftPos = query.record().indexOf("left");
            int left = query.value(leftPos).toInt();
            int booking = query.value(query.record().indexOf("booking")).toInt();
            qDebug()<<booking;
            query3.next();
            QString backDateString = query3.value(query3.record().indexOf("shouldbackDate")).toString();
            QDate backDate = QDate(backDateString.left(4).toInt(),backDateString.mid(5,2).toInt(),backDateString.right(2).toInt());
            QDate currentDate = QDate::currentDate();
            if(Tools::largerYearIsInLeft(backDate,currentDate)){
                if(left > 0){
                    QString bookingStartDate = QDate::currentDate().toString("yyyy-MM-dd");
                    QString bookingEndDate = Tools::addDaysOnDate(QDate::currentDate(),15).toString("yyyy-MM-dd");
                    QString sql = "INSERT INTO booking(readerid,bookid,bookingStartDate,bookingEndDate) VALUES(\'" + this->readerId + "\',\'" + bookingBookId + "\',\'" + bookingStartDate + "\',\'" + bookingEndDate + "\')";
                    if(query.exec(sql)){
                        QMessageBox::information(NULL,"提示","预约成功，请在15天之内到图书馆进行借阅");
                        booking++;
                        QString sql = "UPDATE books SET booking = " +  QString("%1").arg(booking) + " WHERE id = \'" + bookingBookId + "\' ; ";
                        query.exec(sql);
                        return;
                    }
                    else{
                            QMessageBox::information(NULL,"提示","预约失败");
                            qDebug()<<sql;
                            return;
                    }
                }
                else{
                    QString sql = "INSERT INTO booking(readerid,bookid,bookingStartDate,bookingEndDate) VALUES(\'" + this->readerId + "\',\'" + bookingBookId + "\',\'0\',\'0\')";
                    if(query.exec(sql)){
                        QMessageBox::information(NULL,"提示","预约成功，有读者归还此书时将第一时间通知您，并且您需要在归还的15天内到图书馆进行借阅。");
                        return;
                    }
                }
            }
            else{
                QMessageBox::information(NULL,"提示","您还有逾期的书籍没有还，请先还书后再进行预约操作。");
                return;
            }
        }
        QMessageBox::information(NULL,"提示","未查询到相应书籍！");
    }
}

BookingBord::~BookingBord()
{
    delete ui;
}
