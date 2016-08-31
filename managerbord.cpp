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
    booksInit();
    readersInit();

    connect(ui->btn_changePassword,SIGNAL(clicked(bool)),this,SLOT(changePasswordButtonOnClicked()));
    connect(ui->btn_logout,SIGNAL(clicked(bool)),this,SLOT(logoutButtonOnClicked()));

    connect(ui->btn_search,SIGNAL(clicked(bool)),this,SLOT(searchBookButtonOnClicked()));
    connect(ui->btn_addBook,SIGNAL(clicked(bool)),this,SLOT(addBookButtonOnClicked()));
    connect(ui->btn_delBook,SIGNAL(clicked(bool)),this,SLOT(delBookButtonOnClicked()));
    connect(ui->btn_editBook,SIGNAL(clicked(bool)),this,SLOT(editBookButtonOnClicked()));
    connect(ui->btn_showReaders,SIGNAL(clicked(bool)),this,SLOT(showBook_sReadersButtonOnClicked()));

    connect(ui->btn_readerSearch,SIGNAL(clicked(bool)),this,SLOT(searchReaderButtonOnClicked()));
    connect(ui->btn_addReader,SIGNAL(clicked(bool)),this,SLOT(addReaderButtonOnClicked()));
    connect(ui->btn_delReader,SIGNAL(clicked(bool)),this,SLOT(delReaderButtonOnClicked()));
    connect(ui->btn_editReader,SIGNAL(clicked(bool)),this,SLOT(editReaderButtonOnClicked()));
    connect(ui->btn_verifyReader,SIGNAL(clicked(bool)),this,SLOT(verifyButtonOnClicked()));
    connect(ui->btn_showBooks,SIGNAL(clicked(bool)),this,SLOT(showReader_sBookButtonOnClicked()));
}

void ManagerBord::init(){
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

    ui->cb_readerType->addItem("全部");
    ui->cb_readerType->addItem("本科生");
    ui->cb_readerType->addItem("研究生");
    ui->cb_readerType->addItem("留学生");
    ui->cb_readerType->addItem("教师");
    ui->cb_readerType->addItem("管理员");

    ui->cb_readerVerify->addItem("全部");
    ui->cb_readerVerify->addItem("已审核");
    ui->cb_readerVerify->addItem("未审核");

    int total = 0, borrowed = 0, left = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM books ;");
    while(query.next()){
        total += query.value(query.record().indexOf("total")).toInt();
        left += query.value(query.record().indexOf("left")).toInt();
    }
    borrowed = total - left;
    ui->lb_totalBooks->setText(QString("%1").arg(total));
    ui->lb_borrowodBooks->setText(QString("%1").arg(borrowed));
    ui->lb_leftBooks->setText(QString("%1").arg(left));
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
    model->setHeaderData(7, Qt::Horizontal, "审核状态");
    model->setHeaderData(8, Qt::Horizontal, "可借阅天数");
    ui->tv_readers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_readers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_readers->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tv_readers->setModel(model);
    ui->tv_readers->setColumnHidden(4,true);
//    ui->tv_readers->setColumnWidth(2,120);
//    ui->tv_readers->setColumnWidth(3,62);
//    ui->tv_readers->setColumnWidth(5,55);
//    ui->tv_readers->setColumnWidth(6,55);
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
    if(ret == QMessageBox::Yes){
        this->mainwindow->show();
        this->close();
    }
}

//books
void ManagerBord::searchBookButtonOnClicked(){
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
    ui->tv_books->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_books->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_books->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tv_books->setModel(model);
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
void ManagerBord::showBook_sReadersButtonOnClicked(){
    QModelIndex row = ui->tv_books->currentIndex();
    QModelIndex xrow = ui->tv_books->model()->index(row.row(),0);
    QVariant data = ui->tv_books->model()->data(xrow);
    QString id = data.toString();
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Ok);
    qbox.setDefaultButton(QMessageBox::Ok);
    QString readerId,readerName,contact = "";
    QSqlQuery query;
    query.exec("SELECT * FROM borrow WHERE bookid = \'" + id + "\' ;");
    int i = 0;
    while(query.next())
    {
        if(i++ == 0)contact += "编号\t\t姓名\n";
        readerId = query.value(query.record().indexOf("readerid")).toString();
        QSqlQuery query2;
        query2.exec("SELECT * FROM readers WHERE id = \'" + readerId + "\' ;");
        if(query2.next()){
            readerName = query2.value(query2.record().indexOf("name")).toString();
            contact += readerId + "\t" + readerName + "\n";
        }
    }
    if(i == 0)contact = "暂无借阅者";
    qbox.setText(contact);
    qbox.exec();
}

//readers
void ManagerBord::searchReaderButtonOnClicked(){
    QString id = ui->tf_readerId->text();
    QString name = ui->tf_readerName->text();
    QString department = ui->tf_readerDepartment->text();
    QString type = ui->cb_readerType->currentText();
    QString verify = ui->cb_readerVerify->currentText();


    QString sql = "SELECT * FROM readers ";
    if((id == NULL || id == "" )&&(name == NULL || name == "" )&&(department == NULL || department == "" )&&(type == "全部")&&(verify == "全部")){
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
        if(department != NULL && department != ""){
            if(added) sql += "AND ";
            else added = true;
            sql += "department = \'";
            sql += department;
            sql += "\' ";
        }
        if(type != "全部"){
            if(added) sql += "AND ";
            else added = true;
            sql += "type = \'";
            sql += type;
            sql += "\' ";
        }
        if(verify != "全部"){
            if(added) sql += "AND ";
            else added = true;
            sql += "verify = \'";
            sql += verify;
            sql += "\' ";
        }
        sql += ";";
    }
    qDebug()<<sql;
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(sql);
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "所属单位");
    model->setHeaderData(3, Qt::Horizontal, "类型");
    model->setHeaderData(4, Qt::Horizontal, "密码");
    model->setHeaderData(5, Qt::Horizontal, "可借阅量");
    model->setHeaderData(6, Qt::Horizontal, "已借阅量");
    model->setHeaderData(7, Qt::Horizontal, "审核状态");
    model->setHeaderData(8, Qt::Horizontal, "可借阅天数");
    ui->tv_readers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_readers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_readers->setEditTriggers (QAbstractItemView::NoEditTriggers );
    ui->tv_readers->setModel(model);
}
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
    QMessageBox qbox;
    qbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    qbox.setDefaultButton(QMessageBox::Yes);
    qbox.setText("是否确定将此读者（" + id + "）从列表中删除？这将导致读者无法再进行借阅操作，并所有已借书籍将需要人力收回。");
    int ret = qbox.exec();
    if(ret == QMessageBox::Yes){
        bool ret = query.exec(sql);
        if(ret){
            QMessageBox::information(NULL,"提示","删除成功");
            this->readersInit();

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
