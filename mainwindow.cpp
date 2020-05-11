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
#include <c_options.h>

const QString key ="76532a92d48d6e7e7fb5d72eaf2029b3"; /**< clé de l'API themoviedb */
const QString defaultUrl = " https://api.themoviedb.org/3/"; /**< adresse de l'API themoviedb */
const QString urlBaseAffiche="https://image.tmdb.org/t/p/w500"; /**< adresse pour la récupération des image */
const QString directoryBase= "d:/tempo68"; /**< chemin du dossier de stockage */


const QString database = "dvdflix";/**< nom de la base de donnée */
const QString adress = "127.0.0.1";/**< adresse du serveur mysql */
const int port = 3308;/**< port du serveur mysql */
const QString user ="root";/**< nom utilisateur sur le server mysql */
const QString password = "coucou256!";/**< mot de passe du serveur mysql */


/**
 * @brief constructeur
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_dlmanager(this)
    , min2()
    , m_minifilmMini(0)
    , m_minifilmMax(0)
    , m_minifilmCountLocal(0)
    , m_minifilmCountOnline(0)
    , m_totalPage(0)
    , m_pageNumber(0)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
    //on check le bouton locale +distant par defaut pour le recherche
    ui->rdb_rechDist->setChecked(true);
    //on connect les signaux de connection a la db
    connect(&sql,SIGNAL(connected()),this,SLOT(status_dbConnectee()));
    connect(&sql,SIGNAL(disconnected()),this,SLOT(status_dbDeconnectee()));
    //on se connect a la db
    sql.connection(database,adress,port,user,password);
}

/**
 * @brief destructeur
 *
 * @todo supprimer les image qui ont été télécharger lors de la dernière recherche
 *
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @fn movieDlFinished()
 * @author: Mercier Laurent
 * @date 07/04/2020
 *
 * @brief SLOT demarant le traitement des fichier après leurs téléchargment
 *
*/
void MainWindow::movieDlFinished()
{
    //DEBUG 2l
    //qWarning()<<"movieDlFinished()";
    //qWarning()<<"lecture du fichier json de la recherche ok";
    getPageNumberJson();
    readJson();

}
/**
 * @fn restoreValue()
 * @author: Mercier Laurent
 * @date 01/05/2020
 *
 * @brief restoration des membres à leur valeur initiales
 * @todo verifier bug vidage de min1
 *
*/
void MainWindow::restoreValue()
{
    //on réinitialise les valeurs servant a la gestion de la bibliothèque
    ui->dvdtek->setCurrentIndex(0);
    getsion_prevNext_Btn(); //les bouton previous et next
     //reset des divers membres utilisés
    m_minifilmMax=0;
    m_minifilmMini=0;
    m_minifilmCountLocal=0;
    m_minifilmCountOnline=0;
    m_totalPage=0;
    m_pageNumber=0;
    m_JsonSearch.clear();
    //suppression du fichier saveMovies.json
    bool result = QFile::remove(directoryBase+"/saveMovies.json");
    //DEBUG
    //qWarning()<<"Suppression du fichier: "<<result;
  sql.videMinifilm();
    //on vide le tableau de minifilm de resultat en ligne
    for(int i =0;i<150;i++){
        if(min2[i]){
            //DEBUG
            qWarning()<<"vidage de min2 : "<<i;
            min2[i]->~C_miniFilm();

        }
    }
    //on reset le compteur de resultat de la derniere recherche en local
    sql.resetResultCounter();
}
/**
 * @fn formatSearch()
 * @author: Mercier Laurent
 * @date 01/05/2020
 *
 * @brief replacement des espaces par des tirets dans le texte du control ln_titre
 *
 * @return QString
*/
QString MainWindow::formatSearch()
{

    QString recherche = ui->ln_titre->text();
    int i=0;
    do{
        i =recherche.indexOf(" ",0);
        recherche.replace(i,1,"-");
        //DEBUG
        //qWarning()<<recherche;
    } while (i!=-1);
    return recherche;
}
/**
 * @fn on_btn_rechercher_clicked()
 * @author: Mercier Laurent
 * @date 07/04/2020
 *
 * @brief Lancement de la recherche en ligne a partir du titre du film
 *
 * @todo supprimer les image telechargées durant la dernière recherche
 *
*/

void MainWindow::on_btn_rechercher_clicked()
{
    restoreValue();

    //on vérifie que la db est bien connectée
    if(m_DBState){
        m_minifilmCountLocal= sql.filmCount(ui->lbl_titre->text());



         sql.searchTitre(ui->lbl_titre->text());
         m_minifilmCountLocal = sql.getFilmCount();
         //DEBUG
         qWarning()<<" m_minifilmCountLocal :"<<m_minifilmCountLocal;
  //     min2[h]->setIcone(directoryBase+"/home.png");
    }else
    {
      QMessageBox::warning(this,"Echec de connection","Echec de la connection à la base de données recherche locale impossible",QMessageBox::Ok);
    }


    //DEBUG
    //qWarning()<<"ajout movie0.json a DL_MANAGER ok";
    //on recupere la premiere page du film correspondant apres mise en forme du titre (remplacemant des espaces par de tirets)
    m_dlmanager.append(QUrl::fromUserInput((m_dlmanager.formatUrl(formatSearch()))),"movie0.json");
    //DEBUG
    // qWarning()<<"connect au slot getpagenumber() ok";
    connect(&m_dlmanager,SIGNAL(emptyQueue()),SLOT(getPageNumberJson()));
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
    //qWarning()<<"->getPageNumberJson()";
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
    //qWarning() << JsonObj.value(QString("total_pages"));
    //on recupere le nombre de page pour le film recherché
    m_totalPage = JsonObj.value(QString("total_pages")).toInt();
    //on recupere le nombre de film total
    m_minifilmCountOnline=JsonObj.value(QString("total_results")).toInt();
    //on telecharge les page suivante si il y en a
    //DEBUG
    //qWarning()<<"nombre total de film correspondant a la recherche:  "<< m_minifilmCount;

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
            m_dlmanager.append(QUrl::fromUserInput((m_dlmanager.formatUrl(ui->ln_titre->text(),i))),filename);
        }
    }
    //DEBUG
    //qWarning()<<"getPageNumberjson->";


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
    //qWarning()<<"concatJson";

    for(int i=0;i<= m_pageNumber; i++){
        QFile filej;
        filej.setFileName(directoryBase+"/movie"+QString::number(i)+".json");
        filej.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray val = filej.readAll();
        filej.close();
        QJsonDocument doc = QJsonDocument::fromJson(val);
        QJsonObject jsonObj = doc.object();
        m_JsonSearch.append(jsonObj);
        //traitement a la dernière page
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
    //qWarning()<<"jsonmerge->readjson";
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
      //qWarning()<<"->readJson";

      QFile filej;
      filej.setFileName(directoryBase+"/saveMovies.json");
      filej.open(QIODevice::ReadOnly | QIODevice::Text);
      QByteArray val = filej.readAll();
      filej.close();
      //DEBUG
      //qWarning()<<"readJson->lecture fichier";

      QJsonDocument doc = QJsonDocument::fromJson(val);
      QJsonObject JsonObj= doc.object();
      QJsonArray arry= JsonObj.value(QString("results")).toArray();




//boucle créant les miniature pour chaque film dans le json movie.json
int counter =0 ;
      for(int i =0 ; i<arry.count();i++)
      {
          QJsonArray child =arry[i].toArray();
          //DEBUG				 
          //qWarning()<<"arry"<<i<<" child: " <<child.count();
          for(int j =0 ; j<child.count();j++){

                //DEBUG
               //qWarning()<<"readJson->boucle: "<<i<<"-"<<j;

               //creation d'une fiche de miniature
               C_miniFilm *min3 =new C_miniFilm();
                //ajout de la fiche a la colletion
                min2[counter] =min3;														
                //ajout des donnés d'un film
                //qWarning()<<"Ajout des données du film";
                min2[counter]->setTitre(child[j].toObject()["title"].toString());
                min2[counter]->setAnnee((child[j].toObject()["release_date"].toString()));
                min2[counter]->setNote(QString::number(child[j].toObject()["vote_average"].toDouble()));
                min2[counter]->setPop(child[j].toObject()["popularity"].toString());
                min2[counter]->setAdult(child[j].toObject()["adult"].toBool());
                min2[counter]->setId_online( child[j].toObject()["id"].toInt());
                min2[counter]->setVote(child[j].toObject()["vote_count"].toString());
                min2[counter]->setResum(child[j].toObject()["overview"].toString());
                min2[counter]->setLanguage(child[j].toObject()["original_language"].toString());
                min2[counter]->setTitreOri(child[j].toObject()["original_title"].toString());
                min2[counter]->setBackdrop(child[j].toObject()["backdrop_path"].toString());
                min2[counter]->setIcone(directoryBase+"/online.png");
                min2[counter]->setLocal(false);
                QJsonArray genreArray = child[j].toObject()["genre_ids"].toArray();
                for(int i =0; i<genreArray.count();i++)
                {
                    min2[counter]->setGenres(i,genreArray[i].toInt());
                }
                int genreCode =genreArray[0].toInt();
                QString  genrePrincipal = sql.getGenre(genreCode);
                 min2[counter]->setGenre(genrePrincipal);
           //telechargement de affiche des films
            if(child[j].toObject()["poster_path"].toString()!="")
            {
                m_dlmanager.append(urlBaseAffiche+ child[j].toObject()["poster_path"].toString(),child[j].toObject()["poster_path"].toString());
                min2[counter]->setAffiche(directoryBase+child[j].toObject()["poster_path"].toString());
             }
            else{
              min2[counter]->setAffiche(directoryBase+"/noPicture.png");
              }
            counter++;
          }
      }
      //DEBUG
      //qWarning()<<"fin de la lecture du fichier saveMovie.json";
      connect(&m_dlmanager,SIGNAL(startCreateMini()),this ,SLOT(createMinifilm()));
      createMinifilm();
   }
/**
 * @brief
 *
 * @return bool
 */
bool MainWindow::createMinifilm(){
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
   int totalResult= m_minifilmCountLocal+m_minifilmCountOnline;

    //remplissage des page completes (10 minifilms)
    for(int i = filmCounter;i<totalResult/10 && i<150;i++){
        for(int j =0; j<2;j++){ //pour les lignes
            for(int k =0; k<5; k++){ //pour les colones
                if (filmCounter<m_minifilmCountLocal){
                    sql.min1[filmCounter]->addAffiche();
                    grdt[i]->addWidget(sql.min1[filmCounter],j,k);
                    filmCounter++;
                    lastPage =i+1;
                }else{
                    min2[filmCounter-m_minifilmCountLocal]->addAffiche();
                    grdt[i]->addWidget(min2[filmCounter-m_minifilmCountLocal],j,k);
                    filmCounter++;
                    lastPage =i+1;
                }
            }
        }							   
    }
   for(int j =0; j<2;j++){ //pour les lignes
        for(int k =0; k<5; k++){ //pour les colones
            if(filmCounter <m_minifilmCountOnline){
                if (filmCounter<m_minifilmCountLocal){
                    sql.min1[filmCounter]->addAffiche();
                    grdt[lastPage]->addWidget(sql.min1[filmCounter],j,k);
                    filmCounter++;
                }else{
                    min2[filmCounter]->addAffiche();
                    grdt[lastPage]->addWidget(min2[filmCounter],j,k);
                    filmCounter++;
                }
            }						
        }
    }
    getsion_prevNext_Btn();
    min2[0]->addAffiche();
    return true;
}
/**
 * @brief
 *
 */
void MainWindow::status_dbConnectee(){
    m_DBState=true;
    ui->lbl_db_status->setText("Database connectée");
}
/**
 * @brief
 *
 */
void MainWindow::status_dbDeconnectee(){
    QMessageBox::warning(this,"Echec de connection","Echec de la connection à la base de données",QMessageBox::Ok);
    m_DBState = false;
    ui->lbl_db_status->setText("Database NON connectée");
}
/**
 * @fn getsion_prevNext_Btn()
 * @author: Mercier Laurent
 * @date 13/04/2020
 * @brief vide les layout, conteneurs des minifilms
 *
 * @param layout Layout à vider
 */
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
/**
 * @fn getsion_prevNext_Btn()
 * @author: Mercier Laurent
 * @date 11/04/2020
 *
 * @brief getion des boutons btn_previous et btn_next dans le cas on on affiche la
 * premiere ou la derniere page des résultat de recherche
 * */
void MainWindow::getsion_prevNext_Btn(){
    if(ui->dvdtek->currentIndex()>=m_minifilmCountOnline/10){
        ui->btn_next->setEnabled(false);
    }else ui->btn_next->setEnabled(true);
    if(ui->dvdtek->currentIndex()==0){
        ui->btn_previous->setEnabled(false);
    }else ui->btn_previous->setEnabled(true);
}

/**
 * @fn on_btn_next_clicked()
 * @author: Mercier Laurent
 * @date 13/04/2020
 * @brief Affichage de la page suivante des résultats de recherche
 *
 */
void MainWindow::on_btn_next_clicked()
{
    //on passe a la page precedente du stackedWidget dvdtek
    ui->dvdtek->setCurrentIndex(ui->dvdtek->currentIndex()+1);
    //on gere l'activiter des bouton
    getsion_prevNext_Btn();					   
}

/**
 * @fn on_btn_previous_clicked()
 * @author: Mercier Laurent
 * @date 13/04/2020
 * @brief Affichage de la page précédente des résultats de recherche
 *
 */
void MainWindow::on_btn_previous_clicked()
{
   //on passe a la page precedente du stackedWidget dvdtek
   ui->dvdtek->setCurrentIndex(ui->dvdtek->currentIndex()-1);
   //on gere l'activiter des bouton
   getsion_prevNext_Btn();
}

/**
 * @fn on_rdb_rechLoc_toggled(bool checked)
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
 * @fn on_rdb_rechDist_toggled(bool checked)
 * @author: Mercier Laurent
 * @date 11/04/2020
 * @brief definit une recherche de type locale et web
 *        connecte la base de donnée
 *
 * @param checked   état du bouton radion rdb_searchDist
 */
void MainWindow::on_rdb_rechDist_toggled(bool checked)
{
    if(checked==true)
    sql.connection(database,adress,port,user,password);
    m_searchType=true;

}
void MainWindow::on_pushButton_clicked()
{
   C_options *options = new  C_options();
   options->show();
}
