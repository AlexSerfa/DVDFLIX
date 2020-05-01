#include "C_downloadmanager.h"


#include <QTextStream>
#include<QTimer>
#include <cstdio>

using namespace std;

const QString key ="76532a92d48d6e7e7fb5d72eaf2029b3";
const QString defaultUrl = " https://api.themoviedb.org/3/";
const QString urlBaseAffiche="https://image.tmdb.org/t/p/w500";
const QString directoryBase= "d:/tempo68";
/**
 * @brief constructuer
 */
C_downloadmanager::C_downloadmanager(QObject *parent)
    : QObject(parent)
      ,m_numeroPage(0)
      ,m_uniqueFile(true)
{

}

/**
 * @fn formatUrl(QString url)
 * @brief Formatage de l'url de film pour recherche online, uniquement la premiere page de résultat
 *
 * @param[in]   film                QString         titre du film  a recherche
 * @return      completUrl          QString         url formatées avec la clé de l'API TMBD
 *
*/
QString C_downloadmanager::formatUrl(QString film){
    QString completUrl;
       completUrl =defaultUrl+"search/movie?api_key="+key+"&language=fr&query="+film;


    return completUrl;
}
/**
 * @fn formatUrl(QString url, int page)
 * @brief Formatage de l'url de film a recherche online, précisant le numéro de la page de résultat
 * @warning la page 1 n'existe pas sur TMBD
 *
 * @param[in]   film                QString         titre du film  a recherche
 * @param[in]   page                int             numéro de la page a télécharger
 * @return      completUrl          QString         url formatées avec la clé de l'API TMBD
*/
QString C_downloadmanager::formatUrl(QString film,int page){
    QString completUrl;
       completUrl =defaultUrl+"search/movie?api_key="+key+"&language=fr&query="+film+"&page="+QString::number(page);
 qWarning()<<"fichier pageX: "<<completUrl;

    return completUrl;
}

void C_downloadmanager::append(const QStringList &urls, QStringList &filename)
{
    int counter= 0;
    qWarning()<<"url"<<urls;
    for (const QString &urlAsString : urls){
        append(QUrl::fromEncoded(urlAsString.toLocal8Bit()),filename.takeAt(counter));
        counter++;
    }

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));
}

void C_downloadmanager::append(const QUrl &url, QString filename)
{
    //DEBUG
    qWarning()<<"qurl dlmanager: "<<url;
    if (downloadQueue.isEmpty()){
        QTimer::singleShot(3000, this,SLOT(startNextDownload()));
        qWarning()<<"demarrage telechargement";
    }

    downloadQueue.enqueue(url);
    fileNameQueue.enqueue(filename);
    ++totalCount;
    //DEBUG
    qWarning()<<"Total de fichier a telecharger: "<<totalCount;
}

QString C_downloadmanager::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();
    //DEBUG
    qWarning()<<"fichier de sauvegarde: " <<basename;
    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // si le fichier existe on ne l'écrase pas on ajoute un chiffre a lafin
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

void C_downloadmanager::startNextDownload()
{
    if (downloadQueue.isEmpty()) {

        emit finished() ;
        totalCount=0;
        return;
    }
    QUrl url = downloadQueue.dequeue();
    QString m_filename= fileNameQueue.dequeue();
    //QString filename = saveFileName(url);
    QString downloadDirectory = QDir::cleanPath(directoryBase);
    bool useDirectory = !downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir();
    if (useDirectory)
       m_filename.prepend(downloadDirectory + '/');
    output.setFileName(m_filename);
    //DEBUG
    //qWarning()<<m_filename;
    if (!output.open(QIODevice::WriteOnly)) {
        qWarning()<< "problème d'ouverture du fichier '%s' pour le téléchargement '%s': %s\n",
                qPrintable(m_filename), url.toEncoded().constData(),
                qPrintable(output.errorString());

        startNextDownload();
        //DEBUG
        //qWarning()<<"demarrage telechargement E2 :"<<QString::number(downloadQueue.count());
        return;
    }
    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    //DEBUG
    qWarning()<<"Téléchargement :"<< url.toEncoded().constData();
    downloadTimer.start();
}


void C_downloadmanager::downloadFinished()
{
    output.close();
    if (currentDownload->error()) {
        // erreur durant le téléchargement
        qWarning()<<"échec: \n"<< qPrintable(currentDownload->errorString());
        output.remove();
    } else {
        // on verifie si il y a une redirection
        if (isHttpRedirect()) {
            reportRedirect();
            output.remove();
        } else {
            qWarning()<<"Succes.\n";
            ++downloadedCount;
            if(downloadQueue.isEmpty() ){
                //DEBUG
                //qWarning()<<"EMIT EMPTYQUEUE";
               emit emptyQueue();
            }
        }
    }

    currentDownload->deleteLater();
    //DEBUG
    //qWarning()<<"demarrage telechargement E3 :"<<QString::number(downloadQueue.count());
    if(downloadQueue.count()==0){
        emit startCreateMini();
    }
    startNextDownload();
}

void C_downloadmanager::downloadReadyRead()
{
    qWarning()<<output.write(currentDownload->readAll());


}

bool C_downloadmanager::isHttpRedirect() const
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void C_downloadmanager::reportRedirect()
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QUrl requestUrl = currentDownload->request().url();
    QTextStream(stderr) << "Requete: " << requestUrl.toDisplayString()
                        << " redirecton avec le code: " << statusCode
                        << '\n';

    QVariant target = currentDownload->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!target.isValid())
        return;
    QUrl redirectUrl = target.toUrl();
    if (redirectUrl.isRelative())
        redirectUrl = requestUrl.resolved(redirectUrl);
    QTextStream(stderr) << "Redirigé vers: " << redirectUrl.toDisplayString()
                        << '\n';
}

