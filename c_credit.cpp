#include "c_credit.h"
#include "ui_c_credit.h"

/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  constructeur
 *
 */
C_credit::C_credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C_credit)
{
    ui->setupUi(this);

    ui->lbl_photo1->setPixmap(qApp->applicationDirPath()+"/lib_img/laurent.png");
    ui->lbl_photo2->setPixmap(qApp->applicationDirPath()+"/lib_img/milan.jpg");
    ui->lbl_photo3->setPixmap(qApp->applicationDirPath()+"/lib_img/alexis.jpg");

}
/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  destructeur
 *
 */
C_credit::~C_credit()
{
    delete ui;
}
/**
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief  gestion du click sur le bouton btn_ok
 *
 */
void C_credit::on_btn_ok_clicked()
{
    this->~C_credit();
}
