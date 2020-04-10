#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <C_minifilm.h>
#include <C_downloadmanager.h>
#include <QSql>
#include <QSqlDatabase>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_rechercher_clicked();
    void on_st_result_currentChanged(int arg1);
    void on_btn_modifier_clicked();
    void on_hsld_result_valueChanged(int value);
    void on_btn_supprimer_clicked();
    void movieDlFinished();
    void moviePageDlFinished();
    void on_btn_next_clicked();
    void on_btn_previous_clicked();
    bool concatJSON();
    void getPageNumberJson();
    void readJson();

private:
    C_downloadmanager  m_dlmanager;
    C_miniFilm *min2[40];
    qint64 m_byteWrite;
    int m_hsld_storedValue;
    int m_minifilmMini;
    int m_minifilmMax;
    int m_minifilmCount;
    int m_totalPage;
    int m_fileType;
    int m_pageNumber;
    QVector<QJsonObject> m_JsonSearch;
    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    std::unique_ptr<QFile> file;
    QFile files[60];
    bool httpRequestAborted;
    Ui::MainWindow *ui;
    void startRequest(const QUrl &requestedUrl);
    void httpFinished();
    void httpReadyRead();
    void downloadFile(QString url);
    QString formatUrl(QString film);
    QString formatUrl(QString film,int page);
    void changePage();

    bool createMinifilm();
    bool JsonMerge();


signals:
    void concatEnd();


};
#endif // MAINWINDOW_H
