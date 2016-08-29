#ifndef READERREGISTER_H
#define READERREGISTER_H

#include <QWidget>

namespace Ui {
class ReaderRegister;
}

class ReaderRegister : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderRegister(QWidget *parent = 0);
    ~ReaderRegister();

private:
    Ui::ReaderRegister *ui;
};

#endif // READERREGISTER_H
