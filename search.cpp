#include "search.h"
#include "ui_search.h"
#include "readerbord.h"
#include <QDebug>

Search::Search(QString readerId,ReaderBord* readerbord, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    this->readerId = readerId;
    this->readerbord = readerbord;
    init();
    searchButtonOnClicked();
    connect(ui->btn_search,SIGNAL(clicked(bool)),this,SLOT(searchButtonOnClicked()));
    connect(ui->btn_borrow,SIGNAL(clicked(bool)),this,SLOT(borrowButtonOnClicked()));
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
void Search::borrowButtonOnClicked(){
    QModelIndex row = ui->tableView->currentIndex();
    QModelIndex xrow = ui->tableView->model()->index(row.row(),0);
    QVariant data = ui->tableView->model()->data(xrow);
    QString borrowBookId = data.toString();
    if(borrowBookId == NULL || borrowBookId == ""){
        QMessageBox::information(NULL,"提示","输入为空！");
    }
    else{
        QSqlQuery query,query2,query3;
        query.exec("SELECT * FROM books WHERE id = \'" + borrowBookId + "\' ;");
        query2.exec("SELECT * FROM readers WHERE id = \'" + this->readerId + "\' ;");
        query3.exec("SELECT * FROM borrow WHERE readerid = \'" + this->readerId + "\' ;");
        if(query.next()&&query2.next()){
            int leftPos = query.record().indexOf("left");
            int left = query.value(leftPos).toInt();
            int hasBorrowPos = query2.record().indexOf("hasBorrow");
            int canBorrowPos = query2.record().indexOf("maxBorrow");
            int daylongPos = query2.record().indexOf("daylong");
            int hasBorrow = query2.value(hasBorrowPos).toInt();
            int canBorrow = query2.value(canBorrowPos).toInt();
            int daylong = query2.value(daylongPos).toInt();
            query3.next();
            QString backDateString = query3.value(query3.record().indexOf("shouldbackDate")).toString();
            QDate backDate = QDate(backDateString.left(4).toInt(),backDateString.mid(5,2).toInt(),backDateString.right(2).toInt());
            QDate currentDate = QDate::currentDate();
            if(Tools::largerYearIsInLeft(backDate,currentDate)){
                if(left > 0){
                    if(hasBorrow < canBorrow){
                        int newLeft = left - 1;
                        int newHasBorrow = hasBorrow + 1;
                        QString borrowDate = QDate::currentDate().toString("yyyy-MM-dd");
                        QString backDate = Tools::addDaysOnDate(QDate::currentDate(),daylong).toString("yyyy-MM-dd");
                        QString sql = "INSERT INTO borrow(readerid,bookid,borrowDate,shouldbackDate) VALUES(\'" + this->readerId + "\',\'" + borrowBookId + "\',\'" + borrowDate + "\',\'" + backDate + "\')";
                        if(query.exec(sql)){
                            QMessageBox::information(NULL,"提示","借阅成功");
                            query.exec("UPDATE books SET `left` = " + QString("%1").arg(newLeft) + " WHERE id = \'" + borrowBookId + "\' ;");
                            query.exec("UPDATE readers SET `hasBorrow` = " + QString("%1").arg(newHasBorrow) + " WHERE id = \'" + this->readerId + "\' ;");
                            readerbord->init();
                            return;
                        }
                        else{
                            QMessageBox::information(NULL,"提示","借阅失败");
                            qDebug()<<sql;
                            return;
                        }
                    }
                    else{
                        QMessageBox::information(NULL,"提示","您已达到最大借阅数量，无法继续借阅，请先还书。");
                        return;
                    }
                }
                else{
                    QMessageBox::information(NULL,"提示","书籍可借剩余量不足！");
                    return;
                }
            }
            else {
                QMessageBox::information(NULL,"提示","您还有逾期的书籍没有还，请先还书后再进行借阅操作。");
                return;
            }
        }
        QMessageBox::information(NULL,"提示","未查询到相应书籍！");
    }
}

Search::~Search()
{
    delete ui;
}
