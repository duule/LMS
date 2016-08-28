#include "search.h"
#include "ui_search.h"
#include <QDebug>

Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    init();
    searchButtonOnClicked();
    connect(ui->btn_search,SIGNAL(clicked(bool)),this,SLOT(searchButtonOnClicked()));
}
void Search::init(){
    ui->cb_ztid->addItem("  <请选择>");
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
}

void Search::searchButtonOnClicked(){
    QString id = ui->tf_id->text();
    QString name = ui->tf_name->text();
    QString author = ui->tf_author->text();
    QString press = ui->tf_press->text();
    QString isbn = ui->tf_isbn->text();
    QString edition = ui->tf_edition->text();
    QString ztid = ui->cb_ztid->currentText();


    QString sql = "SELECT * FROM books ";
    if((id == NULL || id == "" )&&(name == NULL || name == "" )&&(author == NULL || author == "" )&&(press == NULL || press == "" )&&(isbn == NULL || isbn == "" )&&(edition == NULL || edition == "" )&&(ztid == "  <请选择>")){
        sql += ";";
    }
    else{
        bool added = false;
        sql += "WHERE ";
        if (id != NULL && id != ""){
            sql += "id = ";
            sql += id;
            sql += " ";
            added = true;
        }
        if(name != NULL && name != ""){
            if(added) sql += "AND ";
            else added = true;
            sql += "name = \'";
            sql += name;
            sql += "\' ";
        }
        if(author != NULL && author != ""){
            if(added) sql += "AND ";
            else added = true;
            sql += "author = \'";
            sql += author;
            sql += "\' ";
        }
        if(press != NULL && press != ""){
            if(added) sql += "AND ";
            else added = true;
            sql += "press = \'";
            sql += press;
            sql += "\' ";
        }
        if(isbn != NULL && isbn != ""){
            if(added) sql += "AND ";
            else added = true;
            sql += "isbn = \'";
            sql += isbn;
            sql += "\' ";
        }
        if(ztid != "  <请选择>"){
            if(added) sql += "AND ";
            else added = true;
            sql += "ztid = \'";
            sql += ztid.left(2);
            sql += "\' ";
        }
        if(edition != NULL && edition != ""){
            if(added) sql += "AND ";
            else added = true;
            sql += "edition = ";
            sql += edition;
            sql += " ";
        }
        sql += ";";
    }
    qDebug()<<sql;
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(sql);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "中图法分类号");
    model->setHeaderData(2, Qt::Horizontal, "书名");
    model->setHeaderData(3, Qt::Horizontal, "作者");
    model->setHeaderData(4, Qt::Horizontal, "出版社");
    model->setHeaderData(5, Qt::Horizontal, "出版日期");
    model->setHeaderData(6, Qt::Horizontal, "ISBN");
    model->setHeaderData(7, Qt::Horizontal, "版次");
    model->setHeaderData(8, Qt::Horizontal, "价格");
    model->setHeaderData(9, Qt::Horizontal, "总量");
    model->setHeaderData(10,Qt::Horizontal, "可借");
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tableView->setModel(model);
    ui->lb_count->setText(QString("%1").arg(ui->tableView->model()->rowCount()));
}

Search::~Search()
{
    delete ui;
}
