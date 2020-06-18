#include "c_dbconfig.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <fstream>
#include "c_bddsecu.h"
#include <QMessageBox>
#include <QDialog>

const QString  userSecu = "root"; /**< TODO: describe */
const QString passSecu = "admin"; /**< TODO: describe */

/**
 * @fn C_DbConfig(QObject *parent)
 * @author: Barthelmebs Alexis
 * @brief Constructeur
 * @param parent
 */

C_DbConfig::C_DbConfig(QObject *parent)
: QObject(parent)
{

}
/**
 *@fn C_DbConfig()
 * @author  Barthelmebs Alexis
 * @brief
 * constructeur
 *
 */
C_DbConfig::C_DbConfig()
{

}

/**
 * @author Barthelmebs Alexis
 * @fn ~C_DbConfig()
 * @brief destructeur
 */
C_DbConfig::~C_DbConfig()
{

}

/**
 * @fn DbAdr() const
 * @author Barthelmebs Alexis
 * @brief getter Adresse
 *
 * @return QString
 */
QString C_DbConfig::DbAdr() const
{
    return m_DbAdr;
}

/**
 * @fn setDbAdr(const QString DbAdr)
 * @author Barthelmebs Alexis
 * @brief setter Adresse
 *
 * @param DbAdr
 */
void C_DbConfig::setDbAdr(const QString DbAdr)
{
    m_DbAdr = DbAdr;
}

/**
 * @fn DbPort() const
 * @author Barthelmebs Alexis
 * @brief getter Port
 *
 * @return int
 */
int C_DbConfig::DbPort() const
{
    return m_DbPort;
}

/**
 * @fn setDbPort(const int DbPort)
 * @author Barthelmebs Alexis
 * @brief  setter Port
 *
 * @param DbPort
 */
void C_DbConfig::setDbPort(const int DbPort)
{
    m_DbPort = DbPort;
}


/**
 * @fn C_DbConfig::MainDbConfig()
 * @author Barthelmebs Alexis
 * @brief C_DbConfig::MainDbConfig
 *
 * Lire fichier Ini pour récupération Port et Adresse BDD
 * Conection au serveur SQL
 * Création BDD Dvdflix
 * Création tables (Films, genre, genresfilm, param, stockage, stockage_film et bddsecu)
 * Remplissage des tables si nécessaire
 */

void C_DbConfig::MainDbConfig()

{
    //DEBUG
    qWarning()<<"Passage Main DB";
    LireIni();
    connection();
    creation_bdd_dvdflix();
    if(!creation_bdd_dvdflix()){
    QMessageBox msgBox;
    msgBox.setText("Base de donnée DvdFlix non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_film();
    if(!creation_tbl_film()){
    QMessageBox msgBox;
    msgBox.setText("Table Film non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_genre();
    if(!creation_tbl_genre()){
    QMessageBox msgBox;
    msgBox.setText("Table genre non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_genresfilm();
    if(!creation_tbl_genresfilm()){
    QMessageBox msgBox;
    msgBox.setText("Table GenresFilm non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_param();
    if(!creation_tbl_param()){
    QMessageBox msgBox;
    msgBox.setText("Table Param non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_stockage();
    if(!creation_tbl_stockage()){
    QMessageBox msgBox;
    msgBox.setText("Table Stockage non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_stockage_film();
    if(!creation_tbl_stockage_film()){
    QMessageBox msgBox;
    msgBox.setText("Table Stockage Film non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_acteur();
    if(!creation_tbl_acteur()){
    QMessageBox msgBox;
    msgBox.setText("Table Acteur non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_scene();
    if(!creation_tbl_scene()){
    QMessageBox msgBox;
    msgBox.setText("Table scene non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_realis();
    if(!creation_tbl_realis()){
    QMessageBox msgBox;
    msgBox.setText("Table realis non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_prod();
    if(!creation_tbl_prod()){
    QMessageBox msgBox;
    msgBox.setText("Table realis non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

    creation_tbl_bddSecu();
    if(!creation_tbl_bddSecu()){
    QMessageBox msgBox;
    msgBox.setText("Base de donnée DvdFlix non créée");
    msgBox.setStandardButtons(QMessageBox::Ok);}

}

/**
 * @fn C_DbConfig::LireIni()
 * @author Barthelmebs Alexis
 * @brief
 * Lecture du fichier Ini pour récupérer adresse et port
 *
 */
void C_DbConfig::LireIni()
{
C_bddSecu *secu = new C_bddSecu();
secu->LireIni();
setDbAdr(secu->getBDdvdAdr());
setDbPort(secu->getBDdvdPort());
}

/**
 * @fn C_DbConfig::connection()
 * @author Barthelmebs Alexis
 * @brief
 * Connection au serveur local
 *
 */
void C_DbConfig::connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName(userSecu);
    db.setPassword(passSecu);
    db.setHostName(DbAdr());
    db.setPort(DbPort());
    db.open();

}

/**
 * @fn creation_bdd_dvdflix()
 * @author Barthelmebs Alexis *
 * @brief
 * Creation bdd dvdflix
 *
 * @return bool
 */
bool C_DbConfig::creation_bdd_dvdflix()
{
    bool result= false;
    QSqlQuery query;
    try {

        result= query.exec("CREATE DATABASE dvdflix");
        result=true;
    }

    catch(QException){

        qWarning()<<"Erreur lors de la création de la base de données dvdflix: "<<query.lastError();
        result = false;
    }
    return result;
}
/**
 * @fn creation_tbl_film()
 * @author Barthelmebs Alexis
 * @brief
 * Creation table film
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_film()
{
    bool result = false;
    QSqlQuery query;
    try {

        result = query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`film` (id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "titre TINYTEXT NOT NULL,"
               "adulte TINYINT(1) NOT NULL,"
               "resume TEXT, poster_path TINYTEXT,"
               "backdrop TINYTEXT, titre_origin TINYTEXT,"
               "langue TINYTEXT NOT NULL,"
               "date_real DATE,"
               "video TINYTEXT,"
               "note FLOAT,"
               "vote_count INT(11),"
               "popularity TINYTEXT,"
               "id_film MEDIUMINT(9),"
               "date_enr TINYTEXT,"
               "stockage TINYTEXT,"
               "genre INT(11) NOT NULL)");

        result=true;
    }
    catch (QException)
    {

        qWarning()<<"Erreur lors de la création table film: "<<query.lastError();
        result=false;
    }
    return result;

}

/**
 * @fn creation_tbl_genre()
 * @author Barthelmebs Alexis
 * @brief
 * Creation table genre et remplissage des champs
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_genre()
{
    bool result = false;
    QSqlQuery query;
    try {


        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`genre` (id INT(11) PRIMARY KEY NOT NULL,"
               "nom TINYTEXT NOT NULL)");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES ('28','Action')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('12','Aventure')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('16','Animation')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('35','Comédie')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('80','Crime')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('99','Documentaire')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('18','Drame')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('0751','Famillial')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('14','Fantastique')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('36','Histoire')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('27','Horreur')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('10402','Musique')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('9648','Mystère')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('10749','Romance')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('878','Science-fiction')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('10770','Téléfilm')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('53','Thriller')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('10752','Guerre')");
        query.exec("INSERT INTO `dvdflix`.`genre`(id, nom) VALUES('37','Western')");
        result = true;
        }

    catch (QException) {

        qWarning()<<"Erreur lors de la création table genre: "<<query.lastError();
        result=false;
    }

    return result;

}

/**
 * @fn creation_tbl_genresfilm()
 * @author Barthelmebs Alexis
 *
 * @brief
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_genresfilm()
{
    bool result = false;
    QSqlQuery query;
    try{

        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`genresfilm` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "id_film INT(11) NOT NULL,"
               "genre INT(11) NOT NULL)");
        result = true;
    }
        catch (QException)
    {
        qWarning()<<"Erreur lors de la création table genresfilm: "<<query.lastError();
        result=false;
    }
    return result;
}

/**
 * @brief
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_param()
{
    bool result = false;
    QSqlQuery query;
    try {
        QString cheminTempo = qApp->applicationDirPath()+"/img_tempo";
        QString cheminFixe = qApp->applicationDirPath()+"/lib_img";
        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`param` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
           "tempoPath TINYTEXT NOT NULL,"
           "hardPath TINYTEXT NOT NULL,"
           "codeParental TINYTEXT)");
        query.exec("INSERT INTO `dvdflix`.`param`(ID, tempoPath, hardPath, codeParental) VALUES ('1','"+cheminTempo+"','"+cheminFixe+"','0000')");
        result = true;

    } catch (QException) {
        qWarning()<<"Erreur lors du setup de la table Param: "<<query.lastError();
        result=false;
    }
    return result;
}

/**
 * @brief
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_stockage()
{
    bool result = false;
    QSqlQuery query;
    try {
        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`stockage` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "stockage_lieu TINYTEXT NOT NULL)");
        result = true;

    } catch (QException) {
        qWarning()<<"Erreur lors du setup de la table Param: "<<query.lastError();
        result=false;

    }
    return result;
}

/**
 * @brief
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_stockage_film()
{   bool result = false;
    QSqlQuery query;
    try {
        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`stockagefilm` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "id_film INT(11) NOT NULL,"
               "stockage TINYTEXT NOT NULL)");
        result = true;

    } catch (QException) {
        qWarning()<<"Erreur lors du setup de la table Stockagefilm: "<<query.lastError();
        result=false;

    }
    return result;

}


/**
 * @brief
 *
 * @return bool
 */
bool C_DbConfig::creation_bdd_secu()
{
 bool result = false;
 QSqlQuery query;
 try {
         query.exec("CREATE DATABASE IF NOT EXISTS secu");
         result = true;

 } catch (QException) {
     qWarning()<<"Erreur lors du setup de la Bdd Secu: "<<query.lastError();
     result=false;

 }
 return result;

}

/**
 * @brief
 *
 * @return bool
 */
bool C_DbConfig::creation_tbl_bddSecu()
{
    bool result = true;
    QSqlQuery query;
    try {
        query.exec("CREATE TABLE IF NOT EXISTS `secu`.`bddSecu` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
           "utilisateurBdd VARCHAR(20) NOT NULL,"
           "motDePasseBdd VARCHAR(20)) NOT NULL,"
           "adresse VARCHAR(20) NOT NULL,"
           "port int(5) NOT NULL,");
        result = true;

    } catch (QException) {
        qWarning()<<"Erreur lors du setup de la Bdd Secu: "<<query.lastError();
        result=false;

    }
    return result;

}

bool C_DbConfig::creation_tbl_acteur()
{
    bool result = false;
    QSqlQuery query;
    try{

        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`acteur` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "id_film INT(11) NOT NULL,"
               "acteur VARCHAR(30) NOT NULL)");
        result = true;
    }
        catch (QException)
    {
        qWarning()<<"Erreur lors de la création table acteur: "<<query.lastError();
        result=false;
    }
    return result;
}

bool C_DbConfig::creation_tbl_scene()
{
    bool result = false;
    QSqlQuery query;
    try{

        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`scene` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "id_film INT(11) NOT NULL,"
               "scene VARCHAR(30) NOT NULL)");
        result = true;
    }
        catch (QException)
    {
        qWarning()<<"Erreur lors de la création table scene: "<<query.lastError();
        result=false;
    }
    return result;
}

bool C_DbConfig::creation_tbl_realis()
{
    bool result = false;
    QSqlQuery query;
    try{

        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`realis` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "id_film INT(11) NOT NULL,"
               "realis VARCHAR(30) NOT NULL)");
        result = true;
    }
        catch (QException)
    {
        qWarning()<<"Erreur lors de la création table realis: "<<query.lastError();
        result=false;
    }
    return result;
}

bool C_DbConfig::creation_tbl_prod()
{
    bool result = false;
    QSqlQuery query;
    try{

        query.exec("CREATE TABLE IF NOT EXISTS `dvdflix`.`prod` (ID INT(11) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "id_film INT(11) NOT NULL,"
               "prod VARCHAR(30) NOT NULL)");
        result = true;
    }
        catch (QException)
    {
        qWarning()<<"Erreur lors de la création table prod: "<<query.lastError();
        result=false;
    }
    return result;
}

