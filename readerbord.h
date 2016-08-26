#ifndef READERBORD_H
#define READERBORD_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QSqlRecord>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "search.h"

namespace Ui {
class ReaderBord;
}

class ReaderBord : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReaderBord(QString id,QString name, QMainWindow* mainwindow, QWidget *parent = 0);
    ~ReaderBord();

private:
    Ui::ReaderBord *ui;
    void init();
    QString readerid;
    QString readername;
    QMainWindow* mainwindow;
private slots:
    void searchButtonOnClicked();
};

#endif // READERBORD_H
