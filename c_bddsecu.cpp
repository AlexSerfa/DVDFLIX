#include "c_bddsecu.h"
#include <QDebug>
#include <fstream>
#include <string>
using namespace std;

const QString databaseSecu ="security";
const QString  userSecu = "root";
const QString passSecu = "admin";
/**
 * @fn c_bddsecu
 * @author: Jovanovic Milan
 * @date 15/05/2020
 * @brief   Constructeur
 *
 *
 */

/**/

C_bddSecu::C_bddSecu(C_MySQLManager *_db)
{
   db= _db;
}
void C_bddSecu::LireIni()
{
    ifstream f;
    QDir::setCurrent(qApp->applicationDirPath());
    f.open("dvdflix.ini");

    string adr;
    int prt;
    f>>adr;
    QString adresse =QString::fromStdString(adr);
    setBDdvdAdr(adresse);
    cout<<adr<<endl;
    f>>prt;
    setBDdvdPort(prt);
    f.close();

    setBDdvdPass(passSecu);
    setBDdvdUser(userSecu);
}
void C_bddSecu::connection()
{
        QSqlQuery requete;
        requete.prepare("SELECT * FROM `bddsecu` WHERE `ID` = 1");
        requete.exec();
        if(requete.next()){
            m_dvdFlixUser =requete.value(1).toString();
            m_dvdFlixPass = requete.value(2).toString();
            m_dvdFlixAdr = requete.value(3).toString();
            m_dvdFlixPort =  requete.value(4).toInt();
      }

}

bool C_bddSecu::verifCodeParent(QString codeLu, QString codeSaisi)
{
    if(codeLu==codeSaisi){
        return true;
    }
    return false;
}
void C_bddSecu::close(){
    db->close();
}

QString C_bddSecu::getBDdvdUser() const
{
    return BDdvdUser;
}

void C_bddSecu::setBDdvdUser(const QString &value)
{
    BDdvdUser = value;
}

QString C_bddSecu::getBDdvdPass() const
{
    return BDdvdPass;
}

void C_bddSecu::setBDdvdPass(const QString &value)
{
    BDdvdPass = value;
}

QString C_bddSecu::getBDdvdAdr() const
{
    return BDdvdAdr;
}

void C_bddSecu::setBDdvdAdr(const QString &value)
{
    BDdvdAdr = value;
}

int C_bddSecu::getBDdvdPort() const
{
    return BDdvdPort;
}

void C_bddSecu::setBDdvdPort(int value)
{
    BDdvdPort = value;
}

QString C_bddSecu::getDvdFlixUser() const
{
    return m_dvdFlixUser;
}

QString C_bddSecu::getDvdFlixPass() const
{
    return m_dvdFlixPass;
}

QString C_bddSecu::getDvdFlixAdr() const
{
    return m_dvdFlixAdr;
}

int C_bddSecu::getDvdFlixPort() const
{
    return m_dvdFlixPort;
}

