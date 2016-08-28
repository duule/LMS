#ifndef ADDREADERBORD_H
#define ADDREADERBORD_H

#include <QWidget>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPalette>


namespace Ui {
class AddReaderBord;
}
class ManagerBord;
class AddReaderBord : public QWidget
{
    Q_OBJECT

public:
    explicit AddReaderBord(ManagerBord* mb, QString type, QString id = "", QWidget *parent = 0);
    ~AddReaderBord();

private:
    Ui::AddReaderBord *ui;
    ManagerBord* mb;
    QString type;
    QString id;
    QString types[4] = {"本科生","研究生","留学生","教师"};
    void init();

private slots:
    void addButtonOnClicked();
    void cancelButtonOnClicked();


    void idEditFinished();
    void nameEditFinished();
    void departmentEditFinished();
};

#endif // ADDREADERBORD_H
