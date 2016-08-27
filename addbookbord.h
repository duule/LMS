#ifndef ADDBOOKBORD_H
#define ADDBOOKBORD_H

#include <QWidget>

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
private slots:
    void addButtonOnClicked();
    void cancelButtonOnClicked();
};

#endif // ADDBOOKBORD_H
