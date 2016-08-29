#ifndef BOOKINGBORD_H
#define BOOKINGBORD_H

#include <QDialog>

namespace Ui {
class BookingBord;
}

class BookingBord : public QDialog
{
    Q_OBJECT

public:
    explicit BookingBord(QWidget *parent = 0);
    ~BookingBord();

private:
    Ui::BookingBord *ui;
};

#endif // BOOKINGBORD_H
