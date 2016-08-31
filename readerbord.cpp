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
    bk = new BookingBord(this,this->readerid);
    init();
    bookingInit();
    connect(ui->btn_search,SIGNAL(clicked(bool)),this,SLOT(searchButtonOnClicked()));
    connect(ui->btn_myInfo,SIGNAL(clicked(bool)),this,SLOT(myInfoButtonOnClicked()));
    connect(ui->btn_borrow,SIGNAL(clicked(bool)),this,SLOT(borrowButtonOnClicked()));
    connect(ui->btn_unborrow,SIGNAL(clicked(bool)),this,SLOT(unborrowButtonOnClicked()));
    connect(ui->btn_booking,SIGNAL(clicked(bool)),this,SLOT(bookingButtonOnClicked()));
    connect(ui->btn_logout,SIGNAL(clicked(bool)),this,SLOT(logoutButtonOnClicked()));
    connect(ui->btn_unbooking,SIGNAL(clicked(bool)),this,SLOT(unbookingButtonOnClicked()));
}
void ReaderBord::init(){
    ui->lb_wealcom->setText("你好，" + this->readername);
    QString bookid ;
    QString bookname ;
    QStandardItemModel* qStandardItemModel = new QStandardItemModel(this);
    qStandardItemModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("编号")));
    qStandardItemModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("状态")));
    qStandardItemModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("应还书日期")));
    qStandardItemModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("书名")));
    QSqlQuery query;
    query.exec("SELECT * FROM borrow");
    int i = 0;
    while(query.next())
    {
        int ridPos = query.record().indexOf("readerid");
        QString readerid = query.value(ridPos).toString();
        if(readerid == this->readerid){
            int bidPos = query.record().indexOf("bookid");
            int backDatePos = query.record().indexOf("shouldbackDate");
            bookid = query.value(bidPos).toString();
            QString backDateString = query.value(backDatePos).toString();
            QDate backDate = QDate(backDateString.left(4).toInt(),backDateString.mid(5,2).toInt(),backDateString.right(2).toInt());
            QDate currentDate = QDate::currentDate();
            QString dateInfo = backDateString;
            QString status;
            if(Tools::largerYearIsInLeft(backDate,currentDate)) status = "正常";
            else status = "已到期";
            QSqlQuery query2;
            query2.exec("SELECT * FROM books WHERE id = \'" + bookid + "\';");
            if(query2.next()){
                int bnamePos = query2.record().indexOf("name");
                bookname = query2.value(bnamePos).toString();
                QStandardItem* standarItem0 = new QStandardItem(bookid);
                QStandardItem* standarItem1 = new QStandardItem(status);
                QStandardItem* standarItem2 = new QStandardItem(dateInfo);
                QStandardItem* standarItem3 = new QStandardItem(bookname);
                qStandardItemModel->setItem(i,0,standarItem0);
                qStandardItemModel->setItem(i,1,standarItem1);
                qStandardItemModel->setItem(i,2,standarItem2);
                qStandardItemModel->setItem(i,3,standarItem3);
                if(status == "已过期"){
                    qStandardItemModel->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
                    qStandardItemModel->item(i,1)->setForeground(QBrush(QColor(255, 0, 0)));
                    qStandardItemModel->item(i,2)->setForeground(QBrush(QColor(255, 0, 0)));
                    qStandardItemModel->item(i,3)->setForeground(QBrush(QColor(255, 0, 0)));
                }
                i++;
            }
        }
    }
    ui->tableView->setModel(qStandardItemModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tableView->setColumnWidth(0,60);
    ui->tableView->setColumnWidth(1,60);

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
void ReaderBord::bookingInit(){
    QString sql = "SELECT * FROM booking WHERE readerid = \'" + this->readerid+ "\' ;";
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(sql);
    model->setHeaderData(0, Qt::Horizontal, "读者编号");
    model->setHeaderData(1, Qt::Horizontal, "书籍编号");
    model->setHeaderData(2, Qt::Horizontal, "预约开始");
    model->setHeaderData(3, Qt::Horizontal, "预约到期");
    ui->tv_booking->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_booking->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_booking->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tv_booking->setModel(model);
    ui->tv_booking->setColumnHidden(0,true);
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
void ReaderBord::bookingButtonOnClicked(){
    bk->show();
}

void ReaderBord::logoutButtonOnClicked(){
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    qbox.setDefaultButton(QMessageBox::Yes);
    qbox.setText("确定注销？");
    int ret = qbox.exec();
    if(ret == QMessageBox::Yes){
        this->mainwindow->show();
        this->close();
    }
}

void ReaderBord::unbookingButtonOnClicked(){
    QModelIndex row = ui->tv_booking->currentIndex();
    QModelIndex xrow = ui->tv_booking->model()->index(row.row(),1);
    QVariant data = ui->tv_booking->model()->data(xrow);
    QString bookingBookId = data.toString();
    if(bookingBookId == NULL || bookingBookId == ""){
        QMessageBox::information(NULL,"提示","输入为空！");
    }
    else{
        QSqlQuery query;
        QString sql = "DELETE FROM booking WHERE readerid = \'" + this->readerid + "\' AND bookid = \'" + bookingBookId + "\' LIMIT 1; ";
        qDebug()<<sql;
        QMessageBox qbox;
        qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        qbox.setDefaultButton(QMessageBox::Yes);
        qbox.setText("确定取消借阅？");
        int ret = qbox.exec();
        if(ret == QMessageBox::Yes){
            if(query.exec(sql)){
                QMessageBox::information(NULL,"提示","取消预约成功！");
                query.exec("SELECT * FROM books WHERE id = \'" + bookingBookId + "\' ;");
                query.next();
                int booking = query.value(query.record().indexOf("booking")).toInt() - 1;
                query.exec("UPDATE books SET booking = " +  QString("%1").arg(booking) + " WHERE id = \'" + bookingBookId + "\' ; ");
                bookingInit();
            }
            else{
                QMessageBox::information(NULL,"提示","取消预约失败！");
            }
        }
    }
}

ReaderBord::~ReaderBord()
{
    delete ui;
}
