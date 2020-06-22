#ifndef C_BDDSECU_H
#define C_BDDSECU_H
#include <iostream>
#include "C_mysqlmanager.h"
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>


class C_bddSecu
{
public:

    C_bddSecu(C_MySQLManager *db=nullptr);
    void LireIni();
    void connection();

    bool verifCodeParent(QString codeLu, QString codeSaisi);

    QString getBDdvdUser() const;
    void setBDdvdUser(const QString &value);

    QString getBDdvdPass() const;
    void setBDdvdPass(const QString &value);

    QString getBDdvdAdr() const;
    void setBDdvdAdr(const QString &value);

    int getBDdvdPort() const;
    void setBDdvdPort(int value);

    QString getDvdFlixUser() const;

    QString getDvdFlixPass() const;

    QString getDvdFlixAdr() const;

    int getDvdFlixPort() const;

    void close();

private:
    C_MySQLManager *db;
    QString BDdvdUser;
    QString BDdvdPass;
    int BDdvdPort;
    QString BDdvdAdr;

    QString m_dvdFlixUser;
    QString m_dvdFlixPass;
    QString m_dvdFlixAdr;
    int m_dvdFlixPort;
};

#endif // C_BDDSECU_H
