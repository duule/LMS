#include "addbookbord.h"
#include "ui_addbookbord.h"
#include "managerbord.h"
AddBookBord::AddBookBord(ManagerBord* mb,QString type, QString id , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBookBord)
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
    connect(ui->tf_author,SIGNAL(editingFinished()),this,SLOT(authorEditFinished()));
    connect(ui->tf_isbn,SIGNAL(editingFinished()),this,SLOT(isbnEditFinished()));
}

void AddBookBord::init(){
    for(int i = 0; i<13; i++){
        ui->cb_ztid->addItem(ztids[i]);
    }

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    // Set color to warning label wirh QPalette.
    ui->lb_idwarn->setPalette(pe);
    ui->lb_namewarn->setPalette(pe);
    ui->lb_authorwarn->setPalette(pe);
    ui->lb_isbnwarn->setPalette(pe);
    // warning message is hidden default.
    ui->lb_namewarn->hide();
    ui->lb_idwarn->hide();
    ui->lb_authorwarn->hide();
    ui->lb_isbnwarn->hide();


    if(type == "edit"){
        QSqlQuery query;
        query.exec("SELECT * FROM books WHERE id = " + id + ";");
        if(query.next())
        {
            QString id = query.value(query.record().indexOf("id")).toString();
            QString ztid = query.value(query.record().indexOf("ztid")).toString();
            int currentIndex = 0;
            for(int i = 0;i<13; i++)
                if(ztid == ztids[i].left(2))
                    { currentIndex = i;break; }
            QString name = query.value(query.record().indexOf("name")).toString();
            QString author = query.value(query.record().indexOf("author")).toString();
            QString press = query.value(query.record().indexOf("press")).toString();
            QString date = query.value(query.record().indexOf("date")).toString();
            QString isbn = query.value(query.record().indexOf("isbn")).toString();
            int edition = query.value(query.record().indexOf("edition")).toInt();
            double price = query.value(query.record().indexOf("price")).toDouble();
            int total = query.value(query.record().indexOf("total")).toInt();

            qDebug()<<id<<" "<<ztid<<" "<<name<<" "<<author<<" "<<press<<" "<<date<<" "<<isbn<<" "<<edition<<" "<<price<<" "<<total;

            int year = date.left(4).toInt();
            int month = date.mid(5,2).toInt();
            int day = date.right(2).toInt();
            QDate qdate(year,month,day);

            ui->tf_id->setText(id);
            //
            ui->cb_ztid->setCurrentIndex(currentIndex);
            ui->tf_name->setText(name);
            ui->tf_author->setText(author);
            ui->tf_press->setText(press);
            ui->dateEdit->setDate(qdate);
            ui->tf_isbn->setText(isbn);
            ui->sb_edition->setValue(edition);
            ui->dsp_price->setValue(price);
            ui->sb_total->setValue(total);
        }
        ui->tf_id->setEnabled(false);
        ui->btn_add->setText("修改");
    }
}

void AddBookBord::addButtonOnClicked(){
    QString id = ui->tf_id->text();
    QString ztid = ui->cb_ztid->currentText();
    if(ztid == "无分类")ztid = "";
    else ztid = ztid.left(2);
    QString name = ui->tf_name->text();
    QString author = ui->tf_author->text();
    QString press = ui->tf_press->text();
    QString date = ui->dateEdit->dateTime().toString("yyyy-M-d");
    QString isbn = ui->tf_isbn->text();
    int edition = ui->sb_edition->value();
    double price = ui->dsp_price->value();
    int total = ui->sb_total->value();
    QString sql,success,failed;
    if(type == "add") {
        sql = "INSERT INTO books(id,ztid,`name`,author,press,date,isbn,edition,price,total,`left`) VALUES(\'" + id + "\',\'" + ztid + "\',\'" + name + "\',\'" + author + "\',\'" + press + "\',\'" + date + "\',\'" + isbn + "\'," + QString("%1").arg(edition) + "," + QString("%1").arg(price) + "," + QString("%1").arg(total) + "," + QString("%1").arg(total) + ");";
        success = "添加成功！";
        failed = "添加失败！";
    }
    else if(type == "edit"){
        sql = "UPDATE books SET ztid = \'" + ztid + "\',`name` = \'" + name + "\',author = \'" + author + "\',press = \'" + press + "\',date = \'" + date + "\',isbn = \'" + isbn + "\',edition = " + QString("%1").arg(edition) + ",price = " + QString("%1").arg(price) + ",total = " + QString("%1").arg(total) + ",`left` = " + QString("%1").arg(total) + " WHERE id = \'"+ id +"\' ;";
        success = "更改成功！";
        failed = "更改失败！";
    }
    QSqlQuery query;
    bool ret = query.exec(sql);
    if(ret){
        QMessageBox::information(NULL,"提示",success);
        this->mb->booksInit();
    }
    else{
        QMessageBox::information(NULL,"提示",failed);
    }
    qDebug()<<ret<<" "<<sql<<" "<<id<<" "<<ztid<<" "<<name<<" "<<author<<" "<<press<<" "<<date<<" "<<isbn<<" "<<edition<<" "<<price<<" "<<total;
}
void AddBookBord::cancelButtonOnClicked(){
    this->close();
    delete this;
}


void AddBookBord::idEditFinished(){
    QString id = ui->tf_id->text();
    if(id.length() != 5 )ui->lb_idwarn->show();
    else ui->lb_idwarn->hide();
}
void AddBookBord::nameEditFinished(){
    QString name = ui->tf_name->text();
    if(name == NULL || name == "" )ui->lb_namewarn->show();
    else ui->lb_namewarn->hide();
}
void AddBookBord::authorEditFinished(){
    QString author = ui->tf_author->text();
    if(author == NULL || author == "" )ui->lb_authorwarn->show();
    else ui->lb_authorwarn->hide();
}
void AddBookBord::isbnEditFinished(){
    QString isbn = ui->tf_isbn->text();
    if(isbn.length() == 10 || isbn.length() == 13 )ui->lb_isbnwarn->hide();
    else ui->lb_isbnwarn->show();
}

AddBookBord::~AddBookBord()
{
    delete ui;
}
