#ifndef C_MYSQLMANAGER_H
#define C_MYSQLMANAGER_H
#include <QtCore>
#include <QSql>
#include <QSqlDatabase>
class C_MySQLManager: public QObject
{
    Q_OBJECT
public:
    explicit C_MySQLManager(QObject *parent = nullptr);

    void connection(QString db,QString adress,int port,QString user,QString password);
    void deconnection();
    void setDb(QString db);
    void setAdress(QString adress);
    void setPort(int port);
    void setUser(QString user);
    void setPassword(QString password);
    QString getGenre(int);
signals:
    void connected();
    void disconnected();

private:
    QSqlDatabase m_dvdDB;
    QString m_db;
    QString m_adress;
    int m_port;
    QString m_user;
    QString m_password;
    QString db();
    QString adress() ;
    int port();
    QString user();
    QString password();


};

#endif // C_MYSQLMANAGER_H

