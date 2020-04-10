#ifndef C_DOWNLOADMANAGER_H
#define C_DOWNLOADMANAGER_H
#include<QTextStream>
#include <QtNetwork>
#include <QtCore>

class C_downloadmanager: public QObject
{
    Q_OBJECT
public:
    explicit C_downloadmanager(QObject *parent = nullptr);

    void append(const QStringList &urls,QStringList &filename);
    void append(const QUrl &url,QString filename);
 //   void append(const QUrl &url, const QString filename);
    QString saveFileName(const QUrl &url);
    void setDlType(QString type);

private:

    bool isHttpRedirect() const;
    void reportRedirect();
    int m_numeroPage;
    QString m_filename;
    QNetworkAccessManager manager;
    QQueue<QUrl> downloadQueue;
    QQueue<QString> fileNameQueue;
    QNetworkReply *currentDownload = nullptr;
    QFile output;
    QElapsedTimer downloadTimer;


    int downloadedCount = 0;
    int totalCount = 0;



signals:
    void finished();
    void emptyQueue();

private slots:

    void startNextDownload();
    void downloadFinished();
    void downloadReadyRead();
};


#endif // C_DOWNLOADMANAGER_H
