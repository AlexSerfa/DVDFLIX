#include "c_detail_ajout.h"
#include "ui_c_detail_ajout.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>

/**/
C_detail_ajout::C_detail_ajout(QWidget *parent, QString titre, QString m_ID, QTextEdit *q) :
    QDialog(parent),
    ui(new Ui::C_detail_ajout)
{
    ui->setupUi(this);
    ui->l_titre->setText(titre);
    ui->id_local->setText(m_ID);
    this->q=q;

}

C_detail_ajout::~C_detail_ajout()
{
    delete ui;
}

void C_detail_ajout::on_btn_enregistrer_detail_clicked()
{



    QString s = this->q->toPlainText();

    QString ajout = ui->l_titre->text();
    QString ID_Local = ui->id_local->text();
    QString ajoutCnt = ui->txt_ajouter_detail->text();

    if(s.length()==0){
        this->q->setText(this->ui->txt_ajouter_detail->text());
    }else{
        this->q->setText(s+", "+this->ui->txt_ajouter_detail->text());
        QString qs = this->q->toPlainText();

    }

    QSqlQuery query;
    if(ajout=="Ajouter acteur")
    {
    query.exec("INSERT INTO `dvdflix`.`acteur`(ID, ID_film, acteur) VALUES ('','"+ID_Local+"','"+ajoutCnt+"')");
    }
    else if(ajout=="Ajouter metteur en scène")
    {
    query.exec("INSERT INTO `dvdflix`.`scene`(ID, ID_film, scene ) VALUES ('','"+ID_Local+"','"+ajoutCnt+"')");
    }
    else if(ajout=="Ajouter réalisateur")
    {
    query.exec("INSERT INTO `dvdflix`.`realis`(ID, ID_film, realis) VALUES ('','"+ID_Local+"','"+ajoutCnt+"')");
    }
    else if(ajout=="Ajouter producteur")
    {
    query.exec("INSERT INTO `dvdflix`.`prod`(ID, ID_film, prod) VALUES ('','"+ID_Local+"','"+ajoutCnt+"')");
    }


    qWarning()<<"Acteur : "<<ajout;
    qWarning()<<"ID Local:"<<ID_Local;


    this->close();
}
