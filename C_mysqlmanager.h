#ifndef C_MYSQLMANAGER_H
#define C_MYSQLMANAGER_H
#include <QtCore>
#include <QSql>
#include <QSqlDatabase>
#include <C_minifilm.h>
/**
 * @brief
 *
 */
class C_MySQLManager: public QObject
{
    Q_OBJECT
public:
     C_miniFilm *min1[150];   /*!< collection de minifiche après une recherche d'un film en local*/
    /**
     * @brief
     *
     * @param parent
     */
    explicit C_MySQLManager(QObject *parent = nullptr);

    /**
     * @brief gere la connection a la db
     *
     * @param db
     * @param adress
     * @param port
     * @param user
     * @param password
     */
    void connection(QString db,QString adress,int port,QString user,QString password);
    /**
     * @brief gere la deconnection de la db
     *
     */
    void deconnection();
    QStringList getStockageList();
    QString getStockage(int id_film);
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
    void videMinifilm();
bool saveFilm(C_miniFilm  &film);
signals:
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


    QSqlDatabase m_dvdDB; /**< database objet */
    QString m_db; /**< nom de la db */
    QString m_adress; /**< adresse de la db */
    int m_port; /**< port de la db */
    QString m_user; /**< nom de l'utilisteur de la db */
    QString m_password; /**< password de la db */
    int m_resultCounter=0;
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

