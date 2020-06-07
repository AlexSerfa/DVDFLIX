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
#include "c_bddsecu.h"
#include <fstream>
#include <iostream>
#include <QDir>
#include <QFileDialog>
#include <c_dbconfig.h>
#include <C_censure.h>

using namespace std;

const QString key ="76532a92d48d6e7e7fb5d72eaf2029b3"; /**< clé de l'API themoviedb */
const QString defaultUrl = " https://api.themoviedb.org/3/"; /**< adresse de l'API themoviedb */
const QString urlBaseAffiche="https://image.tmdb.org/t/p/w500"; /**< adresse pour la récupération des image */
const QString directoryBase= "x:/tempo68"; /**< chemin du dossier de stockage */
const QString directoryHard ="x:/tempo69";


const QString database = "dvdflix";/**< nom de la base de donnée */
const QString adress = "127.0.0.1";/**< adresse du serveur mysql */
const int port = 3308;/**< port du serveur mysql */
const QString user ="root";/**< nom utilisateur sur le server mysql */
const QString password = "admin";/**< mot de passe du serveur mysql */


/**
 * @brief constructeur
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Secu()
    , m_dlmanager(this)    
    , min2()
    , minC()
    , codeParentLu("")
    , codeParentSaisi("")
    , codeParentValid(false)
    , m_minifilmMini(0)
    , m_minifilmMax(0)
    , m_minifilmCountLocal(0)
    , m_minifilmCountOnline(0)
    , m_censureCount(0)
    , m_totalPage(0)
    , m_pageNumber(0)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    imageChemin();


    C_DbConfig *Config = new C_DbConfig(this);
    Config->MainDbConfig();
    Config->~C_DbConfig();


   // C_bddSecu Secu = C_bddSecu();
    Secu.LireIni();
    Secu.connection();
    Secu.close();

    //on connect les signaux de connection a la db
    connect(&sql,SIGNAL(connected()),this,SLOT(status_dbConnectee()));
    connect(&sql,SIGNAL(disconnected()),this,SLOT(status_dbDeconnectee()));
    //on se connect a la db

    sql.connection(database,Secu.getDvdFlixAdr(),Secu.getDvdFlixPort(),Secu.getDvdFlixUser(),Secu.getDvdFlixPass());
    connect(&sql,SIGNAL(modifier()),this, SLOT(miseAJourAffichage()));
    codeParentLu  = sql.getCodeParental();
    //DEBUG
    qWarning()<< "code parent lu dans mainwindows"<<codeParentLu;
}

/**
 * @brief destructeur
 *
 * @todo supprimer les image qui ont été télécharger lors de la dernière recherche
 *
 */
MainWindow::~MainWindow()
{
    restoreValue();
    delete ui;
}


/**
 * @brief MainWindow::imageChemin
 * @author: Jovanovic Milan
 * @date 03/06/2020
 * @brief
 *     vérification et création des dossier img_tempo et lib_img
 */
void MainWindow::imageChemin()
{
    QDir cheminTempo(qApp->applicationDirPath()+"/img_tempo");
    QDir cheminFixe(qApp->applicationDirPath()+"/lib_img");

    if(cheminTempo.exists())
    {
        qWarning()<<"TEMPO: ok "<<qApp->applicationDirPath();
    }
    else
    {
        QDir::setCurrent(qApp->applicationDirPath());
        QDir().mkdir(qApp->applicationDirPath()+"/img_tempo");
        qWarning()<<"TEMPO: n'existe pas "<<qApp->applicationDirPath();
    }
    if(cheminFixe.exists())
    {

        qWarning()<<"FIXE: ok "<<qApp->applicationDirPath();
    }
    else
    {
        QDir::setCurrent(qApp->applicationDirPath());
        QDir().mkdir(qApp->applicationDirPath()+"/lib_img");
        qWarning()<<"FIXE: n'existe pas "<<qApp->applicationDirPath();
    }

}




void MainWindow::rechercheFilm()
{
    //DEBUG
    qWarning()<<"rechercher film";
    //on vérifie que la db est bien connectée
    if(m_DBState){
        m_minifilmCountLocal= sql.filmCount(ui->lbl_titre->text());



        sql.searchTitre(ui->lbl_titre->text());
        m_minifilmCountLocal = sql.getFilmCount();
        //DEBUG
        //qWarning()<<" m_minifilmCountLocal :"<<m_minifilmCountLocal;
        //     min2[h]->setIcone(directoryBase+"/home.png");
    }else
    {
        QMessageBox::warning(this,"Echec de connection","Echec de la connection à la base de données recherche locale impossible",QMessageBox::Ok);
    }

if(ui->rdb_rechDist->isChecked()){
    //DEBUG
    //qWarning()<<"ajout movie0.json a DL_MANAGER ok";
    //on recupere la premiere page du film correspondant apres mise en forme du titre (remplacemant des espaces par de tirets)
    m_dlmanager.append(QUrl::fromUserInput((m_dlmanager.formatUrl(formatSearch()))),"movie0.json");
    //DEBUG
    // qWarning()<<"connect au slot getpagenumber() ok";
    connect(&m_dlmanager,SIGNAL(emptyQueue()),SLOT(getPageNumberJson()));
}
else {
    createMinifilm();
}
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
    //suppression des affiches dont les film n'ont pas été enregistrés
    for(int i=0 ; i<affiches.count(); i++){
        QFile::remove(directoryBase+affiches[i]);
    }
    //on vide la qvector des affiches
    affiches.clear();
    //reset des divers membres utilisés
    m_minifilmMax=0;
    m_minifilmMini=0;
    m_minifilmCountLocal=0;
    m_minifilmCountOnline=0;
    m_totalPage=0;
    m_pageNumber=0;
    m_censureCount=0;
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
            //qWarning()<<"vidage de min2 : "<<i;
            min2[i]->~C_miniFilm();

        }
    }
    //on vide le tableau des censures
    for(int i =0;i<300;i++){
        if(minC[i]){
            //DEBUG
            //qWarning()<<"vidage de min2 : "<<i;
            minC[i]->~C_Censure();

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
    rechercheFilm();

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
    //on limite le nombre de page a 7
    if(  m_totalPage>5) m_totalPage =5 ;
    if(m_totalPage>1){
        for(int i =2;i<=m_totalPage;i++){
            //on connect le signal avertissant de la fin du dernier telechargement a la fonction concatJSON()
            if(i==m_totalPage) connect(&m_dlmanager,SIGNAL(emptyQueue()),this,SLOT(concatJSON()));
            //limiation du nombre de page a telecharger
            if(i<=5){
                m_pageNumber++;
                //on format le nom du fichier suivant
                filename= "movie"+QString::number(i-1)+".json";
                //on ajoute le telechargement du fichier au downloadManager
                m_dlmanager.append(QUrl::fromUserInput((m_dlmanager.formatUrl(ui->ln_titre->text(),i))),filename);
            }
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
    //qWarning()<<"->jsonmerge";
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


    int filmAjouter=0;

    //boucle créant les miniature pour chaque film dans le json movie.json
    int counter =0 ;
    for(int i =0 ; i<arry.count() && i<7;i++)
    {
        QJsonArray child =arry[i].toArray();
        //DEBUG
        //qWarning()<<"arry"<<i<<" child: " <<child.count();
        for(int j =0 ; j<child.count();j++){

            //DEBUG
            //qWarning()<<"readJson->boucle: "<<i<<"-"<<j;
            filmAjouter++;
            qWarning()<<"nb film ajouter: "<<filmAjouter;
            //creation d'une fiche de miniature
            C_miniFilm *min3 =new C_miniFilm(this);
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
            const bool connected = connect(min2[counter],SIGNAL(modifier()),this,SLOT(miseAJourAffichage()));
            //DEBUG
            //qDebug() << "Connection established?" << connected;
            // min2[counter]->setMain(this);
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
                //ajout de l'affiche a au qvector des affiches
                affiches.push_back((child[j].toObject()["poster_path"].toString()));

                //on verifie si le fichier existe deja dans le dossier temporaire des telechargement
                QString basename = directoryBase +child[j].toObject()["poster_path"].toString();
                if (!QFile::exists(basename)) {
                    //on telecharge le fichier
                    m_dlmanager.append(urlBaseAffiche+ child[j].toObject()["poster_path"].toString(),child[j].toObject()["poster_path"].toString());

                }else{
                    //DEBUG
                    qWarning()<<"Le fichier "<< child[j].toObject()["poster_path"].toString() <<" existe deja dans le dossier";
                }
                //ajout de l'affiche au minifilm
                min2[counter]->setAffiche(directoryBase+child[j].toObject()["poster_path"].toString());
                //DEBUG
                //qWarning()<<"<setAffiche: "<<directoryBase+child[j].toObject()["poster_path"].toString();
            }
            else{
                min2[counter]->setAffiche(directoryBase+"/noPicture.png");
            }
            counter++;
        }
    }
    connect(&m_dlmanager,SIGNAL(startCreateMini()),this ,SLOT(createMinifilm()));
    createMinifilm();
}
/**
 * @fn initLayout()
 * @author: Mercier Laurent
 * @date 04/06/2020
 * @brief   -affection des layouts grd* au vector grdt
 *          -vidage des Layouts
 *
 */
void MainWindow::initLayout(){
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

}

/**
 * @fn createMinifilm()
 * @author: Mercier Laurent
 * @date 10/04/2020
 * @brief
 *          -affichage des mifilm de resultat d'une recherche de film dans les layouts
 *          -affiche un fiche de film censuré si c'est un film adulte et que le code parental n'a pas été saisi
 *
 * @return bool
 */
bool MainWindow::createMinifilm(){

    initLayout();
    int filmCounter=0;
    int lastPage = 0;
if(ui->rdb_rechDist->isChecked()|| m_minifilmCountLocal > 10)
{    int totalResult= m_minifilmCountLocal+m_minifilmCountOnline;
    if(totalResult>99) {
        totalResult = 100;
        m_minifilmCountOnline = 100;
    }
    //remplissage des page completes (10 minifilms)
    for(int i = filmCounter;i<totalResult/10 && i<150;i++){
        for(int j =0; j<2;j++){ //pour les lignes
            for(int k =0; k<5; k++){ //pour les colones
                if (filmCounter<m_minifilmCountLocal){
                    //on verfie si le code paental a été entré
                    if(!codeParentValid){
                        //on verifie que le film n'est pas classé adult et on l'affiche
                        if(!sql.min1[filmCounter]->getAdult()){
                            sql.min1[filmCounter]->addAffiche();
                            grdt[i]->addWidget(sql.min1[filmCounter],j,k);
                        }
                        //sinon on affiche un minifilm de censure
                        else
                        {
                            C_Censure *miniCensure = new C_Censure();
                            minC[ m_censureCount]=miniCensure;
                            m_censureCount++;
                            grdt[i]->addWidget(miniCensure,j,k);
                        }
                    }else{
                        sql.min1[filmCounter]->addAffiche();
                        grdt[i]->addWidget(sql.min1[filmCounter],j,k);
                    }
                    filmCounter++;
                    lastPage =i+1;
                }
                else
                {
                    //on verfie si le code paental a été entré
                    if(!codeParentValid){
                        //on verifie que le film n'est pas classé adult et on l'affiche
                        if(!min2[filmCounter-(m_minifilmCountLocal)]->getAdult()){
                            min2[filmCounter-(m_minifilmCountLocal)]->addAffiche();
                            grdt[i]->addWidget(min2[filmCounter-(m_minifilmCountLocal)],j,k);
                        }
                        //sinon on affiche un minifilm de censure
                        else
                        {
                            C_Censure *miniCensure = new C_Censure();
                            minC[ m_censureCount]=miniCensure;
                            m_censureCount++;
                            grdt[i]->addWidget(miniCensure,j,k);
                        }
                    }else{
                        min2[filmCounter-(m_minifilmCountLocal)]->addAffiche();
                        grdt[i]->addWidget(min2[filmCounter-(m_minifilmCountLocal)],j,k);

                    }
                    filmCounter++;
                    lastPage =i+1;
                }
            }
        }
    }
    //DEBUG
    qWarning()<<"-------------------------------------";
    qWarning()<<"FIN DES PAGES COMPLETES";
    qWarning()<<"------------------------------------------";

    for(int j =0; j<2;j++){ //pour les lignes
        for(int k =0; k<5; k++){ //pour les colones
            if(filmCounter <m_minifilmCountOnline){
                //on verfie si le code paental a été entré
                if(!codeParentValid){
                    //on verifie que le film n'est pas classé adult et on l'affiche
                    if(!min2[filmCounter-(m_minifilmCountLocal)]->getAdult()){
                        min2[filmCounter-(m_minifilmCountLocal)]->addAffiche();
                        grdt[lastPage]->addWidget(min2[filmCounter-(m_minifilmCountLocal)],j,k);
                    }
                    //sinon on affiche un minifilm de censure
                    else
                    {
                        C_Censure *miniCensure = new C_Censure();
                        minC[ m_censureCount]=miniCensure;
                        m_censureCount++;
                        grdt[lastPage]->addWidget(miniCensure,j,k);
                    }
                }
                filmCounter++;
            }
        }
    }

}
else{
    for(int i = 0;i<m_minifilmCountLocal && i<10;i++){
    for(int j =0; j<2;j++){ //pour les lignes
        for(int k =0; k<5; k++){ //pour les colones
            if(filmCounter <m_minifilmCountLocal){
                //on verfie si le code paental a été entré
                if(!codeParentValid){
                    //on verifie que le film n'est pas classé adult et on l'affiche
                    if(!sql.min1[filmCounter]->getAdult()){
                        sql.min1[filmCounter]->addAffiche();
                        grdt[i]->addWidget(sql.min1[filmCounter],j,k);
                    }
                    //sinon on affiche un minifilm de censure
                    else
                    {
                        C_Censure *miniCensure = new C_Censure();
                        minC[ m_censureCount]=miniCensure;
                        m_censureCount++;
                        grdt[lastPage]->addWidget(miniCensure,j,k);
                    }
                }
                filmCounter++;
            }
        }
    }

}
}

    getsion_prevNext_Btn();
    //DEBUG
    // min2[0]->addAffiche();
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
 * @fn status_dbDeconnectee()
 * @author: Mercier Laurent
 * @date 17/04/2020
 * @brief   -affichage d'une messageBox avertissant d'un probleme de connection a la base de données dvdflix
 *          -modification du text dans le QLabel du grp_statut en relation avec l'informaation de connexion a la DB
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
   /* if(checked==true){
        sql.deconnection();

    }*/
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
    /*
    if(checked==false)
        sql.connection(database,Secu.getDvdFlixAdr(),Secu.getDvdFlixPort(),Secu.getDvdFlixUser(),Secu.getDvdFlixPass());
    qWarning()<<"adr: "<<Secu.getDvdFlixAdr();
    qWarning()<<"port: "<<Secu.getDvdFlixPort();
      qWarning()<<"user: "<<Secu.getDvdFlixUser();
       qWarning()<<"Pass: "<<Secu.getDvdFlixPass();
       */

}


/**
 * @fn miseAJourAffichage()
 * @author: Mercier Laurent
 * @date 12/05/2020
 * @brief   -appel de la fonction de restoration des valeurs par defaut
 *          -appel de la fonction de recherche de films
 */
void MainWindow::miseAJourAffichage()
{
    restoreValue();
    rechercheFilm();

}
/**
 * @fn on_pushButton_clicked()
 * @author: Jovanovic Milan / Mercier Laurent
 * @date 02/06/2020
 * @brief   -Lecture du fichier dvdfllix.ini
 *          -connection à la base de données Security
 *          -création et affichage de la fenetre option avec passage des parametre de connection à la base de donnée dvdflix
 *
 */
void MainWindow::on_pushButton_clicked()
{
    Secu.LireIni();
    Secu.connection();
    C_options *options = new  C_options(this,Secu.getDvdFlixAdr(),Secu.getDvdFlixPass(),Secu.getDvdFlixUser(),Secu.getDvdFlixPort(),codeParentLu);
    options->show();
}

void MainWindow::on_btn_option_clicked()
{
}




/**
 * @fn on_txt_codeParent_textChanged(const QString &arg1)
 * @author: Mercier Laurent
 * @date 03/06/2020
 * @brief   -verfication du nombre de caractere du QLineEdit du code parental
 *          -Activation et désactivations des controles de saisie et de validation du control parental
 * @param &arg1   Qstring contenu dans le controle
 */
void MainWindow::on_txt_codeParent_textChanged(const QString &arg1)
{
    if(ui->txt_codeParent->text().count()==4){
        ui->txt_codeParent->setEnabled(false);
        ui->btn_valideCodeparent->setEnabled(true);
    }
}
/**
 * @fn on_btn_valideCodeparent_clicked()
 * @author: Mercier Laurent
 * @date 03/06/2020
 * @brief   -gestion du click sur le bouton de validation du control parental
 *          -appel de la fonction de control du code parental de la classe C_bddSecu au traver de l'objet Secu
 *          -modification du texte concernant le code parental dans le groupBox de Statut grp_statut
 *          -initialisation du texte dans le QLineEDit de saisie du controle parental
 *          -Activation et désactivations des controles de saisie et de validation du control parental
 *
 */
void MainWindow::on_btn_valideCodeparent_clicked()
{
    if(ui->txt_codeParent->text().count()==4){
        codeParentSaisi =ui->txt_codeParent->text();
        codeParentValid = Secu.verifCodeParent(codeParentLu,codeParentSaisi);
        qWarning()<<codeParentValid;
        if(codeParentValid) ui->lbl_codeParentEtat->setText("Control parental inactif");
        ui->txt_codeParent->setText("");
        ui->txt_codeParent->setEnabled(true);
        ui->btn_valideCodeparent->setEnabled(false);
        miseAJourAffichage();
    }
}
