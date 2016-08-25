#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <QSqlQueryModel>

namespace Ui {
class Search;
}

class Search : public QWidget
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = 0);
    ~Search();

private:
    Ui::Search *ui;
    void init();
private slots:
    void searchButtonOnClicked();
};

#endif // SEARCH_H
