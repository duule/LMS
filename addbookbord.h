#ifndef ADDBOOKBORD_H
#define ADDBOOKBORD_H

#include <QWidget>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPalette>


namespace Ui {
class AddBookBord;
}
class ManagerBord;
class AddBookBord : public QWidget
{
    Q_OBJECT

public:
    explicit AddBookBord(ManagerBord* mb, QString type, QString id = "", QWidget *parent = 0);
    ~AddBookBord();

private:
    Ui::AddBookBord *ui;
    ManagerBord* mb;
    QString type;
    QString id;
    QString ztids[13] = {"无分类","TB  一般工业技术","TD  矿业工程","TE  石油、天然气工业","TF  金工业","TG  金属学","TH  机械","TJ  武器工业","TK  动力工业","TL  原子能技术","TM  电工技术","TN  无线电电子学、通信技术","TP  自动化技术、计算技术"};
    void init();
private slots:
    void addButtonOnClicked();
    void cancelButtonOnClicked();


    void idEditFinished();
    void nameEditFinished();
    void authorEditFinished();
    void isbnEditFinished();
};

#endif // ADDBOOKBORD_H
