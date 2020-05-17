#include "c_bddsecu.h"
#include <QDebug>

/**
 * @fn c_bddsecu
 * @author: Jovanovic Milan
 * @date 15/05/2020
 * @brief
 *         création d'une nouvelle bdd sécurité
 *
 *
 */

C_bddSecu::C_bddSecu(QString databaseSecu,QString  userSecu,QString passSecu)
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName(databaseSecu);
    db.setUserName(userSecu);
    db.setPassword(passSecu);
    bool ok = db.open();

    if(ok){
        qDebug()<<"ok";
    }else{
        qDebug()<<"échec";
    }
}

/*QString C_bddSecu::rnt_username(){
    QSqlQuery query;
    query.exec("SELECT * FROM bddsecu");
    query.next();
    QString res = query.value(0).toString();
    qDebug()<<res;
    return res;
}*/
