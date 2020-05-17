#include "C_mysqlmanager.h"
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
C_MySQLManager::C_MySQLManager(QObject *parent)
    : QObject(parent)
{

}


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
            qDebug() << "Ok - requete";

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
QString C_MySQLManager::getGenre(int number){
    QSqlQuery requete;
    if(requete.exec("SELECT nom FROM genre WHERE id="+QString::number(number))) {
        qDebug() << "Ok - requete";
            return QVariant(requete.value("nom")).toString();


    }
    return "Inconnu";
}
void C_MySQLManager::deconnection(){
    m_dvdDB.close();
    emit disconnected();
}
QString C_MySQLManager::db()
{
return m_db;
}

void C_MySQLManager::setDb( QString db)
{
m_db = db;
}

QString C_MySQLManager::adress()
{
return m_adress;
}

void C_MySQLManager::setAdress(QString adress)
{
m_adress = adress;
}

int C_MySQLManager::port()
{
return m_port;
}

void C_MySQLManager::setPort(int port)
{
m_port = port;
}

QString C_MySQLManager::user()
{
return m_user;
}

void C_MySQLManager::setUser(QString user)
{
m_user = user;
}

QString C_MySQLManager::password()
{
return m_password;
}

void C_MySQLManager::setPassword(QString password)
{
m_password = password;
}
