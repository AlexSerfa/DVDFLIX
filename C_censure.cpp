#include "C_censure.h"
#include "ui_C_censure.h"

C_Censure::C_Censure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_Censure)
{
    ui->setupUi(this);
    this->show();
}

C_Censure::~C_Censure()
{
    delete ui;
}