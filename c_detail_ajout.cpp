#include "c_detail_ajout.h"
#include "ui_c_detail_ajout.h"
#include <QDebug>

C_detail_ajout::C_detail_ajout(QWidget *parent, QString titre, QTextEdit *q) :
    QDialog(parent),
    ui(new Ui::C_detail_ajout)
{
    ui->setupUi(this);
    ui->l_titre->setText(titre);
    this->q=q;
}

C_detail_ajout::~C_detail_ajout()
{
    delete ui;
}

void C_detail_ajout::on_btn_enregistrer_detail_clicked()
{
    QString s = this->q->toPlainText();
    if(s.length()==0){
        this->q->setText(this->ui->txt_ajouter_detail->text());
    }else{
        this->q->setText(s+", "+this->ui->txt_ajouter_detail->text());
        QString qs = this->q->toPlainText();

    }

    this->close();
}

