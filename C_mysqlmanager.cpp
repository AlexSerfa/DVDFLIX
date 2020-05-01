#include "C_mysqlmanager.h"
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
/**
 * @brief constructeur
 *
 * @param parent
 */
C_MySQLManager::C_MySQLManager(QObject *parent)
    : QObject(parent)
{

}


/**
 * @brief gere la connection à la base de donnée
 *
 * @param db
 * @param adress
 * @param port
 * @param user
 * @param password
 */
void C_MySQLManager::connection(QString db, QString adress, int port, QString user, QString password)
{
    m_dvdDB =QSqlDatabase::addDatabase("QMYSQL");
    m_dvdDB.setHostName(adress);
    m_dvdDB.setPort(port);
    m_dvdDB.setUserName(user);
    m_dvdDB.setPassword(password);
    m_dvdDB.setDatabaseName(db);
    if(m_dvdDB.open()) {
        qDebug() << "Ok - ouverture de la base de donnée";
        emit connected();
        // Exécution d'une requête
        QSqlQuery requete;
        if(requete.exec("SELECT * FROM genre")) {
            //DEBUG
            //qDebug() << "Ok - requete";

            // Boucle qui permet de parcourir les enregistrements renvoyés par la requête
            while(requete.next()) {
                // On accède ici aux différents champs par leurs noms, il est également possible
                // d'y accéder par leur index : requete.value(0)
                qDebug() << requete.value("id") << " " << requete.value("nom");
            }
        }
        else {
            // afficher un message explicite sur les causes de l'erreur
            qDebug() << requete.lastError();
        }
    }
    else {
        emit disconnected();
        qDebug() << "Echec d'ouverture de la base de donnée";
        qDebug() << m_dvdDB.lastError();
    }
}
/**
 * @brief recupère le genre de film d'apres le code genre
 *
 * @param number
 * @return QString
 */
QString C_MySQLManager::getGenre(int number){
    QSqlQuery requete;
    if(requete.exec("SELECT nom FROM genre WHERE id="+QString::number(number))) {
        //DEBUG 3l
        qWarning()<<"req first:"<<requete.first();
        //qWarning()<<requete.lastInsertId().toString();
        //qDebug() << "Ok - requete";
            return QVariant(requete.value("nom")).toString();
    }
    return "Inconnu";
}
/**
 * @brief gere la déconnection a la base de donnée
 *
 */
void C_MySQLManager::deconnection(){
    m_dvdDB.close();
    emit disconnected();
}
/**
 * @brief retourne le noom de la database
 *
 * @return QString
 */
QString C_MySQLManager::getDb()
{
    return m_db;
}

/**
 * @brief stock le nom de la database
 *
 * @param db
 */
void C_MySQLManager::setDb( QString db)
{
    m_db = db;
}

/**
 * @brief retourne l'adresse ip de la database
 *
 * @return QString
 */
QString C_MySQLManager::getAdress()
{
    return m_adress;
}

/**
 * @brief stock l'adresse ip de la database
 *
 * @param adress
 */
void C_MySQLManager::setAdress(QString adress)
{
    m_adress = adress;
}

/**
 * @brief retourne le  port de la database
 *
 * @return int
 */
int C_MySQLManager::getPort()
{
    return m_port;
}

/**
 * @brief stock le  port de la database
 *
 * @param port
 */
void C_MySQLManager::setPort(int port)
{
    m_port = port;
}

/**
 * @brief retourne le nom de l'utilisateur de la db
 *
 * @return QString
 */
QString C_MySQLManager::getUser()
{
    return m_user;
}

/**
 * @brief stock le nom de l'utilisateur de la db
 *
 * @param user
 */
void C_MySQLManager::setUser(QString user)
{
    m_user = user;
}

/**
 * @brief retourne le mot de passe de la db
 *
 * @return QString
 */
QString C_MySQLManager::getPassword()
{
    return m_password;
}

/**
 * @brief stock le password de la db
 *
 * @param password
 */
void C_MySQLManager::setPassword(QString password)
{
    m_password = password;
}
