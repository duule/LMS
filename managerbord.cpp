#include "managerbord.h"
#include "ui_managerbord.h"

ManagerBord::ManagerBord(QMainWindow* mainwindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerBord)
{
    ui->setupUi(this);
    this->mainwindow = mainwindow;
    this->cp = new ChangePasswordBord("admin");
    connect(ui->btn_changePassword,SIGNAL(clicked(bool)),this,SLOT(changePasswordButtonOnClicked()));
    connect(ui->btn_logout,SIGNAL(clicked(bool)),this,SLOT(logoutButtonOnClicked()));
    connect(ui->btn_addBook,SIGNAL(clicked(bool)),this,SLOT(addBookButtonOnClicked()));
    connect(ui->btn_delBook,SIGNAL(clicked(bool)),this,SLOT(delBookButtonOnClicked()));
    connect(ui->btn_editBook,SIGNAL(clicked(bool)),this,SLOT(editBookButtonOnClicked()));
}
void ManagerBord::changePasswordButtonOnClicked(){
    this->cp->show();
}
void ManagerBord::logoutButtonOnClicked(){
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    qbox.setDefaultButton(QMessageBox::Yes);
    qbox.setText("确定注销？");
    int ret = qbox.exec();
//    QMessageBox::question(NULL,"提示","确定注销？",QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes){
        this->mainwindow->show();
        this->close();
    }
}
void ManagerBord::addBookButtonOnClicked(){
    AddBookBord* add = new AddBookBord();
    add->show();
}
void ManagerBord::delBookButtonOnClicked(){

}
void ManagerBord::editBookButtonOnClicked(){

}

ManagerBord::~ManagerBord()
{
    delete ui;
}
