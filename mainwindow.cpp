#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->rr = new ReaderRegister();
    connect(ui->btn_login,SIGNAL(clicked(bool)),this,SLOT(loginButtonOnClicked()));
    connect(ui->btn_register,SIGNAL(clicked(bool)),this,SLOT(registerButtonOnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loginButtonOnClicked(){
    QString tf_id = ui->tf_id->text();
    QString tf_ps = ui->tf_password->text();
    QSqlQuery query;
    query.exec("SELECT * FROM readers WHERE id = \'" + tf_id + "\' ;");
    if(query.next())
    {
        int namePos = query.record().indexOf("name");
        int passPos = query.record().indexOf("password");
        int readerTypePos = query.record().indexOf("type");
        int verifyPos = query.record().indexOf("verify");
        QString name = query.value(namePos).toString();
        QString pass = query.value(passPos).toString();
        QString type = query.value(readerTypePos).toString();
        QString verify = query.value(verifyPos).toString();
        if(verify == "已审核"){
            if(tf_ps == pass){
                if(type == "管理员"){
                    ManagerBord* mb = new ManagerBord(this);
                    mb->show();
                    this->hide();
                    return;
                }
                else{
                    ReaderBord* r = new ReaderBord(tf_id,name,this);
                    r->show();
                    this->hide();
                    return;
                }
            }
            else{
                QMessageBox::information(NULL,"提示","密码错误！");
                return;
            }
        }
        else{
            QMessageBox::information(NULL,"提示","账号未审核，请耐心等待管理员审核。");
            return;
        }
    }
    QMessageBox::information(NULL,"提示","未找到用户或连接失败！");
}
void MainWindow::registerButtonOnClicked(){
    this->rr->clearForm();
    this->rr->show();
}
