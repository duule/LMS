#include "editbookinfobord.h"
#include "ui_editbookinfobord.h"

EditBookInfoBord::EditBookInfoBord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBookInfoBord)
{
    ui->setupUi(this);
}

EditBookInfoBord::~EditBookInfoBord()
{
    delete ui;
}
