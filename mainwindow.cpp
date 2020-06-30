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
#include <c_biblio.h>
#include <c_credit.h>
#include <c_apropos.h>

using namespace std;


const QString urlBaseAffiche="https://image.tmdb.org/t/p/w500"; /**< adresse pour la récupération des image */
const QString database = "dvdflix";/**< nom de la base de donnée */


/**
 * @brief constructeur
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dvdtheque()
    , m_dlmanager(this)
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


    C_DbConfig *Config = new C_DbConfig(this);
    Config->MainDbConfig();
    Config->~C_DbConfig();
    dvdtheque =new C_biblio();
    sql= new C_MySQLManager(this,dvdtheque);
    Secu.LireIni();
     //on se connect a la db secu
    sql->connection("security",Secu.getBDdvdAdr(),Secu.getBDdvdPort(),Secu.getBDdvdUser(),Secu.getBDdvdPass());
    Secu.connection();
    ui->setupUi(this);
    //vérification que les chemins par defaut existe et créatio de ces dernier le ca échéant
    imageChemin();
    //on connect les signaux de connection a la db
    connect(sql,SIGNAL(connected()),this,SLOT(status_dbConnectee()));
    connect(sql,SIGNAL(disconnected()),this,SLOT(status_dbDeconnectee()));
    //on se connect a la db dvdflix

    sql->connection(database,Secu.getDvdFlixAdr(),Secu.getDvdFlixPort(),Secu.getDvdFlixUser(),Secu.getDvdFlixPass());
    connect(sql,SIGNAL(modifier()),this, SLOT(on_btn_rechercher_clicked()));
    //on reucpère le code parental et les chemin à utilisé
    codeParentLu  = sql->getCodeParental();
    m_hardPath =sql->getHardPath();
    m_tempoPath = sql->getTempoPath();
    //on tranmet le chemin temporaire a l'objet C_downloadManager
    m_dlmanager.setPath(m_tempoPath);
    //on paramètre l'affiche graphique de l'interface
    ui->logoSearch->setPixmap(qApp->applicationDirPath()+"/lib_img/dvdFlixSearch.png");
    ui->logoSearch->setHidden(true);
    ui->cb_typeSearch->setHidden(true);
    ui->cb_typeSearch->setDisabled(true);
    ui->lbl_titre->setHidden(false);
    ui->lbl_logo->setPixmap(qApp->applicationDirPath()+"/lib_img/logo.png");

}
/**
 * @brief destructeur
 *
 *
 */
MainWindow::~MainWindow()
{
    //on restore les valeur par defaut et on supprime les image du dossier temporaire
    restoreValue();
    delete ui;
}
/**
 * @brief MainWindow::imageChemin
 * @author: Jovanovic Milan
 * @date 03/06/2020
 * @brief   vérification et création des dossier img_tempo et lib_img
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
/**
 * @fn rechercheFilm()
 * @author: Mercier Laurent
 * @date 13/05/2020
 * @brief selectionne les fonctions a éffectuer en fonction du type de recherche demandé
 *
 * @param value     index du combo-box de selection du genre de recherche
 */
void MainWindow::rechercheFilm(int value)
{

    //on vérifie que la db est bien connectée
    if(!m_DBState){
        QMessageBox::warning(this,"Echec de connection","Echec de la connection à la base de données recherche locale impossible",QMessageBox::Ok);
    }
    // si c'est un tire a recherché
    if( value ==0){
        //m_minifilmCountLocal= sql->filmCount(ui->ln_titre->text(),value);
        sql->searchTitre(ui->ln_titre->text());
        m_minifilmCountLocal = sql->getFilmCount();

    }
    //si c'est un acteur
    else if (value ==1)
    {
        sql->searchPersonne(ui->ln_titre->text(), "acteur");
        m_minifilmCountLocal = sql->getFilmCount();
    }
    //si c'est un realisateur
    else if (value ==2)
    {
        sql->searchPersonne(ui->ln_titre->text(), "realis");
        m_minifilmCountLocal = sql->getFilmCount();
    }

    if(ui->rdb_rechDist->isChecked()){

        //on recupere la premiere page du film correspondant apres mise en forme du titre (remplacemant des espaces par de tirets)
        m_dlmanager.append(QUrl::fromUserInput((m_dlmanager.formatUrl(formatSearch()))),"movie0.json");

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
    getPageNumberJson();
    readJson();
}
/**
 * @fn restoreValue()
 * @author: Mercier Laurent
 * @date 01/05/2020
 *
 * @brief restoration des membres à leur valeur initiales
 *
*/
void MainWindow::restoreValue()
{
    //on réinitialise les valeurs servant a la gestion de la bibliothèque
    ui->dvdtek->setCurrentIndex(0);
    getsion_prevNext_Btn(); //les bouton previous et next
    //suppression des affiches dont les film n'ont pas été enregistrés
    for(int i=0 ; i<affiches.count(); i++){
        QFile::remove(m_tempoPath+affiches[i]);
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
    QFile::remove(m_tempoPath+"/saveMovies.json");
    //on reset le compteur de resultat de la derniere recherche en local
    sql->resetResultCounter();
}
/**
 * @fn formatSearch()
 * @author: Mercier Laurent
 * @date 01/05/2020
 *
 * @brief replacement des espaces par des tirets dans le texte du control ln_titre
 *
 * @return QString chaine de carectère formatée pour le recherche en ligne
*/
QString MainWindow::formatSearch()
{
    QString recherche = ui->ln_titre->text();
    int i=0;
    do{
        i =recherche.indexOf(" ",0);
        recherche.replace(i,1,"-");
    } while (i!=-1);
    return recherche;
}
/**
 * @fn on_btn_rechercher_clicked()
 * @author: Mercier Laurent
 * @date 07/04/2020
 *
 * @brief Lancement de la recherche a partir ddes informations saisies par l'utilisateur du film
 *
 *
*/
void MainWindow::on_btn_rechercher_clicked()
{
    //reinitialisation des layouts
    initLayout();
    //premiere anlyse du type de recherche demandé (local ou distante)
    int value;
    if(ui->rdb_rechDist->isChecked())value=0;
    if(ui->rdb_rechLoc->isChecked())value=ui->cb_typeSearch->currentIndex();
    if(ui->ln_titre->text()!=""){
        ui->logoSearch->setHidden(false);
        restoreValue();
        rechercheFilm(value);
    }
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
    // reset du compteur de page a dl
    m_pageNumber=0;
    //creation d'un qbyteArray pour le stockage des données lue
    QByteArray val;

    QFile filej;
    filej.setFileName(m_tempoPath+"/movie0.json");
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


    //on recupere le nombre de page pour le film recherché
    m_totalPage = JsonObj.value(QString("total_pages")).toInt();
    //on recupere le nombre de film total
    m_minifilmCountOnline=JsonObj.value(QString("total_results")).toInt();
    //on telecharge les page suivante si il y en a


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


}
/**
 * @fn concatJson()
 * @author Mercier Laurent
 * @date 07/04/2020
 *
 * @brief
 *- ecriture des fichiers movie * .json
 * -appel de la fonction jsonMerge()
 *
 * @warning signal connecté
 * @warning this::concatEnd()->this::readJson()
 *
 * @warning signal deconnecté
 * @warning C_downloadmananger::emptyQueue()->this::concatJSON()
 */
bool MainWindow::concatJSON(){


    for(int i=0;i<= m_pageNumber; i++){
        QFile filej;
        filej.setFileName(m_tempoPath+"/movie"+QString::number(i)+".json");
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
 *
 */
void MainWindow::JsonMerge(){

    QJsonArray result;
    for(int i =0; i< m_JsonSearch.count();i++){
        result.append(m_JsonSearch[i].value(QString("results")).toArray());
    }
    QJsonObject resultat{
        {"results",result}};
    QJsonDocument concat ;
    concat.setObject(resultat);
    QFile saveFile(m_tempoPath+"/saveMovies.json");
    saveFile.open(QIODevice::WriteOnly);
    saveFile.write(concat.toJson());
    saveFile.close();
    readJson();

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
 * -insertion dans dvdtheque->min2[] de la fiche de chaque film
 *
 */
void MainWindow::readJson()
{

    QFile filej;
    filej.setFileName(m_tempoPath+"/saveMovies.json");
    filej.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = filej.readAll();
    filej.close();
    QJsonDocument doc = QJsonDocument::fromJson(val);
    QJsonObject JsonObj= doc.object();
    QJsonArray arry= JsonObj.value(QString("results")).toArray();


    int filmAjouter=0;

    //boucle créant les miniature pour chaque film dans le json movie.json
    int counter =0 ;
    for(int i =0 ; i<arry.count() && i<7;i++)
    {
        QJsonArray child =arry[i].toArray();

        for(int j =0 ; j<child.count();j++){

            filmAjouter++;
            qWarning()<<"nb film ajouter: "<<filmAjouter;
            //creation d'une fiche de miniature
            C_miniFilm *min3 =new C_miniFilm(this);
            //ajout de la fiche a la colletion
            dvdtheque->addFilmOnline(counter,min3);
            //ajout des donnés d'un film
            dvdtheque->getFilmOnline(counter)->setTitre(child[j].toObject()["title"].toString());
            dvdtheque->getFilmOnline(counter)->setAnnee((child[j].toObject()["release_date"].toString()));
            dvdtheque->getFilmOnline(counter)->setNote(QString::number(child[j].toObject()["vote_average"].toDouble()));
            dvdtheque->getFilmOnline(counter)->setPop(child[j].toObject()["popularity"].toString());
            dvdtheque->getFilmOnline(counter)->setAdult(child[j].toObject()["adult"].toBool());
            dvdtheque->getFilmOnline(counter)->setId_online( child[j].toObject()["id"].toInt());
            dvdtheque->getFilmOnline(counter)->setVote(child[j].toObject()["vote_count"].toString());
            dvdtheque->getFilmOnline(counter)->setResum(child[j].toObject()["overview"].toString());
            dvdtheque->getFilmOnline(counter)->setLanguage(child[j].toObject()["original_language"].toString());
            dvdtheque->getFilmOnline(counter)->setTitreOri(child[j].toObject()["original_title"].toString());
            dvdtheque->getFilmOnline(counter)->setBackdrop(child[j].toObject()["backdrop_path"].toString());
            dvdtheque->getFilmOnline(counter)->setIcone(qApp->applicationDirPath()+"/lib_img/online.png");
            dvdtheque->getFilmOnline(counter)->setLocal(false);
            connect(dvdtheque->getFilmOnline(counter),SIGNAL(modifier()),this,SLOT( on_btn_rechercher_clicked()));

            QJsonArray genreArray = child[j].toObject()["genre_ids"].toArray();
            for(int i =0; i<genreArray.count();i++)
            {
                dvdtheque->getFilmOnline(counter)->setGenres(i,genreArray[i].toInt());
            }

            int genreCode =genreArray[0].toInt();
            QString  genrePrincipal = sql->getGenre(genreCode);
            dvdtheque->getFilmOnline(counter)->setGenre(genrePrincipal);
            //telechargement de affiche des films
            if(child[j].toObject()["poster_path"].toString()!="")
            {
                //ajout de l'affiche a au qvector des affiches
                affiches.push_back((child[j].toObject()["poster_path"].toString()));

                //on verifie si le fichier existe deja dans le dossier temporaire des telechargement
                QString basename = m_tempoPath +child[j].toObject()["poster_path"].toString();
                if (!QFile::exists(basename)) {
                    //on telecharge le fichier
                    m_dlmanager.append(urlBaseAffiche+ child[j].toObject()["poster_path"].toString(),child[j].toObject()["poster_path"].toString());

                }
                //ajout de l'affiche au minifilm
                dvdtheque->getFilmOnline(counter)->setAffiche(m_tempoPath+child[j].toObject()["poster_path"].toString());

            }
            else{
                dvdtheque->getFilmOnline(counter)->setAffiche(qApp->applicationDirPath()+"/lib_img/noPicture.png");
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

    int baseCount =m_minifilmCountLocal;
    if(m_minifilmCountLocal>0){

        for(int i = 0;i<baseCount;i++){
            dvdtheque->getFilmLocal(i)->~C_miniFilm();
            m_minifilmCountLocal=m_minifilmCountLocal-1;
        }
    }
    baseCount =m_minifilmCountOnline;
    if(m_minifilmCountOnline>0){
        for(int i = 0;i<baseCount;i++){
            dvdtheque->getFilmOnline(i)->~C_miniFilm();
            m_minifilmCountOnline=m_minifilmCountOnline-1;
        }
    }

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
                            if(!dvdtheque->getFilmLocal(filmCounter)->getAdult()){
                                dvdtheque->getFilmLocal(filmCounter)->addAffiche();
                                grdt[i]->addWidget(dvdtheque->getFilmLocal(filmCounter),j,k);

                            }
                            //sinon on affiche un minifilm de censure
                            else
                            {
                                C_Censure *miniCensure = new C_Censure();
                                grdt[i]->addWidget(miniCensure,j,k);
                            }
                        }else{
                            dvdtheque->getFilmLocal(filmCounter)->addAffiche();
                            grdt[i]->addWidget(dvdtheque->getFilmLocal(filmCounter),j,k);
                        }
                        filmCounter++;
                        lastPage =i+1;
                    }
                    else
                    {
                        //on verfie si le code paental a été entré
                        if(!codeParentValid){
                            //on verifie que le film n'est pas classé adult et on l'affiche
                            if(!dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal))->getAdult()){
                                dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal))->addAffiche();
                                grdt[i]->addWidget(dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal)),j,k);
                            }
                            //sinon on affiche un minifilm de censure
                            else
                            {
                                C_Censure *miniCensure = new C_Censure();
                                grdt[i]->addWidget(miniCensure,j,k);
                            }
                        }else{
                            dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal))->addAffiche();
                            grdt[i]->addWidget(dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal)),j,k);

                        }
                        filmCounter++;
                        lastPage =i+1;
                    }
                }
            }
        }
        for(int j =0; j<2;j++){ //pour les lignes
            for(int k =0; k<5; k++){ //pour les colones
                if(filmCounter <m_minifilmCountOnline){
                    //on verfie si le code paental a été entré
                    if(!codeParentValid){
                        //on verifie que le film n'est pas classé adult et on l'affiche
                        if(!dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal))->getAdult()){
                            dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal))->addAffiche();
                            grdt[lastPage]->addWidget(dvdtheque->getFilmOnline(filmCounter-(m_minifilmCountLocal)),j,k);
                        }
                        //sinon on affiche un minifilm de censure
                        else
                        {
                            C_Censure *miniCensure = new C_Censure();
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
                            if(!dvdtheque->getFilmLocal(filmCounter)->getAdult()){
                                dvdtheque->getFilmLocal(filmCounter)->addAffiche();
                                grdt[i]->addWidget(dvdtheque->getFilmLocal(filmCounter),j,k);
                            }
                            //sinon on affiche un minifilm de censure
                            else
                            {
                                C_Censure *miniCensure = new C_Censure();
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
    ui->logoSearch->setHidden(true);
    return true;
}
/**
 * @fn status_dbConnectee()
 * @author: Mercier Laurent
 * @date 17/04/2020
 * @brief   -affichage d'une messageBox avertissant que la connexion a la base de données dvdflix est opérationelle
 *          -modification du text dans le QLabel du grp_statut en relation avec l'information de connexion a la DB
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
 *          -modification du text dans le QLabel du grp_statut en relation avec l'information de connexion a la DB
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
    C_options *options = new  C_options(this,Secu.getDvdFlixAdr(),Secu.getDvdFlixPass(),Secu.getDvdFlixUser(),Secu.getDvdFlixPort(),codeParentLu,sql);
    options->show();
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
        if(codeParentValid) ui->lbl_codeParentEtat->setText("Control parental inactif");
        ui->txt_codeParent->setText("");
        ui->txt_codeParent->setEnabled(true);
        ui->btn_valideCodeparent->setEnabled(false);
        on_btn_rechercher_clicked();
    }
}

/**
 * @fn on_rdb_rechLoc_clicked()
 * @author: Mercier Laurent
 * @date 03/06/2020
 * @brief   gestion de l'activation du radio bouton de recherche locale uniquement
 *
 */
void MainWindow::on_rdb_rechLoc_clicked()
{
    ui->cb_typeSearch->show();
    ui->cb_typeSearch->setDisabled(false);
    ui->lbl_titre->setHidden(true);
}
/**
 * @fn on_rdb_rechDist_clicked()
 * @author: Mercier Laurent
 * @date 03/06/2020
 * @brief   gestion de l'activation du radio bouton de recherche distante et locale
 *
 */
void MainWindow::on_rdb_rechDist_clicked()
{
    ui->cb_typeSearch->setHidden(true);
    ui->cb_typeSearch->setDisabled(true);
    ui->lbl_titre->setHidden(false);
}
/**
 * @fn on_btn_credit_clicked()
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief   gestion du click sur le bouton "crédits"
 *
 */
void MainWindow::on_btn_credit_clicked()
{
    C_credit *crdt = new C_credit();
    crdt->show();
}
/**
 * @fn on_btn_aPropos_clicked()
 * @author: Mercier Laurent
 * @date 29/06/2020
 * @brief   gestion du click sur le bouton "a propos"
 *
 */
void MainWindow::on_btn_aPropos_clicked()
{
    C_aPropos *ap= new C_aPropos();
    ap->show();
}
