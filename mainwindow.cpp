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
 * @brief Formatage de l'url de film a recherche online
 *
 * @param[in]   film                QString         titre du film  a recherche
 * @return      completUrl          QString         url formatées avec la clé de l'API TMBD
*/
QString MainWindow::formatUrl(QString film){
    QString completUrl;
       completUrl =defaultUrl+"search/movie?api_key="+key+"&language=fr&query="+film;


    return completUrl;
}
/**
 * @brief Formatage de l'url de film a recherche online
 *
 * @param[in]   film                QString         titre du film  a recherche
 * @param[in]   page                int             numéro de la page a télécharger
 * @warning la page 1 n'existe pas sur TMBD
 * @return      completUrl          QString         url formatées avec la clé de l'API TMBD
*/

QString MainWindow::formatUrl(QString film,int page){
    QString completUrl;
       completUrl =defaultUrl+"search/movie?api_key="+key+"&language=fr&query="+film+"&page="+QString::number(page);
 qWarning()<<"fichier pageX: "<<completUrl;

    return completUrl;
}
/**
 * @brief fonction de telechargement des rsultat pour un film
 *
 * @param[in]   url                 QString         url de la page à télécharger
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
void MainWindow::startRequest(const QUrl &requestedUrl)
{

    url = requestedUrl;
    qWarning()<<"url: "<<url;
    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);

        connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);


}
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
void MainWindow::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply

    if (file){
        m_byteWrite=file->write(reply->readAll());
        qWarning()<<"CLOTURE DU FICHIER:"<<file->fileName();
        if(m_fileType==0){
            QTimer::singleShot(200, this, SLOT(movieDlFinished()));
        }else if (m_fileType==1){
            QTimer::singleShot(200, this, SLOT(moviePageDlFinished()));
        }
    }else{
        qWarning()<<"error httpready";
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
/**************************************************************
 * nom de la fonction: getPageNumberJson()
 * Auteur: Mercier Laurent
 * Date: 07/04/2020
 *
 * Utilités:
 * -Lecture du fichier json movie.json ou creation si il n'existe pas
 *- determination du nombre de page de resutat restant a telecharger
 * -appel de la fonction telechargement des pages supplémentaire
 * -connection au SLOT concatJson lors du dernier telechargement
 *
 * Paramètres:
 * Entré:
 * Sortie:
 * *************************************************************/

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

    //on telecharge les page suivante si il y en a
    //DEBUG
    qWarning()<<"TOTAL de PAGE a DL: "<< m_totalPage;

    //qstring pour stocker le nom du fichier
    QString filename;

    if(m_totalPage>1){
        for(int i =2;i<=m_totalPage;i++){
            //on connect le signal avertissant de la fin du dernier telechargement a la fonction concatJSON()
            if(i==m_totalPage) connect(&m_dlmanager,SIGNAL(emptyQueue()),SLOT(concatJSON()));
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
/**************************************************************
 * nom de la fonction: concatJson()
 * Auteur: Mercier Laurent
 * Date: 07/04/2020
 *
 * Utilités:
 * -suppression dufichier saveMovies.json
 *- lecture du fichier movie0.json
 * -appel de la fonction jsonMerge()

 *
 * Paramètres:
 * Entré:
 * Sortie: bool
 * *************************************************************/
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

/**************************************************************
 * nom de la fonction:JsonMerge()
 * Auteur: Mercier Laurent
 * Date: 07/04/2020
 *
 * Utilités:
 * -création du fichier saveMovies.json
 * -lecture du fichier movie*.json
 * -concatenation des valeur transmise a la fonction et de celle lues dans le fichier
 * -concaténation d'objet json contenus dans m_JsonSearch et enregistrement dans saveMovies.json
 *
 * Paramètres:
 * Entré: QByteArray jsonValeur
 * Sortie: bool
 * *************************************************************/
bool MainWindow::JsonMerge(){
    qWarning()<<"fichier existe";

   QJsonArray result;
    for(int i =0; i< m_JsonSearch.count();i++){
      result.append(m_JsonSearch[i].value(QString("results")).toArray());
    }

    QJsonObject resultat{

        {"results",result}};

        QJsonDocument concat ;
 //  concat.setArray(result);

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
               qWarning()<< "ok set titre";
           //telechargement de affiche des films
            if(child[j].toObject()["poster_path"].toString()!="")
            {
              //DEBUG
              qWarning()<<"readJson->ajout dl_manager: "<<i;
             m_dlmanager.append(urlBaseAffiche+ child[j].toObject()["poster_path"].toString(),child[j].toObject()["poster_path"].toString());
             min2[counter]->setAffiche(directoryBase+child[j].toObject()["poster_path"].toString());
             }
            else{
              min2[counter]->setAffiche(directoryBase+"/noPicture.png");
              }
            //DEBUG
            qWarning()<<"readJson->creation mini E1";



            qWarning()<<counter;
            counter++;
          }
      }




      qWarning()<<"fin phase1";

//creation des pages contenant 10 miniatures chacune

      QGridLayout *layout = new QGridLayout;
      layout->setParent(ui->centralwidget);
      ui->hl_minifilm->setGeometry(QRect(1,1,1150,1000));
      //layout->addWidget(stackedWidget);


      int imax=5;
      int position=0;
      for(int i =0; i<imax;i++){
        if(min2[i]->getAffiche()!=directoryBase){
          ui->hl_minifilm->addWidget(min2[i],0,position);
          position++;
          //on incremente la variable d'index derniere image affiche dans la vue
          m_minifilmMax++;
        }else {
            imax++;
            qWarning()<<"AFFICHE: "<<min2[i]->getAffiche();
        }

      }
      position=0;
      for(int i =imax; i<=imax+4;i++){
        if(min2[i]->getAffiche()!="d:/tempo68"){
          ui->hl_minifilm->addWidget(min2[i],1,position);
          qWarning()<<"AFFICHE: "<<min2[i]->getAffiche();
          position++;
          //on incremente la variable d'index derniere image affiche dans la vue
          m_minifilmMax++;
        }else {
          imax++;
           qWarning()<<"AFFICHE: "<<min2[i]->getAffiche();
        }
      }

      m_hsld_storedValue+=5;


   }
bool MainWindow::createMinifilm(){

}
void MainWindow::on_btn_modifier_clicked()
{

readJson();
}

void MainWindow::on_hsld_result_valueChanged(int value)
{

/*
    if( ui->hl_minifilm->isEmpty()){
        ui->hl_minifilm->addWidget(min2[value]);
        m_hsld_storedValue=value;
    }else if(m_hsld_storedValue>value){
        ui->hl_minifilm->replaceWidget(min2[value], min2[value-1]);
        m_hsld_storedValue=value;
        qWarning()<<"value+1: " <<value-1<<"    "<<"value: "<<value;
       // ui->hl_minifilm->removeWidget(min2[value+1]);
       // ui->hl_minifilm->addWidget(min2[value]);
    }else if(m_hsld_storedValue<value){
        ui->hl_minifilm->replaceWidget(min2[value+1], min2[value]);
        m_hsld_storedValue=value;
        qWarning()<<"value-1: " <<value-1<<"    "<<"value: "<<value;
       // ui->hl_minifilm->removeWidget(min2[value+1]);
        //ui->hl_minifilm->addWidget(min2[value]);
    }*/
}

void MainWindow::on_btn_supprimer_clicked()
{



    for(int i =m_hsld_storedValue; i<=m_hsld_storedValue+4;i++){
        ui->hl_minifilm->removeWidget(min2[i-5]);
         ui->hl_minifilm->addWidget(min2[i]);

     }
    m_hsld_storedValue+=5;

}



void MainWindow::on_btn_next_clicked()
{
    for(int i =m_hsld_storedValue; i<=m_hsld_storedValue+4;i++){
        ui->hl_minifilm->removeWidget(min2[i-5]);
         ui->hl_minifilm->addWidget(min2[i]);

     }
    m_hsld_storedValue+=5;

}

void MainWindow::on_btn_previous_clicked()
{
    delete ui->hl_minifilm;
    /*
    for(int i =m_hsld_storedValue; i>=m_hsld_storedValue-4;i--){
        ui->hl_minifilm->removeWidget(min2[i]);


     }
    m_hsld_storedValue-=5;
    for(int i =m_hsld_storedValue; i<=m_hsld_storedValue+4;i++){

         ui->hl_minifilm->addWidget(min2[i]);

     }
    m_hsld_storedValue+=5;*/
}
