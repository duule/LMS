#include "mainwindow.h"
#include "bookinfo.h"
#include "readerinfo.h"
#include "list.h"
#include "tools.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    //-------------test---------------//

    qDebug()<<Tools::getDistanceOfDate(QDate(2014,8,12),QDate(2016,8,12));

    //-------------test---------------//


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("LMS");
    db.setUserName("root");
    db.setPassword("Tami16.");
    if (db.open()) { w.show();}
    else{QMessageBox::information(NULL,"提示","数据库连接失败！");w.close();a.quit();return 0;}
    return a.exec();
}
