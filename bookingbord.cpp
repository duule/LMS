#include "bookingbord.h"
#include "ui_bookingbord.h"

BookingBord::BookingBord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookingBord)
{
    ui->setupUi(this);
}

BookingBord::~BookingBord()
{
    delete ui;
}
