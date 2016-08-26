#include "readerinfobord.h"
#include "ui_readerinfobord.h"

ReaderInfoBord::ReaderInfoBord(QString readerId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderInfoBord)
{
    ui->setupUi(this);
    this->readerId = readerId;
    init();
    connect(ui->btn_changePassword,SIGNAL(clicked(bool)),this,SLOT(changePasswordButtonOnClicked()));
}
void ReaderInfoBord::init(){
    QSqlQuery query;
    query.exec("SELECT * FROM readers");
    while(query.next())
    {
        int idPos = query.record().indexOf("id");
        QString id = query.value(idPos).toString();
        if(this->readerId == id ){
            int namePos = query.record().indexOf("name");
            int departmentPos = query.record().indexOf("department");
            int typePos = query.record().indexOf("type");
            QString name = query.value(namePos).toString();
            QString department = query.value(departmentPos).toString();
            QString type = query.value(typePos).toString();
            ui->lb_id->setText(id);
            ui->lb_name->setText(name);
            ui->lb_department->setText(department);
            ui->lb_type->setText(type);
            return;
        }
    }
    qDebug()<<"error!!!";
}
    ChangePasswordBord* cpw = new ChangePasswordBord(this->readerId);
    cpw->show();
}

ReaderInfoBord::~ReaderInfoBord()
{
    delete ui;
}
