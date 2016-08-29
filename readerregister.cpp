#include "readerregister.h"
#include "ui_readerregister.h"

ReaderRegister::ReaderRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderRegister)
{
    ui->setupUi(this);
    init();
    connect(ui->tf_id,SIGNAL(editingFinished()),this,SLOT(idEditFinished()));
    connect(ui->tf_name,SIGNAL(editingFinished()),this,SLOT(nameEditFinished()));
    connect(ui->tf_department,SIGNAL(editingFinished()),this,SLOT(departmentEditFinished()));
    connect(ui->tf_password,SIGNAL(editingFinished()),this,SLOT(passwordEditFinished()));
    connect(ui->tf_passwordRepet,SIGNAL(editingFinished()),this,SLOT(passwordRepetEditFinished()));
    connect(ui->btn_register,SIGNAL(clicked(bool)),this,SLOT(registerButtonOnClicked()));
    connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(cancelButtonOnClicked()));
}

void ReaderRegister::init(){
    QString types[4] = {"本科生","研究生","留学生","教师"};
    for(int i = 0; i<4; i++){
        ui->cb_type->addItem(types[i]);
    }
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    // Set color to warning label wirh QPalette.
    ui->lb_idwarn->setPalette(pe);
    ui->lb_namewarn->setPalette(pe);
    ui->lb_departmentwarn->setPalette(pe);
    ui->lb_passwarn->setPalette(pe);
    ui->lb_reptwarn->setPalette(pe);
    // warning message is hidden default.
    ui->lb_namewarn->hide();
    ui->lb_idwarn->hide();
    ui->lb_departmentwarn->hide();
    ui->lb_passwarn->hide();
    ui->lb_reptwarn->hide();
}

void ReaderRegister::clearForm(){
    ui->tf_id->clear();
    ui->tf_name->clear();
    ui->tf_password->clear();
    ui->tf_passwordRepet->clear();
    ui->tf_department->clear();
    ui->cb_type->setCurrentIndex(0);
}

void ReaderRegister::registerButtonOnClicked(){
    QString types[4] = {"本科生","研究生","留学生","教师"};
    QString id = ui->tf_id->text();
    QString name = ui->tf_name->text();
    QString password = ui->tf_password->text();
    QString passwordRepet = ui->tf_passwordRepet->text();
    QString department = ui->tf_department->text();
    QString type = ui->cb_type->currentText();
    int maxBorrow,hasBorrow = 0;
    if(type == types[0])maxBorrow = 4;
    else if(type == types[1])maxBorrow = 6;
    else if(type == types[2])maxBorrow = 6;
    else if(type == types[3])maxBorrow = 8;

    if(id.length() != 10 ){ui->lb_idwarn->show();return;}
    else if(name == NULL || name == "" ){ui->lb_namewarn->show();return;}
    else if(department == NULL || department == "" ){ui->lb_departmentwarn->show();return;}
    else if(password == NULL || password == ""){ui->lb_passwarn->show();return;}
    else if(password != passwordRepet){ui->lb_reptwarn->show();return;}

    QString sql = "INSERT INTO readers(id,`name`,department,type,password,maxBorrow,hasBorrow,verify) VALUES(\'" + id + "\',\'" + name + "\',\'" + department + "\',\'" + type + "\',\'" + password + "\'," + QString("%1").arg(maxBorrow) + "," + QString("%1").arg(hasBorrow) + ",\'未审核\');";
    qDebug()<<sql;
    QSqlQuery query;
    bool ret = query.exec(sql);
    if(ret) {QMessageBox::information(NULL,"提示","注册成功！请耐心等待管理员审核后即可登录。");this->close();}
    else QMessageBox::information(NULL,"提示","注册失败！");
}
void ReaderRegister::cancelButtonOnClicked(){
    this->close();
}

void ReaderRegister::idEditFinished(){
    QString id = ui->tf_id->text();
    if(id.length() != 10 ){
        ui->lb_idwarn->setText("编号长度为10");
        ui->lb_idwarn->show();
        return;
    }
    else {
        QSqlQuery query;
        query.exec("SELECT * FROM readers WHERE id = \'" + id + "\' ;");
        if(query.next()){
            ui->lb_idwarn->setText("该编号已存在。");
            ui->lb_idwarn->show();
            return;
        }
        ui->lb_idwarn->hide();
    }
}
void ReaderRegister::nameEditFinished(){
    QString name = ui->tf_name->text();
    if(name == NULL || name == "" )ui->lb_namewarn->show();
    else ui->lb_namewarn->hide();
}
void ReaderRegister::passwordEditFinished(){
    QString password = ui->tf_password->text();
    if(password == NULL || password == "")ui->lb_passwarn->show();
    else ui->lb_passwarn->hide();
}
void ReaderRegister::passwordRepetEditFinished(){
    QString password = ui->tf_password->text();
    QString passwordRepet = ui->tf_passwordRepet->text();
    if(password != passwordRepet)ui->lb_reptwarn->show();
    else ui->lb_reptwarn->hide();
}
void ReaderRegister::departmentEditFinished(){
    QString department = ui->tf_department->text();
    if(department == NULL || department == "" )ui->lb_departmentwarn->show();
    else ui->lb_departmentwarn->hide();
}

ReaderRegister::~ReaderRegister()
{
    delete ui;
}
