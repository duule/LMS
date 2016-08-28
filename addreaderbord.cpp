#include "addreaderbord.h"
#include "ui_addreaderbord.h"
#include "readerbord.h"
AddReaderBord::AddReaderBord(ManagerBord* mb,QString type, QString id , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddReaderBord)
{
    ui->setupUi(this);
    this->mb = mb;
    this->type = type;
    this->id = id;
    init();

    connect(ui->btn_add,SIGNAL(clicked(bool)),this,SLOT(addButtonOnClicked()));
    connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(cancelButtonOnClicked()));
    connect(ui->tf_id,SIGNAL(editingFinished()),this,SLOT(idEditFinished()));
    connect(ui->tf_name,SIGNAL(editingFinished()),this,SLOT(nameEditFinished()));
    connect(ui->tf_department,SIGNAL(editingFinished()),this,SLOT(departmentEditFinished()));
}


void AddReaderBord::init(){
    for(int i = 0; i<13; i++){
        ui->cb_type->addItem(types[i]);
    }

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    // Set color to warning label wirh QPalette.
    ui->lb_idwarn->setPalette(pe);
    ui->lb_namewarn->setPalette(pe);
    ui->lb_departmentwarn->setPalette(pe);
    // warning message is hidden default.
    ui->lb_namewarn->hide();
    ui->lb_idwarn->hide();
    ui->lb_departmentwarn->hide();


    if(type == "edit"){
        QSqlQuery query;
        query.exec("SELECT * FROM readers WHERE id = " + id + ";");
        if(query.next())
        {
            QString id = query.value(query.record().indexOf("id")).toString();
            QString name = query.value(query.record().indexOf("name")).toString();
            QString department = query.value(query.record().indexOf("department")).toString();
            QString type = query.value(query.record().indexOf("type")).toString();
            int currentIndex = 0;
            for(int i = 0;i<4; i++)
                if(type == types[i])
                    { currentIndex = i;break; }

            ui->tf_id->setText(id);
            ui->tf_name->setText(name);
            ui->tf_department->setText(department);
            ui->cb_type->setCurrentIndex(currentIndex);
        }
        ui->btn_add->setText("修改");
    }
}

void AddReaderBord::addButtonOnClicked(){
    QString id = ui->tf_id->text();
    QString name = ui->tf_name->text();
    QString department = ui->tf_department->text();
    QString type = ui->cb_type->currentText();
    int maxBorrow,hasBorrow = 0;
    if(type == types[0])maxBorrow = 4;
    else if(type == types[1])maxBorrow = 6;
    else if(type == types[2])maxBorrow = 6;
    else if(type == types[3])maxBorrow = 8;
    QString sql,success,failed;
    if(this->type == "add") {
//        sql = "INSERT INTO readers(id,ztid,`name`,author,press,date,isbn,edition,price,total,`left`) VALUES(\'" + id + "\',\'" + ztid + "\',\'" + name + "\',\'" + author + "\',\'" + press + "\',\'" + date + "\',\'" + isbn + "\'," + QString("%1").arg(edition) + "," + QString("%1").arg(price) + "," + QString("%1").arg(total) + "," + QString("%1").arg(total) + ");";
        success = "添加成功！";
        failed = "添加失败！";
    }
    else if(this->type == "edit"){
//        sql = "UPDATE readers SET ztid = \'" + ztid + "\',`name` = \'" + name + "\',author = \'" + author + "\',press = \'" + press + "\',date = \'" + date + "\',isbn = \'" + isbn + "\',edition = " + QString("%1").arg(edition) + ",price = " + QString("%1").arg(price) + ",total = " + QString("%1").arg(total) + ",`left` = " + QString("%1").arg(total) + " WHERE id = \'"+ id +"\' ;";
        success = "更改成功！";
        failed = "更改失败！";
    }
    QSqlQuery query;
    bool ret = query.exec(sql);
    if(ret){
        QMessageBox::information(NULL,"提示",success);
        this->mb->readersInit();
    }
    else{
        QMessageBox::information(NULL,"提示",failed);
    }
}
void AddReaderBord::cancelButtonOnClicked(){
    this->close();
    delete this;
}


void AddReaderBord::idEditFinished(){
    QString id = ui->tf_id->text();
    if(id.length() != 5 )ui->lb_idwarn->show();
    else ui->lb_idwarn->hide();
}
void AddReaderBord::nameEditFinished(){
    QString name = ui->tf_name->text();
    if(name == NULL || name == "" )ui->lb_namewarn->show();
    else ui->lb_namewarn->hide();
}
void AddReaderBord::departmentEditFinished(){
    QString department = ui->tf_department->text();
    if(department == NULL || department == "" )ui->lb_departmentwarn->show();
    else ui->lb_departmentwarn->hide();
}

AddReaderBord::~AddReaderBord()
{
    delete ui;
}
