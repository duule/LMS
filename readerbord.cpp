#include "readerbord.h"
#include "ui_readerbord.h"

ReaderBord::ReaderBord(QString id, QString name, QMainWindow* mainwindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReaderBord)
{
    ui->setupUi(this);
    this->readerid = id;
    this->readername = name;
    this->mainwindow = mainwindow;
    search = new Search(id,this);
    bb = new BorrowBord(this,this->readerid);
    ub = new UnBorrowBord(this,this->readerid);
    init();
    connect(ui->btn_search,SIGNAL(clicked(bool)),this,SLOT(searchButtonOnClicked()));
    connect(ui->btn_myInfo,SIGNAL(clicked(bool)),this,SLOT(myInfoButtonOnClicked()));
    connect(ui->btn_borrow,SIGNAL(clicked(bool)),this,SLOT(borrowButtonOnClicked()));
    connect(ui->btn_unborrow,SIGNAL(clicked(bool)),this,SLOT(unborrowButtonOnClicked()));
    connect(ui->btn_logout,SIGNAL(clicked(bool)),this,SLOT(logoutButtonOnClicked()));
}
void ReaderBord::init(){
    ui->lb_wealcom->setText("你好，" + this->readername);
    QString bookid ;
    QString bookname ;
    QStandardItemModel* qStandardItemModel = new QStandardItemModel(this);
    QSqlQuery query;
    query.exec("SELECT * FROM borrow");
    while(query.next())
    {
        int ridPos = query.record().indexOf("readerid");
        QString readerid = query.value(ridPos).toString();
        if(readerid == this->readerid){
            int bidPos = query.record().indexOf("bookid");
            bookid = query.value(bidPos).toString();
            QSqlQuery query2;
            query2.exec("SELECT * FROM books WHERE id = \'" + bookid + "\';");
            if(query2.next()){
                int bnamePos = query2.record().indexOf("name");
                bookname = query2.value(bnamePos).toString();
                QStandardItem* standarItem = new QStandardItem(bookid + " " + bookname);
                qStandardItemModel->appendRow(standarItem);
            }
        }
    }
    ui->listView->setModel(qStandardItemModel);
    query.exec("SELECT * FROM readers WHERE id = \'" + this->readerid + "\' ;");
    if(query.next()){
        int maxPos = query.record().indexOf("maxBorrow");
        int hasPos = query.record().indexOf("hasBorrow");
        QString maxBorrow = query.value(maxPos).toString();
        QString hasBorrow = query.value(hasPos).toString();
        int canBorrow = maxBorrow.toInt() - hasBorrow.toInt();
        ui->lb_maxBorrow->setText(maxBorrow);
        ui->lb_hasBorrow->setText(hasBorrow);
        ui->lb_canBorrow->setText(QString("%1").arg(canBorrow));
    }
}

void ReaderBord::searchButtonOnClicked(){
    search->show();
}
void ReaderBord::myInfoButtonOnClicked(){
    ReaderInfoBord* rib = new ReaderInfoBord(this->readerid);
    rib->show();
}
void ReaderBord::borrowButtonOnClicked(){
    bb->show();
}
void ReaderBord::unborrowButtonOnClicked(){
    ub->show();
}
void ReaderBord::logoutButtonOnClicked(){
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

ReaderBord::~ReaderBord()
{
    delete ui;
}
