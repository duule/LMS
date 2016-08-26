#ifndef CHANGEPASSWORDBORD_H
#define CHANGEPASSWORDBORD_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>

namespace Ui {
class ChangePasswordBord;
}

class ChangePasswordBord : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordBord(QString id, QWidget *parent = 0);
    ~ChangePasswordBord();

private:
    Ui::ChangePasswordBord *ui;
    QString id;
private slots:
    void buttonboxAcceptOnClicked();
};

#endif // CHANGEPASSWORDBORD_H
