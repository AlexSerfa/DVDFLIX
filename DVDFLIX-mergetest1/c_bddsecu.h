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

/*
const QString databaseSecu ="bbdsecu";
const QString  userSecu = "root";
const QString passSecu = "admin";
*/

class C_bddSecu
{
public:
    C_bddSecu();
    C_bddSecu(QString databaseSecu,QString  userSecu,QString passSecu);

    //QString rnt_username();
private:
     QSqlDatabase db;
};

#endif // C_BDDSECU_H
