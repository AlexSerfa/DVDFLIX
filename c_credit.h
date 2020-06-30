#ifndef C_CREDIT_H
#define C_CREDIT_H

#include <QDialog>

namespace Ui {
class C_credit;
}

class C_credit : public QDialog
{
    Q_OBJECT

public:
    explicit C_credit(QWidget *parent = nullptr);
    ~C_credit();

private slots:
    void on_btn_ok_clicked();

private:
    Ui::C_credit *ui;
};

#endif // C_CREDIT_H
