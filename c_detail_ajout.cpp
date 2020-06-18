#include "c_detail_ajout.h"
#include "ui_c_detail_ajout.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>


C_detail_ajout::C_detail_ajout(QWidget *parent, QString titre, QString m_ID,QString titreFilm_1, QTextEdit *nom) :
    QDialog(parent),
    ui(new Ui::C_detail_ajout)
{
    ui->setupUi(this);
    ui->l_titre->setText(titre);
    ui->id_mondial->setText(m_ID);
    ui->txt_film->setText(titreFilm_1);
    this->m_nom=nom;

}
C_detail_ajout::~C_detail_ajout()
{
    delete ui;
}

void C_detail_ajout::on_btn_enregistrer_detail_clicked()
{


    QString texte = this->m_nom->toPlainText();

    QString ajout = ui->l_titre->text();
    QString ID_Mondial = ui->id_mondial->text();
    QString ajoutCnt = ui->txt_ajouter_detail->text();

    if(texte.length()==0){
        this->m_nom->setText(this->ui->txt_ajouter_detail->text());
    }else{
        this->m_nom->setText(texte+", "+this->ui->txt_ajouter_detail->text());
        QString qTexte = this->m_nom->toPlainText();

    }

    QSqlQuery query;
    if(ajout=="Ajouter acteur")
    {
    query.exec("INSERT INTO `dvdflix`.`acteur`(ID, ID_film, acteur) VALUES ('','"+ID_Mondial+"','"+ajoutCnt+"')");
    }
    else if(ajout=="Ajouter metteur en scène")
    {
    query.exec("INSERT INTO `dvdflix`.`scene`(ID, ID_film, scene ) VALUES ('','"+ID_Mondial+"','"+ajoutCnt+"')");
    }
    else if(ajout=="Ajouter réalisateur")
    {
    query.exec("INSERT INTO `dvdflix`.`realis`(ID, ID_film, realis) VALUES ('','"+ID_Mondial+"','"+ajoutCnt+"')");
    }
    else if(ajout=="Ajouter producteur")
    {
    query.exec("INSERT INTO `dvdflix`.`prod`(ID, ID_film, prod) VALUES ('','"+ID_Mondial+"','"+ajoutCnt+"')");
    }



    this->close();
}

