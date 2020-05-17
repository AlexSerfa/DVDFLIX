#include "c_options.h"
#include "ui_c_options.h"
#include <iostream>
#include "C_mysqlmanager.h"
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <string>

#include <fstream>

using namespace std;


/**
 * @fn c_option
 * @author: Jovanovic Milan
 * @date 11/05/2020
 * @brief
 *         création d'une nouvelle forme
 *         ajout des champs
 *         lire les valeurs bdd
 *
 */

C_options::C_options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C_options)
{
    ui->setupUi(this);

    /*
     ifstream a;
     a.open("dvdflix.ini");
     if(a.fail()){
         qDebug()<<"existe";
     }else{
         qDebug()<<"n'existe pas";
     }
*/


    ifstream f;
    f.open("dvdflix.ini");

    string adr;
    int prt;

    f>>adr;
    cout<<adr<<endl;
    f>>prt;

    f.close();

    ui->txt_adresse->setText(QString::fromStdString(adr));
    ui->txt_port->setText(QString::number(prt));
}

C_options::~C_options()
{
    delete ui;
}

void C_options::on_pushButton_clicked()
{
    QString nom_utilisateur = ui->txt_utilisateur->text();
    QString mdp = ui->txt_mdp->text();
    QString adresse = ui->txt_adresse->text();
    QString port = ui->txt_port->text();
    QString tempo = ui->txt_tempo->text();
    QString fixe = ui->txt_fixe->text();

    /**
      vérification si les champs sont vides
    **/
    if(
            nom_utilisateur.length()<1 ||
            mdp.length()<1 ||
            adresse.length()<1 ||
            port.length()<1 ||
            tempo.length()<1 ||
            fixe.length()<1
            )
    {
        ui->error_list->setText("Veuillez remplir tous les champs");
    }
    else
    {

        sql =new C_MySQLManager();
        connect(sql,SIGNAL(connected()),SLOT(infoConnection()));
        connect(sql,SIGNAL(disconnected()),SLOT(infoDeconnection()));
        sql->connection("dvdflix",adresse,port.toInt(),nom_utilisateur,mdp);

    }



}

void C_options::infoConnection()
{
    qDebug() << "Ok - ouverture de la base de donnée";
    ui->error_list->setText("Connexion réussie");
    disconnect(sql,SIGNAL(connected()),this,SLOT(infoConnection()));


}

void C_options::infoDeconnection()
{
    qDebug() << "KO - ouverture de la base de donnée échec";
    ui->error_list->setText("Connexion non réussie");
    disconnect(sql,SIGNAL(connected()),this,SLOT(infoConnection()));
    disconnect(sql,SIGNAL(disconnected()),this,SLOT(infoDeconnection()));
}

/**
 * @fn c_options
 * @author: Jovanovic Milan
 * @date 16/05/2020
 * @brief
 *         création fichier dvdflix.ini
 *         récuperation des valeurs pré-enregistrées
 *         modification des valeurs
 *         sauvgarde dans le fichier dvdflix.ini
 *
 *
 */
void C_options::on_pushButton_modifier_clicked()
{
    QString adrdbSecu = ui->txt_adrDbSecu->text();
    QString portdbSecu = ui->txt_portDbSecu->text();

    if(adrdbSecu.length()>5 && portdbSecu.length()>0){
        ofstream f;
        f.open("dvdflix.ini");
        f<<adrdbSecu.toLocal8Bit().constData()<<endl;
        f<<portdbSecu.toLocal8Bit().constData()<<endl;
        f.close();
        //this->close();
        ui->txt_adresse->setText(adrdbSecu);
        ui->txt_port->setText(portdbSecu);
    }
}
