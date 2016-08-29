#ifndef READERREGISTER_H
#define READERREGISTER_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ReaderRegister;
}

class ReaderRegister : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderRegister(QWidget *parent = 0);
    void clearForm();
    ~ReaderRegister();

private:
    Ui::ReaderRegister *ui;
    void init();
private slots:
    void idEditFinished();
    void nameEditFinished();
    void passwordEditFinished();
    void passwordRepetEditFinished();
    void departmentEditFinished();

    void registerButtonOnClicked();
    void cancelButtonOnClicked();
};

#endif // READERREGISTER_H
