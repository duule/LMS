#ifndef MANAGERBORD_H
#define MANAGERBORD_H

#include <QWidget>
#include <QMainWindow>
#include "changepasswordbord.h"
#include "addbookbord.h"
#include "addreaderbord.h"

namespace Ui {
class ManagerBord;
}

class ManagerBord : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerBord(QMainWindow* mainwindow, QWidget *parent = 0);
    void init();
    void booksInit();
    void readersInit();
    ~ManagerBord();

private:
    Ui::ManagerBord *ui;
    QMainWindow* mainwindow;
    ChangePasswordBord* cp;
private slots:
    void logoutButtonOnClicked();
    void changePasswordButtonOnClicked();

    void searchBookButtonOnClicked();
    void addBookButtonOnClicked();
    void delBookButtonOnClicked();
    void editBookButtonOnClicked();
    void showBook_sReadersButtonOnClicked();

    void searchReaderButtonOnClicked();
    void addReaderButtonOnClicked();
    void delReaderButtonOnClicked();
    void editReaderButtonOnClicked();
    void verifyButtonOnClicked();
    void showReader_sBookButtonOnClicked();
};

#endif // MANAGERBORD_H
