#ifndef READERBORD_H
#define READERBORD_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "search.h"
#include "readerinfobord.h"
#include "borrowbord.h"
#include "unborrowbord.h"

namespace Ui {
class ReaderBord;
}

class ReaderBord : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReaderBord(QString id,QString name, QMainWindow* mainwindow, QWidget *parent = 0);
    ~ReaderBord();
    void init();
private:
    Ui::ReaderBord *ui;
    Search* search;
    QString readerid;
    QString readername;
    QMainWindow* mainwindow;
    BorrowBord* bb;
    UnBorrowBord* ub;
private slots:
    void searchButtonOnClicked();
    void myInfoButtonOnClicked();
    void borrowButtonOnClicked();
    void unborrowButtonOnClicked();
    void logoutButtonOnClicked();
};

#endif // READERBORD_H
