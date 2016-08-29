#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QPluginLoader>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class Search;
}
class ReaderBord;
class Search : public QWidget
{
    Q_OBJECT

public:
    explicit Search(QString readerId,ReaderBord* readerbord, QWidget *parent = 0);
    ~Search();

private:
    Ui::Search *ui;
    QString readerId;
    ReaderBord* readerbord;
    void init();
private slots:
    void searchButtonOnClicked();
    void borrowButtonOnClicked();
};

#endif // SEARCH_H
