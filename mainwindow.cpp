#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "C_downloadmanager.h"
#include <QtNetwork>
#include <QUrl>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <C_minifilm.h>
#include <QVector>
#include <QScrollArea>
#include <QTextStream>
#include <QObject>
#include <QPair>
#include <C_minifilm.h>
const QString key ="76532a92d48d6e7e7fb5d72eaf2029b3";
#if QT_CONFIG(ssl)
const QString defaultUrl = " https://api.themoviedb.org/3/";
const QString urlBaseAffiche="https://image.tmdb.org/t/p/w500";
#else
const QString defaultUrl = " http://api.themoviedb.org/3/";
#endif
const char defaultFileNameMovie[] = "essaiperso.html";
const QString directoryBase= "d:/tempo68";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_dlmanager(this)
    , min2()
    , m_byteWrite(0)
    , m_hsld_storedValue(0)
    , m_minifilmMini(0)
    , m_minifilmMax(0)
    , m_minifilmCount(0)
    , m_totalPage(0)
    , m_fileType(0)
    , m_pageNumber(0)
    , reply(nullptr)
    , file(nullptr)
    , httpRequestAborted(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @fn formatUrl(QString url)
 * @brief Formatage de l'url de film pour recherche online, uniquement la premiere page de résultat
 *
 * @param[in]   film                QString         titre du film  a recherche
 * @return      completUrl          QString         url formatées avec la clé de l'API TMBD
 *
*/
QString MainWindow::formatUrl(QString film){
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
QString MainWindow::formatUrl(QString film,int page){
    QString completUrl;
       completUrl =defaultUrl+"search/movie?api_key="+key+"&language=fr&query="+film+"&page="+QString::number(page);
 qWarning()<<"fichier pageX: "<<completUrl;

    return completUrl;
}

/**
 * @fn downloadFile(QString url )
 * @brief fonction de telechargement des rsultat pour un film
 *
 * @param[in]   url                 QString         url de la page à télécharger
 *
 * @deprecated depuis v0.02
*/
void MainWindow::downloadFile(QString url )
{

    const QString urlSpec = url;
    if (urlSpec.isEmpty())
        return;
    //DEBUG permet d'afficher la version ssl de compilation de qt et la version installer sur le pc (pour debug) 1l
    //qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString()<<"+" << QSslSocket::sslLibraryVersionString();
    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString()));
        return;
    }

    QString fileName = newUrl.fileName();
    // ajout de l'extension au fichier
    fileName+=QString::number(m_pageNumber)+".json";
    qWarning()<< "nom du fichier1:"<<fileName;
    if (fileName.isEmpty())
        fileName = defaultFileNameMovie;

    QString downloadDirectory = QDir::cleanPath(directoryBase);
    bool useDirectory = !downloadDirectory.isEmpty() && QFileInfo(downloadDirectory).isDir();
    if (useDirectory)
        fileName.prepend(downloadDirectory + '/');
    //DEBUG affichage du chemin complet 1l
        qWarning()<< "nom du fichier2:"<<fileName;
    if (QFile::exists(fileName)) {
        if (QMessageBox::question(this, tr("Overwrite Existing File"),
                                  tr("There already exists a file called %1%2."
                                     " Overwrite?")
                                     .arg(fileName,
                                          useDirectory
                                           ? QString()
                                           : QStringLiteral(" in the current directory")),
                                     QMessageBox::Yes | QMessageBox::No,
                                     QMessageBox::No)
            == QMessageBox::No) {
            return;
        }
        QFile::remove(fileName);
    }

    file = openFileForWrite(fileName);
    if (!file)
        return;

    // schedule the request
    startRequest(newUrl);
}
/**
 * @fn openFileForWrite(const QString &fileName)
 * @brief ecriture sur hdd du fichier passé en paramètre
 *
 * @param[in]   &fileNAme             QString               nom du fichier à écrire
 *
 * @return      file                  unique_ptr<QFile>     fichier ecrit
 * @deprecated depuis v0.02
*/
std::unique_ptr<QFile> MainWindow::openFileForWrite(const QString &fileName)
{
      qDebug()<<"openfile"<<endl;
    std::unique_ptr<QFile> file(new QFile(fileName));
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Impossible d'enregister le ficher %1: %2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file->errorString()));
        return nullptr;
    }
    return file;
}
/**
 * @fn startRequest(const QUrl &requestedUrl)
 * @brief execution d'une requete http
 *
 * @param[in]   &requestedUrl         QUrl                  url du fichier à telecharger
 *
 * @warning signal connected
 * @warning &QNetworkReply::finished->&MainWindow::httpFinished
 * @warning &QIODevice::readyRead->&MainWindow::httpReadyRead
 *
 * @deprecated depuis v0.02
*/
void MainWindow::startRequest(const QUrl &requestedUrl)
{

    url = requestedUrl;
    qWarning()<<"url: "<<url;
    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);

        connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);


}
/**
 * @fn httpFinished()
 * @brief gestion de la réponse d'une requete http
 *
 * @deprecated depuis v0.02
*/
void MainWindow::httpFinished()
{
    QFileInfo fi;
    if (file) {
        fi.setFile(file->fileName());
        file->close();
        file.reset();
    }

    if (httpRequestAborted) {
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    if (reply->error()) {
        QFile::remove(fi.absoluteFilePath());
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = nullptr;

    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(this, tr("Redirection"),
                                  tr("Rediriger vers %1 ?").arg(redirectedUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
            QFile::remove(fi.absoluteFilePath());


            return;
        }
        file->open(QIODevice::WriteOnly | QIODevice::Text);
        if (!file) {

            return;
        }
        startRequest(redirectedUrl);
        return;
    }

}
/**
* @fn httpReadyRead()
* @brief  ecriture des données au  fur et à mesure de leurs arrivée
*
* @brief
* Ce SLOT est appélé chaque fois que QNetworkReply à de nouvelles données.
* On lit toutes ces données et on les écrite sur le disque..
* On utilise ainsi moin de RAM qu'en lisant seulement à la fin.
* signal de QNetworkReply
*
* @deprecated depuis v0.02
*/

void MainWindow::httpReadyRead()
{


    if (file){
        m_byteWrite=file->write(reply->readAll());
        //DEBUG
        qWarning()<<"CLOTURE DU FICHIER:"<<file->fileName();
        if(m_fileType==0){
            QTimer::singleShot(200, this, SLOT(movieDlFinished()));
        }else if (m_fileType==1){
            QTimer::singleShot(200, this, SLOT(moviePageDlFinished()));
        }
    }else{
        qWarning()<<"erreur de lecture des données reçues";
    }
}

/*************************************************************************
 * SLOT lit le fichier movie.json et insere les donné dans les miniatures
 *
 * **********************************************************************/
void MainWindow::movieDlFinished()
{
    //DEBUG
    qWarning()<<"movieDlFinished()";

    qWarning()<<"lecture du fichier json de la recherche ok";
    getPageNumberJson();
    readJson();

}
void MainWindow::moviePageDlFinished()
{

}

/*************************************************************************
 * Lancement de la recherche en ligne a partir du titre du film
 *
 * **********************************************************************/
void MainWindow::on_btn_rechercher_clicked()
{
    //! @TODO mettre la partie initialisation dans une fonction
    //on réinitialise les valeurs servant a la gestion de la bibliothèque
    getsion_prevNext_Btn(); //les bouton previous et next
    m_minifilmMax=0;    //reset des divers membres utilisés
    m_minifilmMini=0;
    m_minifilmCount=0;
    m_totalPage=0;
    m_pageNumber=0;


    //on vide le tableau de minifilm
    for(int i =0;i<80;i++){
        if(min2[i]){
            qWarning()<<i;
            min2[i]->~C_miniFilm();
        }
    }

    //DEBUG
    qWarning()<<"ajout movie0.json a DL_MANAGER ok";
    //on recupere la premiere page du film correspondant
    m_dlmanager.append(QUrl::fromUserInput((formatUrl(ui->ln_titre->text()))),"movie0.json");
    //DEBUG
    qWarning()<<"connect au slot getpagenumber() ok";
    connect(&m_dlmanager,SIGNAL(emptyQueue()),SLOT(getPageNumberJson()));
}

void MainWindow::changePage()
{

}
void MainWindow::on_st_result_currentChanged(int arg1)
{

}
/**
 * @fn getPageNumberJson()
 * @author: Mercier Laurent
 * @date 07/04/2020
 *
 * @brief
 * -Lecture du fichier json movie.json ou creation si il n'existe pas
 *- determination du nombre de page de resutat restant a telecharger
 * -appel de la fonction telechargement des pages supplémentaires
 * -connection au SLOT concatJson lors du dernier telechargement
 *
 * @warning signal connected
 * @warning C_downloadmananger::emptyQueue()->this::concatJSON()
*/

void MainWindow::getPageNumberJson(){
    //deconnection du signal de fin de telechargement
    disconnect(&m_dlmanager,SIGNAL(emptyQueue()),this,SLOT(getPageNumberJson()));
    //DEBUG
   qWarning()<<"->getPageNumberJson()";
    // reset du compteur de page a dl
    m_pageNumber=0;
    //creation d'un qbyteArray pour le stockage des données lue
    QByteArray val;

    QFile filej;
    filej.setFileName(directoryBase+"/movie0.json");
    //on lit le fichier movie0.json si il existe
    if(filej.exists()){
        filej.open(QIODevice::ReadOnly | QIODevice::Text);
        //transfert des données lues dans val
        val = filej.readAll();
    }else{
        //sinon on crée le fichier
        filej.open(QIODevice::ReadWrite | QIODevice::Text);
        //transfert des données lues dans val
        val = filej.readAll();
    }
    //fermeture du fichier
    filej.close();


    //creation d'un jsondocument a partir de val
    QJsonDocument doc = QJsonDocument::fromJson(val);
    //recuperation de l'objet présent dans le document
    QJsonObject JsonObj= doc.object();

    //DEBUG
    qWarning() << JsonObj.value(QString("total_pages"));
    //on recupere le nombre de page pour le film recherché
    m_totalPage = JsonObj.value(QString("total_pages")).toInt();
    //on recupere le nombre de film total
    m_minifilmCount=JsonObj.value(QString("total_results")).toInt();
    //on telecharge les page suivante si il y en a
    //DEBUG
    qWarning()<<"TOTAL de PAGE a DL: "<< m_totalPage;

    //qstring pour stocker le nom du fichier
    QString filename;

    if(m_totalPage>1){
        for(int i =2;i<=m_totalPage;i++){
            //on connect le signal avertissant de la fin du dernier telechargement a la fonction concatJSON()
            if(i==m_totalPage) connect(&m_dlmanager,SIGNAL(emptyQueue()),this,SLOT(concatJSON()));
            m_pageNumber++;
            //on format le nom du fichier suivant
            filename= "movie"+QString::number(i-1)+".json";

            //on ajoute le telechargement du fichier au downloadManager
            m_dlmanager.append(QUrl::fromUserInput((formatUrl(ui->ln_titre->text(),i))),filename);

        }
    }
    //DEBUG
    qWarning()<<"<-getPageNumber()";


}
/**
 * @fn concatJson()
 * @author Mercier Laurent
 * @date 07/04/2020
 *
 * @brief
 *- lecture des fichiers movie * .json
 * -appel de la fonction jsonMerge()
 *
 * @warning signal connecté
 * @warning this::concatEnd()->this::readJson()
 *
 * @warning signal deconnecté
 * @warning C_downloadmananger::emptyQueue()->this::concatJSON()
 */
bool MainWindow::concatJSON(){

    //DEBUG
    qWarning()<<"concatJson";

  //  QFile::remove(directoryBase+"/saveMovies.json");

    for(int i=0;i<= m_pageNumber; i++){
        QFile filej;
        filej.setFileName(directoryBase+"/movie"+QString::number(i)+".json");
        filej.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray val = filej.readAll();
        filej.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        QJsonObject jsonObj = doc.object();
        m_JsonSearch.append(jsonObj);
        if(i==m_pageNumber){
            JsonMerge();
            connect(this,SIGNAL(concatEnd()),this,SLOT(readJson()));
        }

    }
    disconnect(&m_dlmanager,SIGNAL(emptyQueue()),this,SLOT(concatJSON()));
    return true;
}

/**
 * @fn JsonMerge()
 * @author: Mercier Laurent
 * @date 09/04/2020
 *
 * @brief
 * -création du fichier saveMovies.json
 * -concaténation d'objet json contenus dans m_JsonSearch
 * -ajout d'une clé "results"
 * -écriture dans le fichier saveMovies.json
 *
 * @return      bool   inutilisé dans cette version
 *
 * @todo récupérer les informations devant etre mise dans la minifiche
 */
bool MainWindow::JsonMerge(){
    //DEBUG
    qWarning()<<"fichier existe";
    QJsonArray result;
    for(int i =0; i< m_JsonSearch.count();i++){
      result.append(m_JsonSearch[i].value(QString("results")).toArray());
    }
    QJsonObject resultat{
        {"results",result}};
    QJsonDocument concat ;
    concat.setObject(resultat);
    QFile saveFile(directoryBase+"/saveMovies.json");
    saveFile.open(QIODevice::WriteOnly);
    qint64 byteWrite= saveFile.write(concat.toJson());
    saveFile.close();
    //DEBUG
    qWarning()<<byteWrite;
    readJson();
    // emit concatEnd();
    return true;

}
/**
 * @fn readJson()
 * @author: Mercier Laurent
 * @date 09/04/2020
 *
 * @brief
 * -lecture du fichier saveMovies.json
 * -recuperation du titre des films
 * -recuperaton de l'affiche du film
 * -ajout a la queue du downbloadManager
 * -creation de la minifilm
 * -insertion des valeur recupérées
 * -insertion dans min2[] de la fiche de chaque film
 *
 *
 * @todo récupérer les informations devant etre mise dans la minifiche
 * @todo redécouper cette fonction car elle fait trop de chose à elle seule
 */
void MainWindow::readJson()
   {
      //DEBUG
      qWarning()<<"<-readJson";

      QFile filej;
      filej.setFileName(directoryBase+"/saveMovies.json");
      filej.open(QIODevice::ReadOnly | QIODevice::Text);
      QByteArray val = filej.readAll();
      filej.close();
      //DEBUG
      qWarning()<<"readJson->lecture fichier";

      QJsonDocument doc = QJsonDocument::fromJson(val);
      QJsonObject JsonObj= doc.object();
      QJsonArray arry= JsonObj.value(QString("results")).toArray();

      //DEBUG
      qWarning()<<"readJson->jsonArray"<<arry.count();


//boucle créant les miniature pour chaque film dans le json movie.json
int counter = 0;
      for(int i =0 ; i<arry.count();i++)
      {
          QJsonArray child =arry[i].toArray();
          qWarning()<<"arry"<<i<<" child: " <<child.count();
         for(int j =0 ; j<child.count();j++){

                //DEBUG
               qWarning()<<"readJson->boucle: "<<i<<"-"<<j;

               //creation d'une fiche de miniature
               C_miniFilm *min3 =new C_miniFilm();
                //ajout de la fiche a la colletion
                min2[counter] =min3;
                //DEBUG
               qWarning()<<"readJson->creation mini E2";
             //ajout du titre pour ce film
                min2[counter]->setTitre(child[j].toObject()["title"].toString());

                //DEBUG
               qWarning()<< "ajout du titre";
           //telechargement de affiche des films
            if(child[j].toObject()["poster_path"].toString()!="")
            {
              //DEBUG
              qWarning()<<"readJson->ajout dl_manager du fichier image de l'affiche n°: "<<i;
             m_dlmanager.append(urlBaseAffiche+ child[j].toObject()["poster_path"].toString(),child[j].toObject()["poster_path"].toString());
             min2[counter]->setAffiche(directoryBase+child[j].toObject()["poster_path"].toString());
             }

            else{
              min2[counter]->setAffiche(directoryBase+"/noPicture.png");
              }




            qWarning()<<counter;
            counter++;
          }
      }



      //DEBUG
      qWarning()<<"fin de la lecture du fichier saveMovie.json";
      createMinifilm();


   }
bool MainWindow::createMinifilm(){
    //DEBUG
    qWarning()<<"creation de 10 fiches à partir du fichier saveMovie.json";

    //creation des pages contenant 10 miniatures chacune

    QGridLayout *layout = new QGridLayout;
    layout->setParent(ui->centralwidget);
    ui->hl_minifilm->setGeometry(QRect(1,1,1150,1000));

    int imax=5;
    int position=0;
    for(int i =0; i<imax;i++){
        if(i<=m_minifilmCount){
            ui->hl_minifilm->addWidget(min2[i],0,position);
            position++;
            //on incremente la variable d'index derniere image affiche dans la vue
            m_minifilmMax++;
            //DEBUG
            qWarning()<<"AFFICHE: "<<min2[i]->getAffiche();
        }
        getsion_prevNext_Btn();
    }

    position=0;
    if(imax<=m_minifilmCount){
        for(int i =imax; i<=imax+4;i++){
            ui->hl_minifilm->addWidget(min2[i],1,position);
            qWarning()<<"AFFICHE: "<<min2[i]->getAffiche();
            position++;
            //on incremente la variable d'index derniere image affiche dans la vue
            m_minifilmMax++;
        }
    }

    //DEBUG 2l
    qWarning()<<"minifilm maxi:"<<QString::number(m_minifilmMax);
    qWarning()<<"minifilm compte:"<<QString::number(m_minifilmCount);
    return true;

}
void MainWindow::on_btn_modifier_clicked()
{

readJson();
}



void MainWindow::on_btn_supprimer_clicked()
{


/* QGridLayout *minifilm = new QGridLayout(ui->centralwidget);
ui->setupUi(this);
ui->hl_minifilm->~QGridLayout();*/
QGridLayout *hl_page= new QGridLayout();
hl_page->setGeometry(QRect(1,1,1150,1000));
hl_page->setParent(ui->hl_minifilm);
//ui->hl_minifilm = hl_page;

}
/**
 * @fn getsion_prevNext_Btn()
 * @author: Mercier Laurent
 * @date 11/04/2020
 *
 * @brief getion des boutons btn_previous et btn_next dans le cas on on affiche la
 * premiere ou la derniere page des résultat de recherche
 * */
void MainWindow::getsion_prevNext_Btn(){
    if(m_minifilmMax>=m_minifilmCount){
        ui->btn_next->setEnabled(false);
    }else ui->btn_next->setEnabled(true);
    if(m_minifilmMini<=0){
        ui->btn_previous->setEnabled(false);
    }else ui->btn_previous->setEnabled(true);

}

void MainWindow::on_btn_next_clicked()
{
    int position=0;

    //suppression de minifilm deja affichés
    for(int i =4;i>=0;i--){

        //delete ui->hl_minifilm->itemAtPosition(1,0);
        ui->hl_minifilm->itemAtPosition(0,i)->widget()->hide();
        ui->hl_minifilm->removeWidget(ui->hl_minifilm->itemAtPosition(0,i)->widget());
        ui->hl_minifilm->itemAtPosition(1,i)->widget()->hide();
        ui->hl_minifilm->removeWidget(ui->hl_minifilm->itemAtPosition(1,i)->widget());
        //   ui->hl_minifilm->itemAtPosition(1,i)->widget()->hide();

    }

    //on redefinit m_minifilmMini comme valant m_minifilmMax
    m_minifilmMini=m_minifilmMax;
    int imax=m_minifilmMax;
    //on ajout la ligne du haut
    for(int i =imax; i<=m_minifilmMax+4;i++){
        if(imax<m_minifilmCount){
            ui->hl_minifilm->addWidget(min2[i],0,position);
            position++;
            imax++;
          //  ui->hl_minifilm->itemAtPosition(0,position)->widget()->show();
        }
        getsion_prevNext_Btn();
    }

    m_minifilmMax+=5;
    position=0;

    for(int i =imax; i<=m_minifilmMax+4;i++){
        if(imax<m_minifilmCount){
            ui->hl_minifilm->addWidget(min2[i],1,position);
            position++;
            imax++;
           // ui->hl_minifilm->itemAtPosition(1,position)->widget()->show();
        }
        getsion_prevNext_Btn();
    }
    m_minifilmMax+=5;
    qWarning()<<"m_minifilmMini"<<QString::number(m_minifilmMini);
    qWarning()<<"m_minifilmMax"<<QString::number(m_minifilmMax);
    getsion_prevNext_Btn();
}

void MainWindow::on_btn_previous_clicked()
{
    qWarning()<<"m_minifilmMini initiale : "<<QString::number(m_minifilmMini);
    qWarning()<<"m_minifilmMax initiale : "<<QString::number(m_minifilmMax);
    int position=0;

    //suppression de minifilm deja affichés
    for(int i =4;i>=0;i--){

        //delete ui->hl_minifilm->itemAtPosition(1,0);
        ui->hl_minifilm->itemAtPosition(0,i)->widget()->hide();
        ui->hl_minifilm->removeWidget(ui->hl_minifilm->itemAtPosition(0,i)->widget());
        ui->hl_minifilm->itemAtPosition(1,i)->widget()->hide();
        ui->hl_minifilm->removeWidget(ui->hl_minifilm->itemAtPosition(1,i)->widget());
        //   ui->hl_minifilm->itemAtPosition(1,i)->widget()->hide();

    }
    //on redefinit m_minifilmMini comme valant m_minifilmMax leur valeur -10
    m_minifilmMini-=10;
   m_minifilmMax=m_minifilmMini;

    qWarning()<<min2[2]->getAffiche();
    qWarning()<<"m_minifilmMini"<<QString::number(m_minifilmMini);
    qWarning()<<"m_minifilmMax"<<QString::number(m_minifilmMax);


    int imax=m_minifilmMini;
    qWarning()<<"m_minifilmMini avH"<<QString::number(m_minifilmMini);
    qWarning()<<"m_minifilmMax avH"<<QString::number(m_minifilmMax);
    qWarning()<<"imax avH : "<<QString::number(imax);
    //on ajout la ligne du haut
    for(int i =0; i<=4;i++){
         qWarning()<<"boucle previous haut: "<<i;
         qWarning()<<"position : "<<position;
        ui->hl_minifilm->addWidget(min2[m_minifilmMini+position],0,position);
        position++;
        imax++;
       ui->hl_minifilm->itemAtPosition(0,position)->widget()->show();
        getsion_prevNext_Btn();
    }
    /*
    m_minifilmMax+=imax;
    position=0;
    qWarning()<<"m_minifilmMini apH"<<QString::number(m_minifilmMini);
    qWarning()<<"m_minifilmMax apH"<<QString::number(m_minifilmMax);
    qWarning()<<"imax apH: "<<QString::number(imax);
    qWarning()<<"item count apH"<< ui->hl_minifilm->count();
    for(int i =imax; i<=m_minifilmMax+4;i++){
        qWarning()<<"boucle previous bas: "<<i;
       qWarning()<<"position : "<<position;
        ui->hl_minifilm->addWidget(min2[m_minifilmMini+position+5],1,position);
        position++;
        imax++;
        //ui->hl_minifilm->itemAtPosition(1,position)->widget()->show();
        getsion_prevNext_Btn();
    }
    */
   m_minifilmMax+=5;
   qWarning()<<"m_minifilmMini apB"<<QString::number(m_minifilmMini);
   qWarning()<<"m_minifilmMax apB"<<QString::number(m_minifilmMax);
       qWarning()<<"imax apB: "<<QString::number(imax);
   getsion_prevNext_Btn();
}
