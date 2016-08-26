#include "changepasswordbord.h"
#include "ui_changepasswordbord.h"

ChangePasswordBord::ChangePasswordBord(QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordBord)
{
    ui->setupUi(this);
    this->id = id;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(buttonboxAcceptOnClicked()));
}

void ChangePasswordBord::buttonboxAcceptOnClicked(){
    QString newPassword = ui->tf_newpass->text();
    QString reNewPassword = ui->tf_renewpass->text();
    if(newPassword == reNewPassword){
        QSqlQuery query;
        query.exec("UPDATE readers SET password = \'" + newPassword + "\' WHERE id = \'" + this->id + "\' ;");
        QMessageBox::information(NULL,"提示","密码修改成功！");
    }
    else{
        QMessageBox::information(NULL,"提示","两次输入不同！");
    }
}

ChangePasswordBord::~ChangePasswordBord()
{
    delete ui;
}
