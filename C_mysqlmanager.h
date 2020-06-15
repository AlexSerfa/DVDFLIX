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

    /**
    * @brief Constructeur
    *
    * @param parent
    * @param _biblio    pointeur sur l'objet C_biblio utilisé par l'application
    */

    explicit C_MySQLManager(QObject *parent = nullptr, C_biblio *_biblio=nullptr);


    /**
     * @brief retourne sous forme de QString le code parental enregistré dans la base de données
     *
     * @return QString  code parental lu
     */
    QString getCodeParental();
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
    /**
     * @brief      recupere les lieux de stockage disponible dans la base de données dvdflix
     *
     * @return QStringList  liste des lieux de stockage
     */
    QStringList getStockageList();
    /**
     * @brief      recupere le lieu de stockage du film
     *
     * @return QString      lieu de stockage
     */

    QString getStockage(int id_film);
    /**
     * @brief fermeture de la connexion a la base de données
     *
     * @return bool     indique que la fonction c'est bien déroulée
     */
    bool close();
    /**
     * @brief   suppression d'un film enregistré dans la base de données
     *
     * @param  QString   idFilm    identifaint  du film
     * @return bool                indique que la fonction c'est bien déroulée
     */
    bool suppressionFilm(QString idFilm);
   /**
    * @brief recherche les titres corrrespondant au texte entré la recherche dans la fenetre principale et retourne les info contenues dans la db après création d'un C_miniFilm
    *
    *  @return C_miniFilm*  minifilm du film trouvé
    */
   void searchTitre(QString titre);
    /**
    * @brief recupère le genre de film d'apres le code genre
    *
    * @param number    code genre
    * @return QString  genre du film
     */
    QString getGenre(int);

    /**
     * @brief recherche le nombre de film corrrespondant au texte entré la recherche dans la fenetre principale et retourne les info contenues dans la db après création d'un C_miniFilm
     *
     * @return int  nombre de film correspondant a une recherche dans la base de données
     */
    int getFilmCount();
    /**
     * @brief     réinitialisation du memebre m_resultCounter correspondant au nombre de resultat lors d'une recherche de film dans la base de données
     *
     */
    void resetResultCounter();
    /**
     * @brief       Enregistrement d'un fillm dans la table film de la base de données dvdflix
     *
     * @param film  minifilm du film concerné
     * @param _date_enr date d'enregistrement du film
     * @return bool indication que l'opération s'est dérouler correctement
     */
    bool saveFilm(C_miniFilm  &film, QString _date_enr, QString _stock);
    /**
    * @brief   enregistrement des modification apportées à un film enregistré
    *
    * @param film      minifilm du film modifier
    * @return bool     indique que la foncton c'est bien déroulée
     */
    bool updateFilm(C_miniFilm  &film);
    /**
     * @brief   effectue une recherche d'un nom dans l'une des tables : acteur, realis, producteur, scene
     *
     * @param nom       nom a rechercher dans la table
     * @param table     table de la  base de données dans la qu'elle la rechrche dot etre effectuée
     */
    void searchPersonne(QString nom, QString table);
    /**
     * @brief retourne le chemin de stockage des fichiers images téléchargés lors du recherche online
     *
     * @return QString  chemin des fichiers images des film enregistrés dans la base de données
     */
    QString getHardPath();
    /**
     * @brief   retourne le chemin de stockage des fichiers images téléchargés lors du recherche online chemin de stockage des fichiers images des film enregistré dans la base de données
     *
     * @return QString  chemin des fichier image temporaires
     */
    QString getTempoPath();

public slots:
    /**
    * @brief propagation du signal lors d'un modification d'un film enregistré dans la base de données
    *
    */
    void modification();

signals:
    /**
    * @brief propagation du signal lors d'un modification d'un film enregistré dans la base de données
    *
    */
    void modifier();
    /**
     * @brief   signal indiquant la connection à la base de données
     *
     */
    void connected();
    /**
     * @brief   signal indiquant une déconnexion a la base de données
     *
     */
    void disconnected();

private:
    C_biblio *dvdtheque;                /**< objet C_bilio utilisé par l'application lors de la recherche de film */
    QSqlDatabase m_dvdDB;               /**< database objet */
    QString m_db;                       /**< nom de la db */
    QString m_adress;                   /**< adresse de la db */
    int m_port;                         /**< port de la db */
    QString m_user;                     /**< nom de l'utilisteur de la db */
    QString m_password;                 /**< password de la db */
    int m_resultCounter=0;              /**< pcompteur de resultat lors d'une recherche de film dans la db */
    /**
     * @brief   transforme une QString en une QDate
     *
     * @return QDate    QDate en fonction de la QString passée en paramètres
     */
    QDate QstringToQDate(QString date);


};
#endif // C_MYSQLMANAGER_H
