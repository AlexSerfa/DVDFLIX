#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <C_minifilm.h>
#include <C_downloadmanager.h>
#include <C_MySQLManager.h>
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

private slots:
    /**
     * @brief
     *
     */
    void on_btn_rechercher_clicked();
    /**
     * @brief
     *
     * @param arg1
     */
    void on_st_result_currentChanged(int arg1);
    /**
     * @brief
     *
     */
    void on_btn_modifier_clicked();
    /**
     * @brief
     *
     */
    void on_btn_supprimer_clicked();
    /**
     * @brief
     *
     */
    void movieDlFinished();
    /**
     * @brief
     *
     */
    void moviePageDlFinished();
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

    C_MySQLManager sql;
    C_downloadmanager  m_dlmanager; /**< TODO: describe */
    C_miniFilm *min2[200];   /*!< collection de minifiche après une recherche d'un film*/
    qint64 m_byteWrite;     /*!< contien la valeur des bytes écrit lors d'une écriture sur le disque dur (obsolète)*/
    bool m_searchType;      /*!< definit le type de recherche true: locale et web; false: locale uniquement*/
    int m_hsld_storedValue;
    int m_minifilmMini;     /*!< numero minimum de la minifiche affichée   */
    int m_minifilmMax;      /*!< numero maximum de la minifiche affichée   */
    int m_minifilmCount;    /*!< nombre de film pour la derniere recherche */
    int m_totalPage;        /*!< nombre total de page pour la recherche d'un film   */
    int m_fileType;         /*!< definit la connection a un slot donné en fonction de sa valeur (obsolète)*/
    int m_pageNumber;       /*!< stock le nombre de page deja telecharger lors d'un recherche contenant plusieurs pages*/
    QVector<QJsonObject> m_JsonSearch;  /*!< stockage des objet Json contenu dans les fichier telecharger lors d'une recherche de film avant concatenation*/
    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);
    QUrl url;
    QNetworkAccessManager qnam; /*!<  utiliser pour requete http d'une page unique (obsolète)*/
    QNetworkReply *reply;       /*!<  utiliser pour réponse a une requete http d'une page unique (obsolète)*/
    std::unique_ptr<QFile> file;/*!<  utiliser pour ecrire un fichier sur le hdd lors de la recherche d'une page unique (obsolete)*/
    bool httpRequestAborted;    /*!<  utiliser en cs d'annulation dune requete http lors de la recherche d'une page unique (osolete)*/
    Ui::MainWindow *ui;
    void startRequest(const QUrl &requestedUrl);
    void httpFinished();
    void videLayout(QLayout *layout);
    /**
     * @brief
     *
     */
    void httpReadyRead();
    /**
     * @brief
     *
     * @param url
     */
    void downloadFile(QString url);
    /**
     * @brief
     *
     * @param film
     * @return QString
     */
    QString formatUrl(QString film);
    /**
     * @brief getion des boutons btn_prev et btn_next dans le cas on on affiche la
     * premieer ou la derniere page des résultat de recherche
     *
     */
    void getsion_prevNext_Btn();
    /**
     * @brief
     *
     * @param film
     * @param page
     * @return QString
     */
    QString formatUrl(QString film,int page);
    /**
     * @brief
     *
     */
    void changePage();


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
