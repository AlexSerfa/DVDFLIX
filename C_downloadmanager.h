#ifndef C_DOWNLOADMANAGER_H
#define C_DOWNLOADMANAGER_H
#include<QTextStream>
#include <QtNetwork>
#include <QtCore>

/**
 * @brief
 *
 */
class C_downloadmanager: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit C_downloadmanager(QObject *parent = nullptr);
    void setPath(QString path);
    /**
     * @brief
     *
     * @param film
     * @return QString
     */
    QString formatUrl(QString film);
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
     * @param urls
     * @param filename
     */
    void append(const QStringList &urls,QStringList &filename);
    /**
     * @brief
     *
     * @param url
     * @param filename
     */
    void append(const QUrl &url,QString filename);
    /**
     * @brief
     *
     * @param url
     * @return QString
     */
    QString saveFileName(const QUrl &url);

signals:
    /**
     * @brief
     *
     */
    void finished();
    /**
     * @brief
     *
     */
    void emptyQueue();
    /**
     * @brief
     *
     */
    void startCreateMini();
private:

    /**
     * @brief
     *
     * @return bool
     */
    bool isHttpRedirect() const;
    /**
     * @brief
     *
     */
    void reportRedirect();
    int m_numeroPage; /**< TODO: describe */
    QString m_tempoPath;
    QNetworkAccessManager manager; /**< TODO: describe */
    QQueue<QUrl> downloadQueue; /**< TODO: describe */
    QQueue<QString> fileNameQueue; /**< TODO: describe */
    QNetworkReply *currentDownload = nullptr; /**< TODO: describe */
    QFile output; /**< nom du fichier à écrire sur le disque */
    QElapsedTimer downloadTimer; /**< TODO: describe */


    int downloadedCount = 0; /**< TODO: describe */
    int totalCount = 0; /**< TODO: describe */





private slots:

    /**
     * @brief
     *
     */
    void startNextDownload();
    /**
     * @brief
     *
     */
    void downloadFinished();
    /**
     * @brief
     *
     */
    void downloadReadyRead();
};


#endif // C_DOWNLOADMANAGER_H
