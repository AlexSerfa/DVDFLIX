#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <C_minifilm.h>
#include <C_downloadmanager.h>
#include <C_mysqlmanager.h>
#include <c_bddsecu.h>
#include <c_options.h>
#include <QVBoxLayout>
#include <C_censure.h>
#include <c_biblio.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief constructeur
     *
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief   destructeur
     *
     */
    ~MainWindow();

public slots:
    /**
     * @brief   -lecture du fichier saveMovies.json
     *          -recuperation du titre des films
     *          -recuperaton de l'affiche du film
     *          -ajout a la queue du downbloadManager
     *          -creation de la minifilm
     *          -insertion des valeur recupérées
     *          -insertion dans dvdtheque->min2[] de la fiche de chaque film
     *
     */
    void readJson();
    /**
     * @brief   affichage du texte de statut de la base de données dvdflix dans le groupe box de statut lorsque la db est déconnectée
     *
     */
    void status_dbConnectee();
    /**
     * @brief   affichage du texte de statut de la base de données dvdflix dans le groupe box de statut lorsque la db est déconnectée
     *
     */
    void status_dbDeconnectee();
    /**
     * @brief selectionne les fonctions a éffectuer en fonction du type de recherche demandé
     *
     * @param value
     */
    void rechercheFilm(int value);
    /**
     * @brief vérification et création des dossier img_tempo et lib_img
     *
     */
    void imageChemin();

private slots:
    /**
     * @brief   Lancement de la recherche a partir ddes informations saisies par l'utilisateur du film
     *
     */
    void on_btn_rechercher_clicked();
    /**
     * @brief    -Lecture du fichier dvdfllix.ini
     *          -connection à la base de données Security
     *          -création et affichage de la fenetre option avec passage des parametre de connection à la base de donnée dvdflix
     *
     */
    void on_pushButton_clicked();

    /**
     * @brief SLOT demarant le traitement des fichier après leurs téléchargment
     *
     */
    void movieDlFinished();
    /**
     * @brief Affichage de la page suivante des résultats de recherche
     *
     */
    void on_btn_next_clicked();
    /**
     * @brief   Affichage de la page précédente des résultats de recherche
     *
     */
    void on_btn_previous_clicked();
    /**
     * @brief
     *- lecture des fichiers movie * .json
     * -appel de la fonction jsonMerge()
     *
     * @return bool
     */
    bool concatJSON();
    /**
    * @brief
    * -Lecture du fichier json movie.json ou creation si il n'existe pas
    *- determination du nombre de page de resutat restant a telecharger
    * -appel de la fonction telechargement des pages supplémentaires
    * -connection au SLOT concatJson lors du dernier telechargement
    */
    void getPageNumberJson();

    /**
     * @brief
     *          -affichage des mifilm de resultat d'une recherche de film dans les layouts
     *          -affiche un fiche de film censuré si c'est un film adulte et que le code parental n'a pas été saisi
     *
     * @return bool
     */
    bool createMinifilm();
    /**
     * @brief   limite le code parental a 4 difgits et desactive le control une fois cette taille atteinte
     *
     */
    void on_txt_codeParent_textChanged(const QString &arg1);
    /**
     * @brief   lance le controle du codde parental saisi par rapport au code parental lut dans la base de donées
     *
     */
    void on_btn_valideCodeparent_clicked();
    /**
     * @brief   gestion de l'activation du radio bouton de recherche locale uniquement
     *
     */
    void on_rdb_rechLoc_clicked();
    /**
     * @brief   gestion de l'activation du radio bouton de recherche distante et locale
     *
     */
    void on_rdb_rechDist_clicked();

    void on_btn_credit_clicked();

    void on_btn_aPropos_clicked();

private:
    QGridLayout *grdt[21];              /*!< tableau des layou affichant les minifilms après une recherche*/
    C_biblio *dvdtheque;                /*!< objet de stockage des minifilms lors d'une recherche*/
    C_bddSecu Secu;                     /*!< objet gérant la sécurité et info de conexion a la base dvdflix */
    C_MySQLManager *sql;                /*!< objet gérant la partie Mysql */
    C_downloadmanager  m_dlmanager;     /*!< objet gérant le tééléchargement des fichier sur la toile et l'enregistrement sur le hdd */
    QVector<QString> affiches;          /*!< contient la liste des affiches*/
    QString codeParentLu;               /*!< code parental lu dans la base de donées */
    QString codeParentSaisi;            /*!< code parental saisi par l'utilisateur */
    bool codeParentValid;               /*!< indicauteur de code parental egal au code parental lu */
    QString m_hardPath;                 /*!< chemin de stockage des fichiers images des film enregistré dans la base de données*/
    QString m_tempoPath;                /*!< chemin de stockage des fichiers images téléchargés lors du recherche online*/
    bool m_DBState;                     /*!< flag de connection a la database Mysql */
    int m_minifilmMini;                 /*!< numero minimum de la minifiche affichée   */
    int m_minifilmMax;                  /*!< numero maximum de la minifiche affichée   */
    int m_minifilmCountLocal;           /*!< nombre de film pour la derniere recherche en local*/
    int m_minifilmCountOnline;          /*!< nombre de film pour la derniere recherche en ligne*/
    int m_censureCount;                 /*!< nombre de film non affichés si le code partental n'a pas été saisi correctement*/
    int m_totalPage;                    /*!< nombre total de page pour la recherche d'un film   */
    int m_pageNumber;                   /*!< stock le nombre de page deja telecharger lors d'un recherche contenant plusieurs pages*/
    QVector<QJsonObject> m_JsonSearch;  /*!< stockage des objet Json contenu dans les fichier telecharger lors d'une recherche de film avant concatenation*/
    Ui::MainWindow *ui;                 /*!< interface graphique de la fenetre principale*/
    /**
     * @brief vide les layouts des minifilm de la recherche precedente
     *
     */
    void initLayout();
    /**
     * @brief restore les valeurs des menbres concernant l'affichage des minifilm
     *
     */
    void restoreValue();

    /**
     * @brief getion des boutons btn_prev et btn_next dans le cas on on affiche la
     * premieer ou la derniere page des résultat de recherche
     *
     */
    void getsion_prevNext_Btn();
    /**
    * @brief replacement des espaces par des tirets dans le texte du control ln_titre
    *
    * @return QString chaine de carectère formatée pour le recherche en ligne
    */
    QString formatSearch();

    /**
     * @brief     -création du fichier saveMovies.json
     *            -concaténation d'objet json contenus dans m_JsonSearch
     *            -ajout d'une clé "results"
     *            -écriture dans le fichier saveMovies.json
     *
     */
    void JsonMerge();


signals:
    /**
     * @brief Signal donnant l'information qu'un fichier JSON téléchargé peut être lut
     *
     */
    void concatEnd();


};
#endif // MAINWINDOW_H
