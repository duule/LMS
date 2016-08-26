#include "mainwindow.h"
#include "bookinfo.h"
#include "readerinfo.h"
#include "list.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("LMS");
    db.setUserName("root");
    db.setPassword("Tami16.");
    if (db.open()) { w.show();}
    else{QMessageBox::information(NULL,"提示","数据库连接失败！");w.close();a.quit();return 0;}
    return a.exec();
}
