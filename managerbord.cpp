#include "managerbord.h"
#include "ui_managerbord.h"

ManagerBord::ManagerBord(QMainWindow* mainwindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerBord)
{
    ui->setupUi(this);
    this->mainwindow = mainwindow;
    this->cp = new ChangePasswordBord("admin");

    booksInit();
    readersInit();

    connect(ui->btn_changePassword,SIGNAL(clicked(bool)),this,SLOT(changePasswordButtonOnClicked()));
    connect(ui->btn_logout,SIGNAL(clicked(bool)),this,SLOT(logoutButtonOnClicked()));

    connect(ui->btn_addBook,SIGNAL(clicked(bool)),this,SLOT(addBookButtonOnClicked()));
    connect(ui->btn_delBook,SIGNAL(clicked(bool)),this,SLOT(delBookButtonOnClicked()));
    connect(ui->btn_editBook,SIGNAL(clicked(bool)),this,SLOT(editBookButtonOnClicked()));

    connect(ui->btn_addReader,SIGNAL(clicked(bool)),this,SLOT(addReaderButtonOnClicked()));
    connect(ui->btn_delReader,SIGNAL(clicked(bool)),this,SLOT(delReaderButtonOnClicked()));
    connect(ui->btn_editReader,SIGNAL(clicked(bool)),this,SLOT(editReaderButtonOnClicked()));
    connect(ui->btn_verifyReader,SIGNAL(clicked(bool)),this,SLOT(verifyButtonOnClicked()));
    connect(ui->btn_showBooks,SIGNAL(clicked(bool)),this,SLOT(showReader_sBookButtonOnClicked()));
}

void ManagerBord::booksInit(){
    QString sql = "SELECT * FROM books ;";
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
    ui->tv_books->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_books->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_books->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tv_books->setModel(model);
}
void ManagerBord::readersInit(){
    QString sql = "SELECT * FROM readers ;";
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(sql);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "所属单位");
    model->setHeaderData(3, Qt::Horizontal, "类型");
    model->setHeaderData(4, Qt::Horizontal, "密码");
    model->setHeaderData(5, Qt::Horizontal, "可借阅量");
    model->setHeaderData(6, Qt::Horizontal, "已借阅量");
    ui->tv_readers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_readers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_readers->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tv_readers->setModel(model);
    ui->tv_readers->setColumnHidden(4,true);
    ui->tv_readers->setColumnWidth(2,120);
    ui->tv_readers->setColumnWidth(3,62);
    ui->tv_readers->setColumnWidth(5,55);
    ui->tv_readers->setColumnWidth(6,55);
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

//books
void ManagerBord::addBookButtonOnClicked(){
    AddBookBord* add = new AddBookBord(this,"add");
    add->show();
}
void ManagerBord::delBookButtonOnClicked(){
    QModelIndex row = ui->tv_books->currentIndex();
    QModelIndex xrow = ui->tv_books->model()->index(row.row(),0);
    QVariant data = ui->tv_books->model()->data(xrow);
    QString id = data.toString();
    QSqlQuery query;
    QString sql = "DELETE FROM books WHERE id = \'" + id + "\' ;";
    qDebug()<<sql;
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    qbox.setDefaultButton(QMessageBox::Yes);
    qbox.setText("是否确定将" + id + "下架？这将导致读者无法再借阅此书，并如有已借出去的书将需要人力收回。");
    int ret = qbox.exec();
    if(ret == QMessageBox::Yes){
        bool ret = query.exec(sql);
        if(ret){
            QMessageBox::information(NULL,"提示","删除成功");
            this->booksInit();

        }
        else {
            QMessageBox::information(NULL,"提示","删除失败");
        }
    }
}
void ManagerBord::editBookButtonOnClicked(){
    QModelIndex row = ui->tv_books->currentIndex();
    QModelIndex xrow = ui->tv_books->model()->index(row.row(),0);
    QVariant data = ui->tv_books->model()->data(xrow);
    QString id = data.toString();
    AddBookBord* add = new AddBookBord(this,"edit",id);
    add->show();
}

//readers
void ManagerBord::addReaderButtonOnClicked(){
    AddReaderBord* add = new AddReaderBord(this,"add");
    add->show();
}
void ManagerBord::delReaderButtonOnClicked(){
    QModelIndex row = ui->tv_readers->currentIndex();
    QModelIndex xrow = ui->tv_readers->model()->index(row.row(),0);
    QVariant data = ui->tv_readers->model()->data(xrow);
    QString id = data.toString();
    QSqlQuery query;
    QString sql = "DELETE FROM readers WHERE id = \'" + id + "\' ;";
    qDebug()<<sql;
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    qbox.setDefaultButton(QMessageBox::Yes);
    qbox.setText("是否确定将此读者（" + id + "）从列表中删除？这将导致读者无法再进行借阅操作，并所有已借书籍将需要人力收回。");
    int ret = qbox.exec();
    if(ret == QMessageBox::Yes){
        bool ret = query.exec(sql);
        if(ret){
            QMessageBox::information(NULL,"提示","删除成功");
            this->booksInit();

        }
        else {
            QMessageBox::information(NULL,"提示","删除失败");
        }
    }
}
void ManagerBord::editReaderButtonOnClicked(){
    QModelIndex row = ui->tv_readers->currentIndex();
    QModelIndex xrow = ui->tv_readers->model()->index(row.row(),0);
    QVariant data = ui->tv_readers->model()->data(xrow);
    QString id = data.toString();
    AddReaderBord* add = new AddReaderBord(this,"edit",id);
    add->show();
}
void ManagerBord::verifyButtonOnClicked(){
    QModelIndex row = ui->tv_readers->currentIndex();
    QModelIndex xrow = ui->tv_readers->model()->index(row.row(),0);
    QVariant data = ui->tv_readers->model()->data(xrow);
    QString id = data.toString();
    QSqlQuery query;
    if(query.exec("UPDATE readers SET verify = \'已审核\' WHERE id = \'" + id + "\' ;")){
        QMessageBox::information(NULL,"提示","审核成功！");
        readersInit();
    }
    else QMessageBox::information(NULL,"提示","审核失败！");
}
void ManagerBord::showReader_sBookButtonOnClicked(){
    QModelIndex row = ui->tv_readers->currentIndex();
    QModelIndex xrow = ui->tv_readers->model()->index(row.row(),0);
    QVariant data = ui->tv_readers->model()->data(xrow);
    QString id = data.toString();
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Ok);
    qbox.setDefaultButton(QMessageBox::Ok);
    QString bookId,bookName,contact = "";
    QSqlQuery query;
    query.exec("SELECT * FROM borrow WHERE readerid = \'" + id + "\' ;");
    int i = 0;
    while(query.next())
    {
        if(i++ == 0)contact += "编号\t书名\n";
        bookId = query.value(query.record().indexOf("bookid")).toString();
        QSqlQuery query2;
        query2.exec("SELECT * FROM books WHERE id = \'" + bookId + "\' ;");
        if(query2.next()){
            bookName = query2.value(query2.record().indexOf("name")).toString();
            contact += bookId + "\t" + bookName + "\n";
        }
    }
    if(i == 0)contact = "暂无已借书籍";
    qbox.setText(contact);
    qbox.exec();
}

ManagerBord::~ManagerBord()
{
    delete ui;
}
