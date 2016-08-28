#include "addbookbord.h"
#include "ui_addbookbord.h"

AddBookBord::AddBookBord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBookBord)
{
    ui->setupUi(this);
    init();
    connect(ui->btn_add,SIGNAL(clicked(bool)),this,SLOT(addButtonOnClicked()));
    connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(cancelButtonOnClicked()));
    connect(ui->tf_id,SIGNAL(editingFinished()),this,SLOT(idEditFinished()));
    connect(ui->tf_name,SIGNAL(editingFinished()),this,SLOT(nameEditFinished()));
    connect(ui->tf_author,SIGNAL(editingFinished()),this,SLOT(authorEditFinished()));
    connect(ui->tf_isbn,SIGNAL(editingFinished()),this,SLOT(isbnEditFinished()));
}

void AddBookBord::init(){
    ui->cb_ztid->addItem("无分类");
    ui->cb_ztid->addItem("TB  一般工业技术");
    ui->cb_ztid->addItem("TD  矿业工程");
    ui->cb_ztid->addItem("TE  石油、天然气工业");
    ui->cb_ztid->addItem("TF  金工业");
    ui->cb_ztid->addItem("TG  金属学");
    ui->cb_ztid->addItem("TH  机械");
    ui->cb_ztid->addItem("TJ  武器工业");
    ui->cb_ztid->addItem("TK  动力工业");
    ui->cb_ztid->addItem("TL  原子能技术");
    ui->cb_ztid->addItem("TM  电工技术");
    ui->cb_ztid->addItem("TN  无线电电子学、通信技术");
    ui->cb_ztid->addItem("TP  自动化技术、计算技术");

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
    QString sql = "INSERT INTO books(id,ztid,`name`,author,press,date,isbn,edition,price,total,`left`) VALUES(\'" + id + "\',\'" + ztid + "\',\'" + name + "\',\'" + author + "\',\'" + press + "\',\'" + date + "\',\'" + isbn + "\'," + QString("%1").arg(edition) + "," + QString("%1").arg(price) + "," + QString("%1").arg(total) + "," + QString("%1").arg(total) + ");";
    QSqlQuery query;
    bool ret = query.exec(sql);
    if(ret){
        QMessageBox::information(NULL,"提示","添加成功！(" + id + ")");
    }
    else{
        QMessageBox::information(NULL,"提示","添加失败！(" + id + ")");
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
