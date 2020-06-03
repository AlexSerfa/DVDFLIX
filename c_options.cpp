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
#include "C_mysqlmanager.h"
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

C_options::C_options(QWidget *parent , QString _dvdAd, QString _dvdPass,QString _dvdUser,int _dvdport) :
    QDialog(parent),
    ui(new Ui::C_options)
  ,secu()
{
    setDvdAdr(_dvdAd);
    setDvdPass(_dvdPass);
    setDvdUser(_dvdUser);
    setDvdport(_dvdport);
    ui->setupUi(this);
    LectureInfoDB();



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
* @fn LectureInfoDB()
* @author: Mercier Laurent
* @date 03/06/2020
* @brief lecture des inofrmation de la table param de la DB dvdflix
*/
void C_options::LectureInfoDB(){
    C_MySQLManager *sql = new C_MySQLManager();
    sql->connection("dvdflix",getDvdAdr(),getDvdport(),getDvdUser(),getDvdPass());

    QSqlQuery requete;
    if(requete.exec("SELECT * FROM param WHERE ID=1"))
    {
       if( requete.next()){
        QString tempoPath =  QVariant(requete.value(1)).toString();
        QString hardPath =  QVariant(requete.value(2)).toString();
        QString codeParental =  QVariant(requete.value(3)).toString();
        setHardPath(hardPath);
        setTempoPath(tempoPath);
        setCodeParental(codeParental);
        qDebug()<<tempoPath;
        ui->txt_fixe->setText(getHardPath());
        ui->txt_tempo->setText(getTempoPath());

       }
    }
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

QString C_options::getCodeParental() const
{
    return m_codeParental;
}

void C_options::setCodeParental(const QString codeParental)
{
    m_codeParental = codeParental;
}

QString C_options::getTempoPath() const
{
    return m_tempoPath;
}

void C_options::setTempoPath(const QString tempoPath)
{
    m_tempoPath = tempoPath;
}

QString C_options::getHardPath() const
{
    return m_hardPath;
}

void C_options::setHardPath(const QString hardPath)
{
    m_hardPath = hardPath;
}

int C_options::getDvdport() const
{
    return dvdport;
}

void C_options::setDvdport(int value)
{
    dvdport = value;
}

QString C_options::getDvdUser() const
{
    return dvdUser;
}

void C_options::setDvdUser(const QString value)
{
    dvdUser = value;
}

QString C_options::getDvdPass() const
{
    return dvdPass;
}

void C_options::setDvdPass(const QString value)
{
    dvdPass = value;
}

QString C_options::getDvdAdr() const
{
    return dvdAdr;
}

void C_options::setDvdAdr(const QString value)
{
    dvdAdr = value;
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
    qWarning()<<"pass: "<<passSecu;
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



void C_options::TexteChemin(QLineEdit *champTexte){
    QFileDialog f;
    f.setFileMode(QFileDialog::DirectoryOnly);
    f.setOption(QFileDialog::ShowDirsOnly,false);

    f.exec();

    qDebug()<<f.directory().absolutePath();

    //création dossier
    QString folder = "/chemin temporaire";
    QString chemin = f.directory().absolutePath();

    qDebug()<<"chemin tempo: "<<chemin;

    champTexte->setText(chemin);

    QDir d = QDir::root();
    qDebug()<<d.mkpath(chemin+folder);
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
    TexteChemin(ui->txt_tempo);
 /*   QFileDialog f;

    f.setFileMode(QFileDialog::DirectoryOnly);
    f.setOption(QFileDialog::ShowDirsOnly,false);


    QStringList fileNames;
    if (f.exec())
        fileNames = f.selectedFiles();
    qDebug()<<"fichier selectionné: "<<fileNames;
    qDebug()<<f.directory().absolutePath();

    //création dossier
    QString folder = "/chemin temporaire";
    QString chemin = f.directory().absolutePath();

    qDebug()<<"chemin tempo: "<<chemin;

    ui->txt_tempo->setText(chemin);

    QDir d = QDir::root();
    qDebug()<<d.mkpath(chemin+folder);
    */
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
    TexteChemin(ui->txt_fixe);
    /*
    QFileDialog f;
    f.setFileMode(QFileDialog::DirectoryOnly);
    f.setOption(QFileDialog::ShowDirsOnly,false);


    QStringList fileNames;
    if (f.exec())
        fileNames = f.selectedFiles();
    qDebug()<<"fichier selectionné: "<<fileNames;
    qDebug()<<f.directory().absolutePath();

    qDebug()<<f.directory().absolutePath();
    //création dossier
    QString folder = "/chemin fixe";
    QString chemin = f.directory().absolutePath();
    //qDebug()<<"chemin fixe: "<<chemin;

    ui->txt_fixe->setText(chemin);

    QDir d = QDir::root();
    qDebug()<<d.mkpath(chemin+folder);*/
}


