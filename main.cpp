#include "mainwindow.h"
#include "bookinfo.h"
#include "readerinfo.h"
#include "list.h"
#include "tools.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDate>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("LMS");
    db.setUserName("root");
    db.setPassword("Tami16.");
    if (db.open()) {
        QSqlQuery query;
        query.exec("SELECT * FROM booking ;");

        while(query.next()){
            QString EndDate = query.value(query.record().indexOf("bookingEndDate")).toString();
            QDate bookingEndDate = QDate(EndDate.left(4).toInt(),EndDate.mid(5,2).toInt(),EndDate.right(2).toInt());
            QDate currentDate = QDate::currentDate();
            if(Tools::largerYearIsInLeft(currentDate,bookingEndDate)){
                QString readerid = query.value(query.record().indexOf("readerid")).toString();
                QString bookid = query.value(query.record().indexOf("bookid")).toString();
                QSqlQuery query2;
                query2.exec("DELETE FROM booking WHERE readerid = \'" + readerid + "\' AND bookid = \'" + bookid + "\' ; ");
            }
        }

        w.show();
    }
    else{QMessageBox::information(NULL,"提示","数据库连接失败！");w.close();a.quit();return 0;}
    return a.exec();
}
