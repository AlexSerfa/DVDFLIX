#include "C_minifilm.h"
#include "ui_C_minifilm.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <C_details.h>




/**
 * @brief constructeur
 *
 * @param parent
 */
C_miniFilm::C_miniFilm(QWidget *parent) :
    QWidget(parent)
   , ui(new Ui::C_miniFilm),m_Affiche(""),m_Icone(""),m_local(false)
{
    ui->setupUi(this);
}

/**
 * @brief destructeur
 *
 */
C_miniFilm::~C_miniFilm()
{
    delete ui;
}

/**
 * @fn on_btn_details_clicked()
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief gère le clique sur le bouton "details" et ouvre la fenetre de détails concernant le film
 *          -recupère le genre du film dans la base de données
 *
 */
void C_miniFilm::on_btn_details_clicked()
{
 C_details *detail= new C_details();

 detail->resize(810,919);
 detail->show();
 detail->addNote(m_notation);
 detail->addVote(m_vote);
 if(m_adult){
    detail->addAdult(true);
 }else{
    detail->addAdult(false);
 }
 detail->addResum(m_resum);
 detail->addTitre(m_titre);
 detail->addAffiche(m_Affiche);
 detail->addIdLocal(m_idLocal);
 detail->addBackdrop(m_backdrop);
 detail->addDateReal(m_release);
 detail->addLanguage(m_language);
 detail->addTitreOri(m_titreOri);
 detail->addIdDistant(m_id_online);
 detail->addDispo(m_Icone);
 detail->setLocal(m_local);
 detail->setFilm(*this);
 detail->listStockage();
 detail->idLocalDetail();
 int i=0;
 QSqlQuery requete;
 C_MySQLManager  *sql =new C_MySQLManager(this);

 while(m_genres[i]!=0){
     QString genre =sql->getGenre(m_genres[i]);

     detail->addGenre(genre);
     i++;
 }

 detail->addAffichePicture(this->getAffiche());
 connect(detail,SIGNAL(modifier()),this,SLOT(modification()));

}






/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retournourne le nombre de vote pour ce film
 *
 * @return QString
 */
QString C_miniFilm::getVote() const
{
    return m_vote;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock le nombre de vote pour ce film
 *
 * @param vote
 */
void C_miniFilm::setVote(const QString &vote)
{
    m_vote = vote;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne la date d'enregistrement du film
 *
 * @return QString  date d'enregistrement
 */
QString C_miniFilm::getDateEnr() const
{
    return m_date_enregistrement;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock la date d'enregistrement dans la base de données
 *
 * @param DateEnr   date d'enregistrement
 */
void C_miniFilm::setDateEnr(const QString &DateEnr)
{
    m_date_enregistrement = DateEnr;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief definit si le film est un film local
 *
 * @param value true si local, false si distant
 */
void C_miniFilm::setLocal(bool value)
{
    m_local=value;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief   retourne true si c'est un film local
 *
 * @return bool true si loca, false si distant
 */
bool C_miniFilm::getLocal() const
{
    return m_local;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief   stock le lieu de stockage du film
 *
 * @param stock lieu de stockage
 */
void C_miniFilm::setStockage(QString stock)
{
    m_stockage=stock;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief   retourne le lieux de stockage du film
 *
 * @return QString
 */
QString C_miniFilm::getStockage()
{
    return m_stockage;
}

/**
 * @author: Mercier Laurent
 * @date 15/05/2020
 * @brief propagation du signal de modification de la fiche de détails du film
 *
 */
void C_miniFilm::modification()
{
    emit modifier();
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne le lien pour le trailer du film
 *
 * @return QString
 */
QString C_miniFilm::getVideo() const
{
    return m_video;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock le lien du trailer du film
 *
 * @param video
 */
void C_miniFilm::setVideo(const QString &video)
{
    m_video = video;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne la date de réalisation du film
 *
 * @return QString
 */
QString C_miniFilm::getRelease() const
{
    return m_release;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock la date de réalisation du film
 *
 * @param release
 */
void C_miniFilm::setRelease(const QString &release)
{
    m_release = release;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne la popularité du film
 *
 * @return float
 */
QString C_miniFilm::getPop() const
{
    return m_pop;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock la popularité du film
 *
 * @param pop
 */
void C_miniFilm::setPop(QString pop)
{
    m_pop = pop;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne le résumé du film
 *
 * @return QString
 */
QString C_miniFilm::getResum() const
{
    return m_resum;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock le résumé du film
 *
 * @param resum
 */
void C_miniFilm::setResum(const QString &resum)
{
    m_resum = resum;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne le titre original du film
 *
 * @return QString
 */
QString C_miniFilm::getTitreOri() const
{
    return m_titreOri;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock le titre original du film
 *
 * @param titreOri
 */
void C_miniFilm::setTitreOri(const QString &titreOri)
{
    m_titreOri = titreOri;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne le language du film
 *
 * @return QString
 */
QString C_miniFilm::getLanguage() const
{
    return m_language;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock le language du film
 *
 * @param language
 */
void C_miniFilm::setLanguage(const QString &language)
{
    m_language = language;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne l'identifiant en ligne du film
 *
 * @return int
 */
int C_miniFilm::getId_online() const
{
    return m_id_online;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock l'identifiant en ligne du film
 *
 * @param id_online
 */
void C_miniFilm::setId_online(int id_online)
{
    m_id_online = id_online;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne l'identifiant du film dans la database local
 *
 * @return int
 */
int C_miniFilm::getIdLocal() const
{
    return m_idLocal;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock l'identifiant du film dans la database local
 *
 * @param idLocal
 */
void C_miniFilm::setIdLocal(int idLocal)
{
    m_idLocal = idLocal;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne le non du fichier de l'image arrière de la jacquette
 *
 * @return QString nom du fichier
 */
QString C_miniFilm::getBackdrop() const
{
    return m_backdrop;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief   stock la valeur du nom de fichier de l'image arière de la jacquette
 *
 * @param backdrop  pointeur sur le nom de l'image
 */
void C_miniFilm::setBackdrop(const QString &backdrop)
{
    m_backdrop = backdrop;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock la valeur du genre à l'index spécifié en paramètre
 *
 * @param index index du tableau des genre
 * @param genre valeur des genre dans le tableau
 */
void C_miniFilm::setGenres(int index,int genre)
{
    m_genres[index] = genre;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne la valeur du genre à l'index spécifié en paramètre
 *
 * @param index
 * @return int
 */
int C_miniFilm::getGenre(int index)
{
    return m_genres[index];
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne l'information indiquant si c'est un film pour adulte
 *
 * @return bool true si film adulte, et false dans le cas contraire
 */
bool C_miniFilm::getAdult() const
{
    return m_adult;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock l'information indiquant si c'est un film pour adulte
 *
 * @param adult true si film adulte, et false dans le cas contraire
 */
void C_miniFilm::setAdult(bool adult)
{
    m_adult = adult;
}
/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stockage et affichage dans le qwidget correspondant du titre du film
 *
 * @param titre titre du film
 */
void C_miniFilm::setTitre(QString titre)
{
    ui->lbl_titre->setText(titre);
    m_titre = titre;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief
 *
 * @return QString
 */
QString C_miniFilm::getTitre()
{
    return m_titre;
}
/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de la date dans le qwidget correspondant
 *
 * @param annee année de réalisation du film
 */
void C_miniFilm::setAnnee(QString annee)
{
    ui->lbl_annee->setText(annee);
    m_release=annee;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief Affichage du genre principal dans le qwidget correspondant
 *
 * @param genre genre principal de l'oeuvre
 */
void C_miniFilm::setGenre(QString genre)
{
    ui->lbl_genre->setText(genre);
}
/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stockage du nom du fichier de la face avant de la jacquette du film
 *
 * @param img nom du fichier
 */
void C_miniFilm::setAffiche(QString img){

    m_Affiche=img;
}
/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief ajout de l'image dans le control correspondant
 *
 */
void C_miniFilm::addAffiche(){

         ui->lbl_affiche->setPixmap(m_Affiche);
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief   stock l'icone du film dans le membre
 *
 * @param img   chemin de l'image de l'icone
 */
void C_miniFilm::setIcone(QString img)
{
    m_Icone=img;
    addIcone();
}
/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne l'icone du film
 *
 * @return QString icone du film
 */
QString C_miniFilm::getIcone()
{
        return m_Icone;
}


/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief ajout de l'icone definissant un film local ou distant
 *
 */
void C_miniFilm::addIcone()
{

    ui->lbl_ico->setPixmap(m_Icone);
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne la note du film
 *
 * @return QString note du film
 */
QString C_miniFilm::getNote() const
{
    return m_notation;
}
/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stock la note du film
 *
 * @param note note du film
 */
void C_miniFilm::setNote(QString note)
{
    ui->lbl_note->setText(note);
    m_notation= note;
}

/**
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief retourne le nom du fichier de l'image de la face avant de la jacquette
 *
 * @return QString nom du fichier
 */
QString C_miniFilm::getAffiche(){
    return m_Affiche;
}
