#include "C_mysqlmanager.h"
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QPluginLoader>
#include <c_biblio.h>

/**
 * @brief constructeur
 *
 * @param parent
 */
C_MySQLManager::C_MySQLManager(QObject *parent, C_biblio *_biblio)
    : QObject(parent)

{
    dvdtheque = _biblio;
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
bool C_MySQLManager::connection(QString db, QString adress, int port, QString user, QString password)
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
        return true;
    }
    else {
        emit disconnected();
        qDebug() << "Echec d'ouverture de la base de donnée";
        qDebug() << m_dvdDB.lastError();
        return false;
    }
}
/**
 * @fn close()
 * @author: Mercier Laurent
 * @date 10/06/2020
 * @brief suppression
 * @brief fermeture de la connexion a la base de données
 *
 * @return bool
 */
bool C_MySQLManager::close(){
    m_dvdDB.close();
    return true;
}
/**
 * @fn suppressionFilm(int idFilm)
 * @author: Mercier Laurent
 * @date 10/06/2020
 * @brief suppression d'un film dans les base de données
 *
 * @param int   idFilm  id du film à supprimer
 * @return QString
 */
bool C_MySQLManager::suppressionFilm(QString idFilm)
{
    bool result = false;
    QSqlQuery requete;
    requete.prepare("DELETE FROM `film` WHERE `id`="+idFilm);
    result = requete.exec();
    requete.prepare("DELETE FROM `genresfilm` WHERE `id`="+idFilm);
    result = requete.exec();
    requete.prepare("DELETE FROM `stockage` WHERE `id`="+idFilm);
    result = requete.exec();
    return result;
}
/**
 * @fn getGenre(int number)
 * @author: Mercier Laurent
 * @date 09/05/2020
 * @brief recupère le genre de film d'apres le code genre
 *
 * @param number    code genre
 * @return QString  genre du film
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
/**
 * @fn getGenre(int number)
 * @author: Mercier Laurent
 * @date 09/05/2020
 * @brief   enregistrement des modification apportées à un film enregistré
 *
 * @param film      minifilm du film modifier
 * @return bool     indique que la foncton c'est bien déroulée
 */
bool C_MySQLManager::updateFilm(C_miniFilm  &film){
    QSqlQuery requete;
    requete.prepare("UPDATE `film` SET `titre` = ?, `adulte` = ?, `resume` = ?, `titre_origin` = ?, `langue` = ? WHERE `film`.`ID` = ? ");
    requete.addBindValue(film.getTitre());
    requete.addBindValue(film.getAdult());
    requete.addBindValue(film.getResum());
    requete.addBindValue(film.getTitreOri());
    requete.addBindValue(film.getLanguage());
    requete.addBindValue(film.getIdLocal());
    requete.exec();
    return true;
}
/**
 * @fn modification()
 * @author: Mercier Laurent
 * @date 22/05/2020
 * @brief propagation du signal lors d'un modification d'un film enregistré dans la base de données
 *
 */
void C_MySQLManager::modification()
{
    emit modifier();
}
/**
 * @fn getStockage(int id_film)
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
 * @fn deconnection()
 * @author: Mercier Laurent
 * @date 10/05/2020
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
 * @date 06/05/2020
 * @brief réinitialisation du memebre m_resultCounter correspondant au nombre de resultat lors d'une recherche de film dans la base de données
 *
 */
void  C_MySQLManager::resetResultCounter()
{
    m_resultCounter=0;
}


/**
 * @fn getFimlCount()
 * @author: Mercier Laurent
 * @date 06/05/2020
 * @brief retourne le nombre de resultat trouvés lors d'une recherche dans la base de donnéees
 *
 * @return int  nombre de résultats trouvés
 */
int C_MySQLManager::getFilmCount()
{
    return m_resultCounter;
}
/**
 * @fn searchPersonne (QString nom, QString table)
 * @author: Mercier Laurent
 * @date 06/05/2020
 * @brief recher d'une personne acteur, réalisateur, producteur, metteur en scène
 *
 * @param nom   nom a rechercher dans la base de données
 * @param table     table ou doit etre faite la recherche
 */
void C_MySQLManager::searchPersonne (QString nom, QString table){

    m_resultCounter=0;
    C_miniFilm *film = new C_miniFilm();
    int i=0;
    QSqlQuery requeteActor;
    QSqlQuery requeteFilm;
    if(requeteActor.exec("SELECT * FROM "+table+" WHERE "+table+"."+table+"  LIKE '%"+nom+"%'" )){
        while(requeteActor.next()){
            if(requeteFilm.exec("SELECT * FROM film WHERE id_film ="+ requeteActor.value(1).toString())){
                while(requeteFilm.next()){
                    m_resultCounter++;
                    film->setTitre(requeteFilm.value("titre").toString());
                    C_miniFilm *min3 =new C_miniFilm();
                    //ajout de la fiche a la colletion
                    dvdtheque->addFilmLocal(i, min3);
                    dvdtheque->getFilmLocal(i) ->setIdLocal(requeteFilm.value(0).toInt());
                    dvdtheque->getFilmLocal(i) ->setTitre(requeteFilm.value(1).toString());
                    dvdtheque->getFilmLocal(i) ->setAdult(requeteFilm.value(2).toBool());
                    dvdtheque->getFilmLocal(i) ->setResum(requeteFilm.value(3).toString());
                    dvdtheque->getFilmLocal(i) ->setAffiche(requeteFilm.value(4).toString());
                    dvdtheque->getFilmLocal(i) ->setBackdrop(requeteFilm.value(5).toString());
                    dvdtheque->getFilmLocal(i) ->setTitreOri(requeteFilm.value(6).toString());
                    dvdtheque->getFilmLocal(i) ->setLanguage(requeteFilm.value(7).toString());
                    dvdtheque->getFilmLocal(i) ->setAnnee(requeteFilm.value(8).toString());
                    dvdtheque->getFilmLocal(i) ->setVideo(requeteFilm.value(9).toString());
                    dvdtheque->getFilmLocal(i) ->setNote(requeteFilm.value(10).toString());
                    dvdtheque->getFilmLocal(i) ->setVote(requeteFilm.value(11).toString());
                    dvdtheque->getFilmLocal(i) ->setPop(requeteFilm.value(12).toString());
                    dvdtheque->getFilmLocal(i) ->setId_online(requeteFilm.value(13).toInt());
                    dvdtheque->getFilmLocal(i) ->setDateEnr(requeteFilm.value(14).toString());
                    dvdtheque->getFilmLocal(i) ->setIcone(getTempoPath()+"/home.png");
                    dvdtheque->getFilmLocal(i) ->addIcone();
                    dvdtheque->getFilmLocal(i) ->setGenre(getGenre(requeteFilm.value(16).toInt()));
                    dvdtheque->getFilmLocal(i) ->setLocal(true);
                    connect(dvdtheque->getFilmLocal(i) ,SIGNAL(modifier()),this,SLOT(modification()));


                    i++;
                }
            }
            while(dvdtheque->getFilmLocal(i) ){
                if(i<m_resultCounter){
                    int j=0;
                    //recupération des genre dans la table genresfilm et assignation au minifilm
                    requeteFilm.prepare(("SELECT * FROM genresfilm WHERE id_film = "+ QString::number(dvdtheque->getFilmLocal(i)->getIdLocal())));
                    requeteFilm.exec();
                    while(requeteFilm.next()){
                        dvdtheque->getFilmLocal(i) ->setGenres(j,requeteFilm.value(2).toInt());
                        j++;
                    }
                    //recupération du lieu de stockage du film dans la table stockagefilm et assignation au minifilm
                    requeteFilm.prepare(("SELECT * FROM stockagefilm WHERE id_film = "+ QString::number(dvdtheque->getFilmLocal(i)->getIdLocal())));
                    requeteFilm.exec();
                    while(requeteFilm.next()){
                        dvdtheque->getFilmLocal(i) ->setStockage(requeteFilm.value(2).toString());
                    }
                }
                    i++;

            }
        }
    }
}

/**
 * @fn searchTitre(QString titre)
 * @author: Mercier Laurent
 * @date 04/05/2020
 * @brief recherche les titres corrrespondant au texte entré la recherche dans la fenetre principale et retourne les info contenues dans la db après création d'un C_miniFilm
 *
 * @return C_miniFilm*  minifilm du film trouvé
 */
void C_MySQLManager::searchTitre(QString titre)
{
     m_resultCounter=0;
    C_miniFilm *film = new C_miniFilm();
    int i=0;
    QSqlQuery requete;
    if(requete.exec("SELECT * FROM film WHERE titre  LIKE '%"+titre+"%'" )){
        while(requete.next()){
            m_resultCounter++;
            film->setTitre(requete.value("titre").toString());
            C_miniFilm *min3 =new C_miniFilm();
            //ajout de la fiche a la colletion
            dvdtheque->addFilmLocal(i, min3);
            dvdtheque->getFilmLocal(i) ->setIdLocal(requete.value(0).toInt());
            dvdtheque->getFilmLocal(i) ->setTitre(requete.value(1).toString());
            dvdtheque->getFilmLocal(i) ->setAdult(requete.value(2).toBool());
            dvdtheque->getFilmLocal(i) ->setResum(requete.value(3).toString());
            dvdtheque->getFilmLocal(i) ->setAffiche(requete.value(4).toString());
            dvdtheque->getFilmLocal(i) ->setBackdrop(requete.value(5).toString());
            dvdtheque->getFilmLocal(i) ->setTitreOri(requete.value(6).toString());
            dvdtheque->getFilmLocal(i) ->setLanguage(requete.value(7).toString());
            dvdtheque->getFilmLocal(i) ->setAnnee(requete.value(8).toString());
            dvdtheque->getFilmLocal(i) ->setVideo(requete.value(9).toString());
            dvdtheque->getFilmLocal(i) ->setNote(requete.value(10).toString());
            dvdtheque->getFilmLocal(i) ->setVote(requete.value(11).toString());
            dvdtheque->getFilmLocal(i) ->setPop(requete.value(12).toString());
            dvdtheque->getFilmLocal(i) ->setId_online(requete.value(13).toInt());
            dvdtheque->getFilmLocal(i) ->setDateEnr(requete.value(14).toString());
            dvdtheque->getFilmLocal(i) ->setIcone(getTempoPath()+"/home.png");
            dvdtheque->getFilmLocal(i) ->addIcone();
            dvdtheque->getFilmLocal(i) ->setGenre(getGenre(requete.value(16).toInt()));
            dvdtheque->getFilmLocal(i) ->setLocal(true);
            connect(dvdtheque->getFilmLocal(i) ,SIGNAL(modifier()),this,SLOT(modification()));
            i++;
        }
    }
    i=0;

    while(dvdtheque->getFilmLocal(i) ){
        if(i<m_resultCounter){
            int j=0;
            //recupération des genre dans la table genresfilm et assignation au minifilm
            requete.prepare(("SELECT * FROM genresfilm WHERE id_film = "+ QString::number(dvdtheque->getFilmLocal(i)->getIdLocal())));
            requete.exec();
            while(requete.next()){
                dvdtheque->getFilmLocal(i) ->setGenres(j,requete.value(2).toInt());
                j++;
            }
            //recupération du lieu de stockage du film dans la table stockagefilm et assignation au minifilm
            requete.prepare(("SELECT * FROM stockagefilm WHERE id_film = "+ QString::number(dvdtheque->getFilmLocal(i)->getIdLocal())));
            requete.exec();
            while(requete.next()){
                dvdtheque->getFilmLocal(i) ->setStockage(requete.value(2).toString());
            }
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
bool C_MySQLManager::saveFilm(C_miniFilm &film, QString _date_enr, QString _stock)
{
    bool result  =false;
    QDate dateR;
    dateR= QstringToQDate( film.getRelease());
    QSqlQuery requete;

    try{
        requete.prepare("INSERT INTO `film` (`ID`, `titre`, `adulte`, `resume`, `poster_path`, `backdrop`, `titre_origin`, `langue`, `date_real`, `video`, `note`, `vote_count`, `popularity`, `id_film`, `date_enr`, `stockage`, `genre`) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        requete.addBindValue(NULL); //ID
        requete.addBindValue(film.getTitre());//titre
        requete.addBindValue(film.getAdult());//adulte
        requete.addBindValue(film.getResum());//resume
        QString basename = QFileInfo(film.getAffiche()).fileName();
        QFile::copy(film.getAffiche(),getHardPath()+"/"+QFileInfo(film.getAffiche()).fileName());
        requete.addBindValue(getHardPath()+"/"+ basename);//poster_path
        requete.addBindValue(film.getBackdrop());//backdrop
        requete.addBindValue(film.getTitreOri());//titreOri
        requete.addBindValue(film.getLanguage());//language
        requete.addBindValue(dateR);//date_real
        requete.addBindValue(film.getVideo());//video
        requete.addBindValue(film.getNote());//note
        requete.addBindValue(film.getVote());//vote_couunt
        requete.addBindValue(film.getPop());//popularity
        requete.addBindValue(film.getId_online());//id_film
        requete.addBindValue(_date_enr);
        requete.addBindValue(_stock);
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
 * @fn  getCodeParental()
 * @author: Mercier Laurent
 * @date 06/05/2020
 * @brief   retourne sous forme de QString le code parental enregistré dans la base de données
 *
 * @return QString  code parental
 */
QString C_MySQLManager::getCodeParental()
{
      QString result="";
      QSqlQuery requete;
      requete.prepare("SELECT * FROM param WHERE ID=1");
      requete.exec();
      if(requete.next()){
          result = requete.value(3).toString();
      }
      return result;
}

/**
 * @fn  QstringToQDate(QString date)
 * @author: Mercier Laurent
 * @date 06/05/2020
 * @brief conversion d'une QString en QDate
 *
 * @param date  date sour forme QString
 * @return QDate    date sousfrme de QDate
 */
QDate C_MySQLManager::QstringToQDate(QString date){

    QDate Date = QDate::fromString(date,"yyyy-MM-dd");
    return Date;
}
/**
 * @fn getHardPath(int number)
 * @author: Mercier Laurent
 * @date 06/06/2020
 * @brief retourne les chemin fixe
 *
 */
QString C_MySQLManager::getHardPath(){
    QSqlQuery requete;
     QString hard ="";
    if(requete.exec("SELECT * FROM param WHERE ID=1"))
    {
       if( requete.next()){
            hard =  QVariant(requete.value(2)).toString();
            return hard;
       }
    }
    return hard;
}

/**
 * @fn getHardPath(int number)
 * @author: Mercier Laurent
 * @date 06/06/2020
 * @brief retourne les chemin fixe
 *
 */
QString C_MySQLManager::getTempoPath(){
    QSqlQuery requete;
    QString tempo="";
    if(requete.exec("SELECT * FROM param WHERE ID=1"))
    {
       if( requete.next()){
       QString tempo =  QVariant(requete.value(1)).toString();
       return tempo;
       }
    }
    return tempo;

}
