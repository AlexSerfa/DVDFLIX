#include "C_censure.h"
#include "ui_C_censure.h"

/**
 * @author: Mercier Laurent
 * @date 29/05/2020
 * @brief  constructeur
 *
 */
C_Censure::C_Censure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_Censure)
{
    ui->setupUi(this);
    this->show();
    ui->lbl_censure->setPixmap(qApp->applicationDirPath()+"/lib_img/censored.png");
}
/**
 * @author: Mercier Laurent
 * @date 29/05/2020
 * @brief  destructeur
 *
 */
C_Censure::~C_Censure()
{
    delete ui;
}
