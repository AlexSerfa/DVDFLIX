#include "C_downloadmanager.h"


#include <QTextStream>
#include<QTimer>
#include <cstdio>

using namespace std;

const QString key ="76532a92d48d6e7e7fb5d72eaf2029b3"; /**< TODO: describe */
const QString defaultUrl = " https://api.themoviedb.org/3/"; /**< TODO: describe */

/**
 * @brief constructuer
 */
C_downloadmanager::C_downloadmanager(QObject *parent)
    : QObject(parent)
      ,m_numeroPage(0)
{

}

/**
 * @fn formatUrl(QString url)
 * @author: Mercier Laurent
 * @date 12/04/2020
 * @brief Formatage de l'url de film pour recherche online, uniquement la premiere page de résultat
 *
 * @param[in]   film                QString         titre du film  a recherche
 * @return      completUrl          QString         url formatées avec la clé de l'API TMBD
 *
*/
void C_downloadmanager::setPath(QString path)
{
    m_tempoPath = path;
}

QString C_downloadmanager::formatUrl(QString film){
    QString completUrl;
       completUrl =defaultUrl+"search/movie?api_key="+key+"&language=fr&query="+film;


    return completUrl;
}
/**
 * @fn formatUrl(QString url, int page)
 * @author: Mercier Laurent
 * @date 12/04/2020
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
    //DEBUG
    //qWarning()<<"fichier pageX: "<<completUrl;
    return completUrl;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief Ajout de des fichiers à télégarger dans la queue
 *
 * @param urls   QUrl        url du fichier a telecharger
 * @param filename  QString     nom du fichier sur le hdd
 */
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

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief Ajout de des fichiers à télégarger dans la queue
 *
 * @param url   QUrl        url du fichier a telecharger
 * @param filename  QString     nom du fichier sur le hdd
 */
void C_downloadmanager::append(const QUrl &url, QString filename)
{
    //DEBUG
    //qWarning()<<"qurl dlmanager: "<<url;
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

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief formatage du nom de fichier à partir de l'url
 *
 * @param url   QUrl    url du fichier à télécharger
 * @return QString  nom du fichier
 */
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

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief démarre le telechargement et nvoir du signal finished si la queue est vide
 *
 */
void C_downloadmanager::startNextDownload()
{
    if (downloadQueue.isEmpty()) {

        emit finished() ;
        totalCount=0;
        return;
    }
    QUrl url = downloadQueue.dequeue();
    totalCount--;
    QString m_filename= fileNameQueue.dequeue();
    QString downloadDirectory = QDir::cleanPath(m_tempoPath);
    bool useDirectory = !downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir();
    if (useDirectory)
       m_filename.prepend(downloadDirectory + '/');
    output.setFileName(m_filename);
    if (!output.open(QIODevice::WriteOnly)) {
        qWarning()<< "problème d'ouverture du fichier '%s' pour le téléchargement '%s': %s\n",
                qPrintable(m_filename), url.toEncoded().constData(),
                qPrintable(output.errorString());

        startNextDownload();
        return;
    }
    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));


    downloadTimer.start();
}


/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief   fermeture du fichier de sortie,
 *           emission du signal de création de minifilm si la queue et vide, demarrage du téléchérgement du fichier suivant dans lec as contraire
 *
 */
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
                 totalCount=0;
               emit emptyQueue();
            }
        }
    }
    currentDownload->deleteLater();
    if(downloadQueue.count()==0){
        emit startCreateMini();
    }
    startNextDownload();
}

/**
 * @brief ecriture des data reçues
 *
 */
void C_downloadmanager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne un booléen si une redirection a lieu
 *
 * @return bool     flag de redirection
 */
bool C_downloadmanager::isHttpRedirect() const
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 *
 * @brief   repport de la redirection dans la console
 *
 */
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

