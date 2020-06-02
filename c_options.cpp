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
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "c_bddsecu.h"
#include <fstream>

using namespace std;

const QString  userSecu = "root";
const QString passSecu = "admin";

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
  ,secu()
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

/**
* @fn c_option
* @author: Jovanovic Milan
* @date 11/05/2020
* @brief
*          lire/écrire fichier dvdflix.ini
*/
    ifstream f;
    QDir::setCurrent(qApp->applicationDirPath());
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

/**
 * @fn c_option
 * @author: Jovanovic Milan
 * @date 11/05/2020
 * @brief
 *          Forme option
 */
void C_options::on_pushButton_clicked()
{
    QString nom_utilisateur = ui->txt_utilisateur->text();
    QString mdp = ui->txt_mdp->text();
    QString adresse = ui->txt_adresse->text();
    QString port = ui->txt_port->text();
    QString tempo = ui->txt_tempo->text();
    QString fixe = ui->txt_fixe->text();
    QString codeP = ui->txt_code->text();




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
            //codeP.length()<1
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
        this->update(nom_utilisateur, mdp, adresse, port.toInt());

        this->upd_param = QSqlDatabase::addDatabase("QMYSQL","aaa");
        upd_param.setHostName(adresse);
        upd_param.setDatabaseName("dvdflix");
        upd_param.setUserName(nom_utilisateur);
        upd_param.setPassword(mdp);
        bool ok = upd_param.open();


//sql names
        QString tempoPath = ui->txt_tempo->text();
        QString hardPath = ui->txt_fixe->text();
        QString code = ui->txt_code->text();

/**
* @fn c_option
* @author: Jovanovic Milan
* @date 23/05/2020
* @brief
*          Update table param*/

        if(ok)
        {
            QSqlQuery q(upd_param);
            q.exec("UPDATE `param` SET `tempoPath` = '"+tempoPath+"' WHERE `ID` = 1;");
            q.exec("UPDATE `param` SET `hardPath` = '"+hardPath+"' WHERE `ID` = 1;");
            q.exec("UPDATE `param` SET `codeParental` = '"+code+"' WHERE `ID` = 1;");

        }
        else
        {
            qDebug()<<"error";
        }

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
 *         écrire données dans le fichier
 */
void C_options::on_pushButton_modifier_clicked()
{
    QString adrdbSecu = ui->txt_adrDbSecu->text();
    QString portdbSecu = ui->txt_portDbSecu->text();

    if(adrdbSecu.length()>5 && portdbSecu.length()>0){
        ofstream f;

        QDir::setCurrent(qApp->applicationDirPath());
        f.open("dvdflix.ini");

        f<<adrdbSecu.toLocal8Bit().constData()<<endl;
        f<<portdbSecu.toLocal8Bit().constData()<<endl;
        f.close();
        //this->close();
        ui->txt_adresse->setText(adrdbSecu);
        ui->txt_port->setText(portdbSecu);


    }
}
/**
 * @fn c_option
 * @author: Jovanovic Milan
 * @date 20/05/2020
 * @brief
 *          Update bdd secu
 */
void C_options::update(QString nomUt, QString pass, QString adr, int port)
{
    secu.LireIni();
    this->upd_secu = QSqlDatabase::addDatabase("QMYSQL","asd");
    upd_secu.setHostName(secu.getBDdvdAdr());
    upd_secu.setDatabaseName("security");
    upd_secu.setUserName(userSecu);
    upd_secu.setPassword(passSecu);
    upd_secu.setPort(secu.getBDdvdPort());
    bool ok = upd_secu.open();
//DEBUG
    qWarning()<<"adresse: "<<secu.getBDdvdAdr();
     qWarning()<<"port: "<<secu.getBDdvdPort();
      qWarning()<<"usser: "<<userSecu;
      qWarning()<<"usser: "<<passSecu;


    if(ok){
        qDebug()<<"connexion ok";
        QSqlQuery query(upd_secu);
    query.prepare("UPDATE `security`.`bddsecu` SET `utilisateurBdd` = '"+nomUt+"', `motDePasseBdd` = '"+pass+"', `adresse` = '"+adr+"', `port` =  '"+QString::number(port)+"' WHERE `bddsecu`.`ID` = 1;");
     //   query.exec("UPDATE `bddsecu` SET `utilisateurBdd` = '"+nomUt+"' WHERE `ID` = 1;");
     //   query.exec("UPDATE `bddsecu` SET `motDePasseBdd` = '"+pass+"' WHERE `ID` = 1;");
     //   query.exec("UPDATE `bddsecu` SET `adresse` = '"+adr+"' WHERE `ID` = 1;");
     //   query.exec("UPDATE `bddsecu` SET `port` = '"+QString::number(port)+"' WHERE `ID` = 1;");
query.exec();
    }else{
        qDebug()<<"connexion n'est pas OK";
    }
}


/**
 * @fn c_options
 * @author: Jovanovic Milan
 * @date 22/05/2020
 * @brief
 *         Path tempo
 */
void C_options::on_pushButton_cheminTempo_clicked()
{
    QFileDialog f;
    f.setFileMode(QFileDialog::DirectoryOnly);
    f.setOption(QFileDialog::ShowDirsOnly,false);
    f.exec();

    qDebug()<<f.directory().absolutePath();

    //création dossier
    QString folder = "/chemin temporaire";
    QString chemin = f.directory().absolutePath();

    qDebug()<<"chemin tempo: "<<chemin;

    ui->txt_tempo->setText(chemin);

    QDir d = QDir::root();
    qDebug()<<d.mkpath(chemin+folder);
}
/**
 * @fn c_options
 * @author: Jovanovic Milan
 * @date 22/05/2020
 * @brief
 *         Path fixe
 */
void C_options::on_pushButton_cheminFixe_clicked()
{
    QFileDialog f;
    f.setFileMode(QFileDialog::DirectoryOnly);
    f.setOption(QFileDialog::ShowDirsOnly,false);
    f.exec();

    qDebug()<<f.directory().absolutePath();
    //création dossier
    QString folder = "/chemin fixe";
    QString chemin = f.directory().absolutePath();
    qDebug()<<"chemin fixe: "<<chemin;

    ui->txt_fixe->setText(chemin);

    QDir d = QDir::root();
    qDebug()<<d.mkpath(chemin+folder);
}
