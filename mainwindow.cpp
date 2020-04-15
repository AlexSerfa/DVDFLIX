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
#include <QSqlQuery>
#include <QSqlRecord>			
#include <C_minifilm.h>
#include <C_mysqlmanager.h>
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
    //on check le bouton locale +distant par defaut pour le recherche
    ui->rdb_rechDist->setChecked(true);
    //on connect les signaux de connection a la db
    connect(&sql,SIGNAL(connected()),this,SLOT(status_dbConnectee()));
    connect(&sql,SIGNAL(disconnected()),this,SLOT(status_dbDeconnectee()));
    //on se connect a la db
    sql.connection("dvdflix","127.0.0.1",3308,"root","coucou256!");															   
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
    ui->dvdtek->setCurrentIndex(0);								   
    getsion_prevNext_Btn(); //les bouton previous et next
    m_minifilmMax=0;    //reset des divers membres utilisés
    m_minifilmMini=0;
    m_minifilmCount=0;
    m_totalPage=0;
    m_pageNumber=0;
	    m_JsonSearch.clear();					 

    //suppression du fichier saveMovies.json
    bool result = QFile::remove(directoryBase+"/saveMovies.json");
    //DEBUG
    qWarning()<<"Suppression du fichier: "<<result;
    //on vide le tableau de minifilm
    for(int i =0;i<150;i++){
        if(min2[i]){
            //DEBUG
            qWarning()<<"vidage de min2 : "<<i;
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
   qWarning()<<"nombre total de film correspondant a la recherche:  "<< m_minifilmCount;

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
    qWarning()<<"getPageNumberjson->";


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
      qWarning()<<"->jsonmerge";
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
  qWarning()<<"jsonmerge->readjson";									  
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
    qWarning()<<"->readJson";

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




//boucle créant les miniature pour chaque film dans le json movie.json
int counter = 0;
      for(int i =0 ; i<arry.count();i++)
      {
          QJsonArray child =arry[i].toArray();
          //DEBUG				 
          qWarning()<<"arry"<<i<<" child: " <<child.count();
          for(int j =0 ; j<child.count();j++){

                //DEBUG
               //qWarning()<<"readJson->boucle: "<<i<<"-"<<j;

               //creation d'une fiche de miniature
               C_miniFilm *min3 =new C_miniFilm();
                //ajout de la fiche a la colletion
                min2[counter] =min3;

														
             //ajout du titre pour ce film
                qWarning()<<"Ajout des données du film";
                min2[counter]->setTitre(child[j].toObject()["title"].toString());
                min2[counter]->setAnnee((child[j].toObject()["release_date"].toString()));
                min2[counter]->setNote(QString::number(child[j].toObject()["vote_average"].toDouble()));
               // QJsonArray genreArray = child[j].toObject()["genre_ids"].toArray();
                //qWarning()<<"genre array 0 : "<<genreArray[0];
              //  QString genrePrincipal = sql.getGenre(genreArray[0].toInt());
              //  qWarning()<<"genre :" << genrePrincipal;
               // min2[counter]->setGenre(sql.getGenre());						  
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
      connect(&m_dlmanager,SIGNAL(startCreateMini()),this ,SLOT(createMinifilm()));
      createMinifilm();


   }
bool MainWindow::createMinifilm(){
    //DEBUG
  //DEBUG
   qWarning()<<"<-createminifil";
   grdt[0]= ui->grd1;
   grdt[1]= ui->grd2;
   grdt[2]= ui->grd3;
   grdt[3]= ui->grd4;
   grdt[4]= ui->grd5;
   grdt[5]= ui->grd6;
   grdt[6]= ui->grd7;
   grdt[7]= ui->grd8;
   grdt[8]= ui->grd9;
   grdt[9]= ui->grd10;
   grdt[10]= ui->grd11;
   grdt[11]= ui->grd12;
   grdt[12]= ui->grd13;
   grdt[13]= ui->grd14;
   grdt[14]= ui->grd15;
   grdt[15]= ui->grd16;
   grdt[16]= ui->grd17;
   grdt[17]= ui->grd18;
   grdt[18]= ui->grd19;
   grdt[19]= ui->grd20;
   grdt[20]= ui->grd21;

    for(int i = 0 ; i<21; i++){
        videLayout(grdt[i]);
    }
   int filmCounter=0;
   int lastPage = 0;
    //remplissage des page complet (10 minifilms)
    for(int i = 0;i<m_minifilmCount/10 && i<200;i++){
        for(int j =0; j<2;j++){ //pour les lignes
            for(int k =0; k<5; k++){ //pour les colones
                min2[filmCounter]->addAffiche();
                grdt[i]->addWidget(min2[filmCounter],j,k);
                filmCounter++;
                lastPage =i+1;

            }
				   
							  
							   
														   
					   
																				  
							
				   
														   
        }
							   
    }
    for(int j =0; j<2;j++){ //pour les lignes
			   
							  
        for(int k =0; k<5; k++){ //pour les colones
            if(filmCounter <m_minifilmCount){
                min2[filmCounter]->addAffiche();
            grdt[lastPage]->addWidget(min2[filmCounter],j,k);
            filmCounter++;
            }
																				  
							
        }
    }
    getsion_prevNext_Btn();
qWarning()<<"affiche de min2 0:"<<min2[0]->getAffiche();

qWarning()<<"affiche de min2 0:"<<min2[1]->getAffiche();
qWarning()<<"affiche de min2 0:"<<min2[3]->getAffiche();
min2[0]->addAffiche();
    return true;

}

void MainWindow::on_btn_modifier_clicked()
{


}
	void MainWindow::status_dbConnectee(){

    qWarning()<<"connecté";
    ui->lbl_db_status->setText("Database connectée");
}
void MainWindow::status_dbDeconnectee(){
    QMessageBox::warning(this,"Echec de connection","Echec de la connection à la base de données",QMessageBox::Ok);
    ui->lbl_db_status->setText("Database NON connectée");
    qWarning()<<"non connecté";
}
void MainWindow::videLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            videLayout(item->layout());
        }

        layout -> removeItem(item);
        delete item;
    }
}								  



void MainWindow::on_btn_supprimer_clicked()
{



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


/**
 * @author: Mercier Laurent
 * @date 13/04/2020
 * @brief Affichage de la page suivante des résultats de recherche
 *
 */
void MainWindow::on_btn_next_clicked()
{
    //on passe a la page precedente du stackedWidget dvdtek
    ui->dvdtek->setCurrentIndex(ui->dvdtek->currentIndex()+1);
    //DEBUG
    qWarning()<<"m_totalpage: "<<m_minifilmCount/10+1<<" curentindex: "<<ui->dvdtek->currentIndex();
    //on gere l'activiter des bouton
    getsion_prevNext_Btn();					   
}

/**
 * @author: Mercier Laurent
 * @date 13/04/2020
 * @brief Affichage de la page précédente des résultats de recherche
 *
 */
void MainWindow::on_btn_previous_clicked()
{
   //on passe a la page precedente du stackedWidget dvdtek
   ui->dvdtek->setCurrentIndex(ui->dvdtek->currentIndex()-1);
   qWarning()<<"m_totalpage: "<<m_totalPage<<" curentindex: "<<ui->dvdtek->currentIndex();
   //on gere l'activiter des bouton
   getsion_prevNext_Btn();
}

/**
 * @author: Mercier Laurent
 * @date 13/04/2020
 * @brief definit une recherche de type locale
 *        deconnecte la base de donnée
 *
 * @param checked   état du bouton radion rdb_searchLoc
 */
void MainWindow::on_rdb_rechLoc_toggled(bool checked)
{
    if(checked==true){
        sql.deconnection();
        m_searchType =false;
    }
}
					  								

/**
 * @author: Mercier Laurent
 * @date 11/04/2020
 * @brief definit une recherche de type locale et web
 *        connecte la base de donnée
 *
 * @param checked   état du bouton radion rdb_searchLDist
 */
void MainWindow::on_rdb_rechDist_toggled(bool checked)
{
    if(checked==true)
    sql.connection("dvdflix","127.0.0.1",3308,"root","coucou256!");
    m_searchType=true;
						  
}
