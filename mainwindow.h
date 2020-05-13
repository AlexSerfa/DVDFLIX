#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <C_minifilm.h>
#include <C_downloadmanager.h>
#include <C_mysqlmanager.h>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
    ~MainWindow();
    QGridLayout *grdt[21];

public slots:
    void readJson();
    void status_dbConnectee();
    void status_dbDeconnectee();
    void rechercheFilm();


private slots:
    /**
     * @brief
     *
     */
    void on_btn_rechercher_clicked();
     void on_pushButton_clicked();

    /**
     * @brief
     *
     */
    void movieDlFinished();
    /**
     * @brief
     *
     */
    void on_btn_next_clicked();
    /**
     * @brief
     *
     */
    void on_btn_previous_clicked();
    /**
     * @brief
     *
     * @return bool
     */
    bool concatJSON();
    /**
     * @brief
     *
     */
    void getPageNumberJson();
    /**
     * @brief
     *
     */

    /**
     * @brief
     *
     * @return bool
     */
    bool createMinifilm();
    void on_rdb_rechLoc_toggled(bool checked);
    void on_rdb_rechDist_toggled(bool checked);

private:

    C_MySQLManager sql;     /*!< objet gérant la partie Mysql */
    C_downloadmanager  m_dlmanager; /*!< objet gérant le tééléchargement des fichier sur la toile et l'enregistrement sur le hdd */
    C_miniFilm *min2[150];   /*!< collection de minifiche après une recherche d'un film en ligne*/
//    C_miniFilm *min1[150];   /*!< collection de minifiche après une recherche d'un film en local*/
    QVector<QString> affiches; /*!< contient la liste des affiches*/
    bool m_DBState;         /*!< flag de connection a la database Mysql */
    bool m_searchType;      /*!< definit le type de recherche true: locale et web; false: locale uniquement*/
    int m_minifilmMini;     /*!< numero minimum de la minifiche affichée   */
    int m_minifilmMax;      /*!< numero maximum de la minifiche affichée   */
    int m_minifilmCountLocal;    /*!< nombre de film pour la derniere recherche en local*/
    int m_minifilmCountOnline;    /*!< nombre de film pour la derniere recherche en ligne*/
    int m_minifilmCount=0;
    int m_totalPage;        /*!< nombre total de page pour la recherche d'un film   */
    int m_pageNumber;       /*!< stock le nombre de page deja telecharger lors d'un recherche contenant plusieurs pages*/
    QVector<QJsonObject> m_JsonSearch;  /*!< stockage des objet Json contenu dans les fichier telecharger lors d'une recherche de film avant concatenation*/
    QUrl url;
    Ui::MainWindow *ui;        /*!< interface graphique de la fenetre principale*/
    /**
     * @brief restore les valeurs des menbres concernant l'affichage des minifilm
     *
     */
    void restoreValue();
    /**
     * @brief vide le layout contenant les minifilm
     *
     */
    void videLayout(QLayout *layout);
    /**
     * @brief getion des boutons btn_prev et btn_next dans le cas on on affiche la
     * premieer ou la derniere page des résultat de recherche
     *
     */
    void getsion_prevNext_Btn();
    /**
     * @brief remplacement des espaces dans le tittre a rechercher par des tirets
     *
     * @return QString
     */
    QString formatSearch();

    /**
     * @brief
     *
     * @return bool
     */
    bool JsonMerge();


signals:
    /**
     * @brief
     *
     */
    void concatEnd();


};
#endif // MAINWINDOW_H
