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
    init();
    connect(ui->btn_search,SIGNAL(clicked(bool)),this,SLOT(searchButtonOnClicked()));
}
void ReaderBord::init(){
    ui->lb_wealcom->setText("你好，" + this->readername);
    QString bookid ;
    QString bookname ;
    QStandardItemModel* qStandardItemModel = new QStandardItemModel(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("LMS");
    db.setUserName("root");
    db.setPassword("Tami16.");
    if (!db.open()) {qDebug() << "Failed to connect to root mysql admin";return;}
    else{
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
            ui->lb_canBorrow->setText(QString(canBorrow));
        }
    }
}

void ReaderBord::searchButtonOnClicked(){
    Search* s = new Search();
    s->show();
}

ReaderBord::~ReaderBord()
{
    delete ui;
}
