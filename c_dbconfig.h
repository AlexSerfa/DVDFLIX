#ifndef C_DBCONFIG_H
#define C_DBCONFIG_H
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>


class C_DbConfig: public QObject
{
    Q_OBJECT

public:
    C_DbConfig(QObject *parent = nullptr);
    C_DbConfig();
    ~C_DbConfig();

    QString DbAdr() const;
    void setDbAdr(const QString DbAdr);

    int DbPort() const;
    void setDbPort(const int DbPort);
    void MainDbConfig();

private slots:



private:

    QString m_DbAdr;
    int m_DbPort;
    void LireIni();

    void connection();
    bool creation_bdd_dvdflix();
    bool creation_tbl_film();
    bool creation_tbl_genre();
    bool creation_tbl_genresfilm();
    bool creation_tbl_param();
    bool creation_tbl_stockage();
    bool creation_tbl_stockage_film();
    bool creation_tbl_bddsecu();
    bool creation_tbl_acteur();
    bool creation_tbl_scene();
    bool creation_tbl_realis();
    bool creation_tbl_prod();
    bool creation_bdd_secu();
    bool creation_tbl_bddSecu();

};
#endif // C_DBCONFIG_H
