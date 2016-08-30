#ifndef BOOKINGBORD_H
#define BOOKINGBORD_H

#include <QDialog>

namespace Ui {
class BookingBord;
}
class ReaderBord;
class BookingBord : public QDialog
{
    Q_OBJECT

public:
    explicit BookingBord(ReaderBord* rb, QString readerId,QWidget *parent = 0);
    ~BookingBord();

private:
    Ui::BookingBord *ui;
    ReaderBord* rb;
    QString readerId;
private slots:
    void buttonBoxAcceptOnClicked();
};

#endif // BOOKINGBORD_H
