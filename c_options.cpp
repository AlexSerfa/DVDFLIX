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
using namespace std;

C_options::C_options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C_options)
{
    ui->setupUi(this);
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
