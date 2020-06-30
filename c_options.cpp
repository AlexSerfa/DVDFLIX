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


#include <QLineEdit>
#include <QIntValidator>


using namespace std;

const QString  userSecu = "root";
const QString passSecu = "admin";



/**/
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

C_options::C_options(QWidget *parent , QString _dvdAd, QString _dvdPass,QString _dvdUser,int _dvdport, QString code,C_MySQLManager *_sql)
    : QDialog(parent),
    ui(new Ui::C_options)
  ,sql()
  ,secu()
{
    sql = _sql;
    setDvdAdr(_dvdAd);
    setDvdPass(_dvdPass);
    setDvdUser(_dvdUser);
    setDvdport(_dvdport);
    ui->setupUi(this);
    LectureInfoDB();
    m_codeParentalLu = code;
    read();

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

    ui->txt_adrDbSecu->setText(QString::fromStdString(adr));
    ui->txt_portDbSecu->setText(QString::number(prt));
}

C_options::~C_options()
{
    delete ui;
}
/**
* @fn LectureInfoDB()
* @author: Mercier Laurent
* @date 06/06/2020
* @brief lecture des inofrmations de la table param de la DB dvdflix
*/
void C_options::LectureInfoDB(){

    setHardPath(sql->getHardPath());
    setTempoPath(sql->getTempoPath());
    setCodeParental(sql->getCodeParental());
    ui->txt_fixe->setText(getHardPath());
    ui->txt_tempo->setText(getTempoPath());
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

    QString lieuStock = ui->txt_lieuStockage->text();

    QSqlQuery query;
    if(lieuStock.length()>1) query.exec("INSERT INTO `dvdflix`.`stockage`(ID, stockage_lieu) VALUES ('','"+lieuStock+"')");

}

void C_options::setSql(C_MySQLManager *value)
{
    sql = value;
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
  /*  secu.LireIni();
    this->upd_secu = QSqlDatabase::addDatabase("QMYSQL","asd");
    upd_secu.setHostName(secu.getBDdvdAdr());
    upd_secu.setDatabaseName("security");
    upd_secu.setUserName(userSecu);
    upd_secu.setPassword(passSecu);
    upd_secu.setPort(secu.getBDdvdPort());*/
    bool ok = upd_secu.open();
    if(ok){
        QSqlQuery query(upd_secu);
        query.prepare("UPDATE `security`.`bddsecu` SET `utilisateurBdd` = '"+nomUt+"', `motDePasseBdd` = '"+pass+"', `adresse` = '"+adr+"', `port` =  '"+QString::number(port)+"' WHERE `bddsecu`.`ID` = 1;");
        query.exec();
    }
}
void C_options::read()
{
    secu.LireIni();
    this->upd_secu = QSqlDatabase::addDatabase("QMYSQL","asd");
    upd_secu.setHostName(secu.getBDdvdAdr());
    upd_secu.setDatabaseName("security");
    upd_secu.setUserName(userSecu);
    upd_secu.setPassword(passSecu);
    upd_secu.setPort(secu.getBDdvdPort());
    bool ok = upd_secu.open();
    if(ok){
        QSqlQuery query(upd_secu);
        query.prepare("SELECT* FROM `security`.`bddsecu` WHERE `ID` = 1;");
        query.exec();
        if( query.next()){
         ui->txt_utilisateur->setText( query.value("utilisateurBdd").toString());
         ui->txt_mdp->setText( query.value("MotDePasseBdd").toString());
         ui->txt_adresse->setText( query.value("adresse").toString());
         ui->txt_port->setText( query.value("port").toString());
        }
    }
}


void C_options::TexteChemin(QLineEdit *champTexte){
    QFileDialog f;
    f.setFileMode(QFileDialog::DirectoryOnly);
    f.setOption(QFileDialog::ShowDirsOnly,false);
    f.exec();
    champTexte->setText(f.selectedFiles().at(0));
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

}



void C_options::on_btn_enr_CP_clicked()
{
    QString codeP = ui->txt_code->text();
    QString nouveauCodeP = ui->txt_nCode->text();
    //sql names
    QString tempoPath = ui->txt_tempo->text();
    QString hardPath = ui->txt_fixe->text();

    if(codeP  == m_codeParentalLu && codeP.length() ==4)
    {
        /* création de la Regex */
        QRegExp Exp ("^[0-9]{4}$");
        if( nouveauCodeP.contains(Exp)){
            QSqlQuery c(upd_param);
            c.exec("UPDATE `param` SET `codeParental` = '"+nouveauCodeP+"' WHERE `ID` = 1;");
        }else{
            qWarning()<<"erreur de format";
            ui->error_list->setText("Le code parental doit etre de 4 chiffres");
        }

    }
        QSqlQuery q;
        q.exec("UPDATE `param` SET `tempoPath` = '"+tempoPath+"' WHERE `ID` = 1;");
        q.exec("UPDATE `param` SET `hardPath` = '"+hardPath+"' WHERE `ID` = 1;");
}

void C_options::on_btn_enr_BD_dvd_clicked()
{
    QString nom_utilisateur = ui->txt_utilisateur->text();
    QString mdp = ui->txt_mdp->text();
    QString adresse = ui->txt_adresse->text();
    QString port = ui->txt_port->text();
    /**
      vérification si les champs sont vides
    **/
    if(
            nom_utilisateur.length()<1 ||
            mdp.length()<1 ||
            adresse.length()<1 ||
            port.length()<1

            )
    {
        ui->error_list->setText("Veuillez remplir tous les champs");
    }else{
        update(nom_utilisateur,mdp,adresse,port.toInt());
    }
}
