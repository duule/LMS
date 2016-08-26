#ifndef READERINFOBORD_H
#define READERINFOBORD_H

#include <QWidget>
#include <QSqlRecord>
#include <qDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <QSqlQueryModel>
#include "changepasswordbord.h"

namespace Ui {
class ReaderInfoBord;
}

class ReaderInfoBord : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderInfoBord(QString readerId, QWidget *parent = 0);
    ~ReaderInfoBord();

private:
    Ui::ReaderInfoBord *ui;
    QString readerId;
    void init();
private slots:
    void changePasswordButtonOnClicked();
};

#endif // READERINFOBORD_H
