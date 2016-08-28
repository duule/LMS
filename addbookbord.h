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

class AddBookBord : public QWidget
{
    Q_OBJECT

public:
    explicit AddBookBord(QWidget *parent = 0);
    ~AddBookBord();

private:
    Ui::AddBookBord *ui;
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
