#include "c_apropos.h"
#include "ui_c_apropos.h"

C_aPropos::C_aPropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C_aPropos)
{
    ui->setupUi(this);
    ui->lbl_logo->setPixmap(qApp->applicationDirPath()+"/lib_img/logo.png");
}

C_aPropos::~C_aPropos()
{
    delete ui;
}
