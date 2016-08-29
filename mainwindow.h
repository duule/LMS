#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include "readerbord.h"
#include "managerbord.h"
#include "readerregister.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ReaderRegister* rr;
private slots:
    void loginButtonOnClicked();
    void registerButtonOnClicked();

};
#endif // MAINWINDOW_H
