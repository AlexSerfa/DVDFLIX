#include "C_mysqlmanager.h"
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>

const QString directoryBase= "d:/tempo68"; /**< chemin du dossier de stockage */
const QString directoryHard ="d:/tempo69";

/**
 * @brief constructeur
 *
 * @param parent
 */
C_MySQLManager::C_MySQLManager(QObject *parent)
    : QObject(parent)
    , min1()
{

}
/**
 * @brief gere la connection à la base de donnée
 *
 * @param db
 * @param adress
 * @param port
 * @param user
 * @param password
 */
void C_MySQLManager::connection(QString db, QString adress, int port, QString user, QString password)
{
    m_dvdDB =QSqlDatabase::addDatabase("QMYSQL");
    m_dvdDB.setHostName(adress);
    m_dvdDB.setPort(port);
    m_dvdDB.setUserName(user);
    m_dvdDB.setPassword(password);
    m_dvdDB.setDatabaseName(db);
    if(m_dvdDB.open()) {
        qDebug() << "Ok - ouverture de la base de donnée";
        emit connected();
        // Exécution d'une requête
        QSqlQuery requete;
    }
    else {
        emit disconnected();
        qDebug() << "Echec d'ouverture de la base de donnée";
        qDebug() << m_dvdDB.lastError();
    }
}
/**
 * @fn getGenre(int number)
 * @author: Mercier Laurent
 * @date 09/05/2020
 * @brief recupère le genre de film d'apres le code genre
 *
 * @param number
 * @return QString
 */
QString C_MySQLManager::getGenre(int number)
{
    QSqlQuery requete;
    if(requete.exec("SELECT * FROM genre WHERE id="+QString::number(number))) {
       if( requete.next()){
        return QVariant(requete.value("nom")).toString();
       }
    }
    return "Inconnu";
}
bool C_MySQLManager::updateFilm(C_miniFilm  &film){
    QSqlQuery requete;
    requete.prepare("UPDATE `film` SET `titre` = ?, `adulte` = ?, `resume` = ?, `titre_origin` = ?, `langue` = ? WHERE `film`.`ID` = ? ");
    requete.addBindValue(film.getTitre());
    requete.addBindValue(film.getAdult());
    requete.addBindValue(film.getResum());
    requete.addBindValue(film.getTitreOri());
    requete.addBindValue(film.getLanguage());
    requete.addBindValue(film.getIdLocal());
    qWarning()<<requete.exec();

    return true;
}

void C_MySQLManager::modification()
{
 //DEBUG
    qWarning()<<"emission du signal depuis sqlManager";
    emit modifier();
}


/**
 * @fn getGenre(int number)
 * @author: Mercier Laurent
 * @date 12/05/2020
 * @brief recupere le lieu de stockage du film
 *
 * @param id_film   identifiant du film
 * @return QString  lieu de stockage du film
 */
QString C_MySQLManager::getStockage(int id_film)
{
    QSqlQuery requete;
    if(requete.exec("SELECT * FROM film WHERE ID="+QString::number(id_film))) {

       if( requete.next()){
        return QVariant(requete.value("stockage")).toString();
       }
    }
    return "inconnu";
}
/**
 * @brief gere la déconnection a la base de donnée
 *
 */
void C_MySQLManager::deconnection(){
    m_dvdDB.close();
    emit disconnected();
}

/**
 * @fn getStockageList()
 * @author: Mercier Laurent
 * @date 10/05/2020
 * @brief recherche lles lieux des stockage des film dans la base de données
 *
 * @return QStringList liste des lieux de stockage
 */
QStringList  C_MySQLManager::getStockageList()
{
    QStringList liste;
    QSqlQuery requete;
    requete.prepare("SELECT * FROM stockage");
    requete.exec();
    while(requete.next()){
        liste.append(requete.value(1).toString());
    }
    return liste;
}
/**
 * @fn getGenre(int number)
 * @author: Mercier Laurent
 * @date 05/05/2020
 * @brief recherche le nombre de film corrrespondant au texte entré la recherche dans la fenetre principale et retourne les info contenues dans la db après création d'un C_miniFilm
 *
 * @return int
 */
int C_MySQLManager::filmCount(QString titre)
{
    int result=0;
    QSqlQuery requete;

    if(requete.exec("SELECT * FROM film WHERE titre="+titre)){
        if (requete.next()) {
            result= requete.value(0).toInt();
        }
    }
    return result;

}
/**
 * @fn getGenre(int number)
 * @author: Mercier Laurent
 * @date 06/05/2020
 * @brief réinitialisation du memebre m_resultCounter correspondant au nombre de resultat lors d'une recherche de film dans la base de données
 *
 */
void  C_MySQLManager::resetResultCounter()
{
    m_resultCounter=0;
}

/**
 * @fn videMinifilm()
 * @author: Mercier Laurent
 * @date 05/05/2020
 * @brief vide le tableau des minifilm locaux
 *
 */
void C_MySQLManager::videMinifilm()
{
    //on vide le tableau de minifilm de resultat en local
    for(int i =0;i<150;i++){
        if(min1[i]){
            min1[i]->~C_miniFilm();
        }
    }
}
/**
 * @brief retourne le nombre de resultat trouvés lors d'une recherche dans la base de donnéees
 *
 * @return int  nombre de résultats trouvés
 */
int C_MySQLManager::getFilmCount()
{
    return m_resultCounter;
}
/**
 * @fn searchTitre(QString titre)
 * @author: Mercier Laurent
 * @date 04/05/2020
 * @brief recherche les titres corrrespondant au texte entré la recherche dans la fenetre principale et retourne les info contenues dans la db après création d'un C_miniFilm
 *
 * @return C_miniFilm*
 */
void C_MySQLManager::searchTitre(QString titre)
{
     m_resultCounter=0;
    C_miniFilm *film = new C_miniFilm();
    int i=0;
    QSqlQuery requete;
    if(requete.exec("SELECT * FROM film WHERE titre="+titre )){
        while(requete.next()){
            m_resultCounter++;
            film->setTitre(requete.value("titre").toString());
            C_miniFilm *min3 =new C_miniFilm();
            //ajout de la fiche a la colletion
            min1[i] =min3;
            min1[i]->setIdLocal(requete.value(0).toInt());
            min1[i]->setTitre(requete.value(1).toString());
            min1[i]->setAdult(requete.value(2).toBool());
            min1[i]->setResum(requete.value(3).toString());
            min1[i]->setAffiche(requete.value(4).toString());
            min1[i]->setBackdrop(requete.value(5).toString());
            min1[i]->setTitreOri(requete.value(6).toString());
            min1[i]->setLanguage(requete.value(7).toString());
            min1[i]->setAnnee(requete.value(8).toString());
            min1[i]->setVideo(requete.value(9).toString());
            min1[i]->setNote(requete.value(10).toString());
            min1[i]->setVote(requete.value(11).toString());
            min1[i]->setPop(requete.value(12).toString());
            min1[i]->setId_online(requete.value(13).toInt());
            min1[i]->setDateEnr(requete.value(14).toString());
            min1[i]->setIcone(directoryBase+"/home.png");
            min1[i]->addIcone();
            min1[i]->setGenre(getGenre(requete.value(16).toInt()));
            min1[i]->setLocal(true);
            connect(min1[i],SIGNAL(modifier()),this,SLOT(modification()));
           // connect(this,SIGNAL(modifier()),))

            i++;
        }
    }
    i=0;
    //recupération des genre dans la table genresfilm et assignation au minifilm
    while(min1[i]){
        int j=0;
        requete.prepare(("SELECT * FROM genresfilm WHERE id_film = "+ QString::number(min1[i]->getIdLocal())));
        requete.exec();
        while(requete.next()){
            min1[i]->setGenres(j,requete.value(2).toInt());
            j++;
        }
        i++;
    }
    i=0;
    //recupération du lieu de stockage du film dans la table stockagefilm et assignation au minifilm
    while(min1[i]){

        requete.prepare(("SELECT * FROM stockagefilm WHERE id_film = "+ QString::number(min1[i]->getIdLocal())));
        requete.exec();
        while(requete.next()){
            min1[i]->setStockage(requete.value(2).toString());
        }
        i++;
    }
}
/**
 * @fn saveFilm(C_miniFilm &film)
 * @author: Mercier Laurent
 * @date 09/05/2020
 * @brief enregistrement d'un film dans la base de donées, des genres du film et du lieu de stockage
 *
 * @param film  film devant etre enregistré
 * @return bool resultat de l'opération, retourne true si enregistrement ok, false sinon.
 */
bool C_MySQLManager::saveFilm(C_miniFilm &film)
{
    bool result  =false;
    QDate dateR;
    dateR= QstringToQDate( film.getRelease());
    //DEBUG 3l
    //qWarning()<<"date: "<< film.getRelease();
    //qWarning()<<"date: "<< QDate::fromString(film.getRelease());
    //qWarning()<<"date: "<< dateR.toString();
    QSqlQuery requete;
    try{
        requete.prepare("INSERT INTO `film` (`ID`, `titre`, `adulte`, `resume`, `poster_path`, `backdrop`, `titre_origin`, `langue`, `date_real`, `video`, `note`, `vote_count`, `popularity`, `id_film`, `date_enr`, `stockage`, `genre`) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        requete.addBindValue(NULL); //ID
        requete.addBindValue(film.getTitre());//titre
        requete.addBindValue(film.getAdult());//adulte
        requete.addBindValue(film.getResum());//resume
        QString basename = QFileInfo(film.getAffiche()).fileName();
        bool resultCopy = QFile::copy(film.getAffiche(), directoryHard+"/"+QFileInfo(film.getAffiche()).fileName());
        //DEBUG
        //qWarning()<<"Fichier image copiée"<<resultCopy;
        //basename =basename;
        requete.addBindValue(directoryHard+"/"+ basename);//poster_path
        requete.addBindValue(film.getBackdrop());//backdrop
        requete.addBindValue(film.getTitreOri());//titreOri
        requete.addBindValue(film.getLanguage());//language
        requete.addBindValue(dateR);//date_real
        requete.addBindValue(film.getVideo());//video
        requete.addBindValue(film.getNote());//note
        requete.addBindValue(film.getVote());//vote_couunt
        requete.addBindValue(film.getPop());//popularity
        requete.addBindValue(film.getId_online());//id_film
        requete.addBindValue(NULL);
        requete.addBindValue(NULL);
        requete.addBindValue(film.getGenre(0));
        requete.exec();
        result =true;
    }
    catch(QException e){

        qWarning()<<"Erreur lors de la requete d'insertion du film: "<<requete.lastError();
        result = false;
    }
    int idFilm; //id locale du film
    //recupération de l'id local du film et insertion des genres dans la table genresfilm
    try {

        requete.prepare("SELECT * FROM film WHERE id_film ="+ QString::number(film.getId_online()));
        requete.exec();
        requete.lastError();
        while(requete.next()){
            idFilm =  requete.value(0).toInt();
        }
        int i=0;
        while(film.getGenre(i)!=0){
            requete.prepare("INSERT INTO `genresfilm` (`ID`, `id_film`, `genre`) VALUES (NULL, '"+QString::number(idFilm)+"', "+QString::number(film.getGenre(i))+");");
            requete.exec();
            i++;
            result =true;
        }
    } catch (QException e) {
        qWarning()<<"Erreur lors de la requete d'insertion des genres: "<<requete.lastError();
        result = false;
    }
    //sauvegarde du lieu de stockage du film
    try {
        requete.prepare("INSERT INTO `stockagefilm` (`ID`, `id_film`, `stockage`) VALUES (NULL, '"+ QString::number(idFilm) +"', '"+ film.getStockage()+"');");
        requete.exec();
        result = true;
    } catch (QException e) {
        qWarning()<<"Erreur lors de la requete d'insertion du lieu  de stockage: "<<requete.lastError();
        result = false;
    }

    return result;
}
/**
 * @brief retourne le noom de la database
 *
 * @return QString   nom de la base de données
 */
QString C_MySQLManager::getDb()
{
    return m_db;
}
/**
 * @brief stock le nom de la database
 *
 * @param db     nom de la base de données
 */
void C_MySQLManager::setDb( QString db)
{
    m_db = db;
}
/**
 * @brief retourne l'adresse ip de la database
 *
 * @return QString   adresse de la base de données
 */
QString C_MySQLManager::getAdress()
{
    return m_adress;
}
/**
 * @brief stock l'adresse ip de la database
 *
 * @param adress    adresse de la base de données
 */
void C_MySQLManager::setAdress(QString adress)
{
    m_adress = adress;
}
/**
 * @brief retourne le  port de la database
 *
 * @return int  port de la base de données
 */
int C_MySQLManager::getPort()
{
    return m_port;
}
/**
 * @brief stock le  port de la database
 *
 * @param port  port de la base de données
 */
void C_MySQLManager::setPort(int port)
{
    m_port = port;
}
/**
 * @brief retourne le nom de l'utilisateur de la db
 *
 * @return QString  nom de l'utilisateur de la base de données
 */
QString C_MySQLManager::getUser()
{
    return m_user;
}
/**
 * @brief stock le nom de l'utilisateur de la db
 *
 * @param user  nom de l'utilisateur de la base de données
 */
void C_MySQLManager::setUser(QString user)
{
    m_user = user;
}
/**
 * @brief retourne le mot de passe de la db
 *
 * @return QString  mot de passe de l'utilisateur de la base de données
 */
QString C_MySQLManager::getPassword()
{
    return m_password;
}
/**
 * @brief stock le password de la db
 *
 * @param password  mot de passe de l'utilisateur de la base de données
 */
void C_MySQLManager::setPassword(QString password)
{
    m_password = password;
}
QDate C_MySQLManager::QstringToQDate(QString date){

    QDate Date = QDate::fromString(date,"yyyy-MM-dd");
    return Date;
}
