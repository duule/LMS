#include "managerbord.h"
#include "ui_managerbord.h"

ManagerBord::ManagerBord(QMainWindow* mainwindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerBord)
{
    ui->setupUi(this);
    this->mainwindow = mainwindow;
    this->cp = new ChangePasswordBord("admin");

    init();

    connect(ui->btn_changePassword,SIGNAL(clicked(bool)),this,SLOT(changePasswordButtonOnClicked()));
    connect(ui->btn_logout,SIGNAL(clicked(bool)),this,SLOT(logoutButtonOnClicked()));
    connect(ui->btn_addBook,SIGNAL(clicked(bool)),this,SLOT(addBookButtonOnClicked()));
    connect(ui->btn_delBook,SIGNAL(clicked(bool)),this,SLOT(delBookButtonOnClicked()));
    connect(ui->btn_editBook,SIGNAL(clicked(bool)),this,SLOT(editBookButtonOnClicked()));
}

void ManagerBord::init(){
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
//    QMessageBox::question(NULL,"提示","是否确定将" + id + "下架？这将导致读者无法再借阅此书，并如有已借出去的书将需要人力收回。",QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes){
        bool ret = query.exec(sql);
        if(ret){
            QMessageBox::information(NULL,"提示","删除成功");
            this->init();

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

ManagerBord::~ManagerBord()
{
    delete ui;
}
