#ifndef C_APROPOS_H
#define C_APROPOS_H

#include <QDialog>

namespace Ui {
class C_aPropos;
}

class C_aPropos : public QDialog
{
    Q_OBJECT

public:
    explicit C_aPropos(QWidget *parent = nullptr);
    ~C_aPropos();

private:
    Ui::C_aPropos *ui;
};

#endif // C_APROPOS_H
