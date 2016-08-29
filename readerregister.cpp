#include "readerregister.h"
#include "ui_readerregister.h"

ReaderRegister::ReaderRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderRegister)
{
    ui->setupUi(this);
}

ReaderRegister::~ReaderRegister()
{
    delete ui;
}
