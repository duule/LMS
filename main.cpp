#include "mainwindow.h"
#include "bookinfo.h"
#include <iostream>
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Date s ;
    BookInfo("123","12","haha","dule","imu",s, "fdsa",  "01",999.98);
    return a.exec();
}
