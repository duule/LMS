#ifndef EDITBOOKINFOBORD_H
#define EDITBOOKINFOBORD_H

#include <QDialog>

namespace Ui {
class EditBookInfoBord;
}

class EditBookInfoBord : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookInfoBord(QWidget *parent = 0);
    ~EditBookInfoBord();

private:
    Ui::EditBookInfoBord *ui;
};

#endif // EDITBOOKINFOBORD_H
