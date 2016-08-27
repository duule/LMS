#include "addbookbord.h"
#include "ui_addbookbord.h"

AddBookBord::AddBookBord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBookBord)
{
    ui->setupUi(this);
    connect(ui->btn_add,SIGNAL(clicked(bool)),this,SLOT(addButtonOnClicked()));
    connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(cancelButtonOnClicked()));
}

void AddBookBord::addButtonOnClicked(){
//    QString id = ui->tf_id->text();
//    QString ztid = ui->cb_ztid->text();
//    QString name = ui->tf_name->text();
//    QString author = ui->tf_author->text();
//    QString press = ui->tf_press->text();
//    int date_y = ui->dateEdit->YearSection;
//    int date_m = ui->dateEdit->MonthSection;
//    int date_d = ui->dateEdit->DaySection;
//    QString isbn = ui->tf_isbn->text();
//    QString edition = ui->tf_edition->text();
//    double price = ui->dsp_price->

}
void AddBookBord::cancelButtonOnClicked(){
    this->close();
    delete this;
}

AddBookBord::~AddBookBord()
{
    delete ui;
}
