#ifndef C_MYSQLMANAGER_H
#define C_MYSQLMANAGER_H
#include <QtCore>
#include <QSql>
#include <QSqlDatabase>
#include <C_minifilm.h>
#include <c_biblio.h>

#include <QMainWindow>
/**
 * @brief
 *
 */
class C_MySQLManager: public QObject
{
    Q_OBJECT
public:
     QString getCodeParental();
    /**
     * @brief
     *
     * @param parent
     */
    explicit C_MySQLManager(QObject *parent = nullptr, C_biblio *_biblio=nullptr);

    /**
     * @brief gere la connection a la db
     *
     * @param db
     * @param adress
     * @param port
     * @param user
     * @param password
     */
    bool connection(QString db,QString adress,int port,QString user,QString password);
    /**
     * @brief gere la deconnection de la db
     *
     */
    void deconnection();
    QStringList getStockageList();
    QString getStockage(int id_film);
    bool close();
    bool suppressionFilm(QString idFilm);
   void searchTitre(QString titre);
    /**
     * @brief
     *
     * @param db
     */
    void setDb(QString db);
    /**
     * @brief
     *
     * @param adress
     */
    void setAdress(QString adress);
    /**
     * @brief
     *
     * @param port
     */
    void setPort(int port);
    /**
     * @brief
     *
     * @param user
     */
    void setUser(QString user);
    /**
     * @brief
     *
     * @param password
     */
    void setPassword(QString password);
    /**
     * @brief
     *
     * @param int
     * @return QString
     */
    QString getGenre(int);
    /**
     * @brief recherche le nombre de film corrrespondant au texte entré la recherche dans la fenetre principale et retourne les info contenues dans la db après création d'un C_miniFilm
     *
     * @param QString
     * @return int
     */
    int filmCount(QString titre);
    int getFilmCount();
    void resetResultCounter();
    bool saveFilm(C_miniFilm  &film);
    bool updateFilm(C_miniFilm  &film);
    QString getHardPath();
    QString getTempoPath();


public slots:
    void modification();
signals:
    void modifier();
    /**
     * @brief
     *
     */
    void connected();
    /**
     * @brief
     *
     */
    void disconnected();


//void setFilm(C_miniFilm  &film);
private:

    C_biblio *dvdtheque;
    QSqlDatabase m_dvdDB; /**< database objet */
    QString m_db; /**< nom de la db */
    QString m_adress; /**< adresse de la db */
    int m_port; /**< port de la db */
    QString m_user; /**< nom de l'utilisteur de la db */
    QString m_password; /**< password de la db */
    int m_resultCounter=0;/**< pcompteur de resultat lors d'une recherche de film dans la db */
    QDate QstringToQDate(QString date);
    /**
     * @brief
     *
     * @return QString
     */
    QString getDb();
    /**
     * @brief
     *
     * @return QString
     */
    QString getAdress() ;
    /**
     * @brief
     *
     * @return int
     */
    int getPort();
    /**
     * @brief
     *
     * @return QString
     */
    QString getUser();
    /**
     * @brief
     *
     * @return QString
     */
    QString getPassword();



};

#endif // C_MYSQLMANAGER_H

