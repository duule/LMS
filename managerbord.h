#ifndef MANAGERBORD_H
#define MANAGERBORD_H

#include <QWidget>
#include <QMainWindow>
#include "changepasswordbord.h"
#include "addbookbord.h"

namespace Ui {
class ManagerBord;
}

class ManagerBord : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerBord(QMainWindow* mainwindow, QWidget *parent = 0);
    void booksInit();
    void readersInit();
    ~ManagerBord();

private:
    Ui::ManagerBord *ui;
    QMainWindow* mainwindow;
    ChangePasswordBord* cp;
private slots:
    void logoutButtonOnClicked();
    void addBookButtonOnClicked();
    void delBookButtonOnClicked();
    void editBookButtonOnClicked();
    void changePasswordButtonOnClicked();
};

#endif // MANAGERBORD_H
