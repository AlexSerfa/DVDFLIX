#include "C_details.h"
#include "ui_C_details.h"
#include <C_mysqlmanager.h>
#include <C_minifilm.h>


const QString database = "dvdflix";/**< nom de la base de donnée */
const QString adress = "127.0.0.1";/**< adresse du serveur mysql */
const int port = 3308;/**< port du serveur mysql */
const QString user ="root";/**< nom utilisateur sur le server mysql */
const QString password = "coucou256!";/**< mot de passe du serveur mysql */

/**
 * @fn C_details(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_details)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief constructeur
 *
 * @param parent
 */
C_details::C_details(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_details)
{
    ui->setupUi(this);
    m_affiche="inconnu";
    m_backdrop="inconnu";

}

/**
 * @fn ~C_details()
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief destructeur
 *
 */
C_details::~C_details()
{
    delete ui;
}
/**
 * @brief
 *
 * @param film
 */
void C_details::setFilm(C_miniFilm &film){
    m_film = &film;
}

/**
 * @fn listStockage())
 * @author: Mercier Laurent
 * @date 10/05/2020
 * @brief rempli et active le combobox des lieux de stockage
 *         et affiche le lieu de stockage actuelle de l'oeuvre
 *
 *
 */
void C_details::listStockage()
{
    QStringList liste;
    liste = sql->getStockageList();
    ui->cbb_stockage->addItems(liste);
    ui->txt_stock->setText(sql->getStockage(m_film->getIdLocal()));

}


/**
 * @fn addAffiche(QString affiche)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stockage du nom du fichier le l'affiche
 *
 * @param affiche
 */
void C_details::addAffiche(QString affiche)
{
    m_affiche=affiche;
}
/**
 * @fn addAffichePicture(QPixmap( picture))
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de l'affiche
 *
 * @param picture
 */
void C_details::addAffichePicture(QPixmap( picture)){
    int w = ui->lbl_front->width();
    int h = ui->lbl_front->height();
    ui->lbl_front->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));

}

/**
 * @fnaddTitreOri(QString titreOri)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage du titre original
 *
 * @param titreOri
 */
void C_details::addTitreOri(QString titreOri)
{
    ui->txt_titreOri->setText(titreOri);
}

/**
 * @fn addLanguage(QString language)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de la langue du film
 *
 * @param language
 */
void C_details::addLanguage(QString language)
{
    ui->txt_langue->setText(language);
}

/**
 * @fn addBackdropPicture(QPixmap picture)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de l'arrière de la jacquette
 *
 * @param picture
 */
void C_details::addBackdropPicture(QPixmap picture)
{
    int w = ui->lbl_front->width();
    int h = ui->lbl_front->height();
    ui->lbl_back->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));
}

/**
 * @fn addBackdrop(QString backdrop)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief stockage du nom  du fichier de l'image de l'arrière de la jacquette
 *
 * @param backdrop
 */
void C_details::addBackdrop(QString backdrop)
{
    m_backdrop=backdrop;
}

/**
 * @fn addAdult(QString adult)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de film adulte ou non
 *
 * @param adult
 */
void C_details::addAdult(QString adult)
{
    ui->txt_adult->setText(adult);
}

/**
 * @fn addNote(QString note)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de la note obtenue par le film
 *
 * @param note
 */
void C_details::addNote(QString note)
{
    ui->lbl_note->setText(note);
}

/**
 * @fn addVote(QString vote)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage du nombre de vote
 *
 * @param vote
 */
void C_details::addVote(QString vote)
{
    ui->lbl_vote->setText(vote);
}

/**
 * @fn addGenre(QString genre)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage des genres du film et ajout du genre passé en paramètre a un QVector
 *
 * @param genre
 */
void C_details::addGenre(QString genre)
{
    ui->txt_genre->setText(ui->txt_genre->text()+= " -"+genre);
    m_genres->append(genre);
}

/**
 * @fn addDateReal(QString date)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief date de réalisation du film
 *
 * @param date
 */
void C_details::addDateReal(QString date)
{
    ui->txt_real->setText(date);
}

/**
 * @fn addIdDistant(int id)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de l'id mondial du film
 *
 * @param id
 */
void C_details::addIdDistant(int id)
{
    ui->txt_id_distant->setText(QString::number(id));
}

/**
 * @fn addIdLocal(int id)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de l'id local du film en database
 *
 * @param id
 */
void C_details::addIdLocal(int id)
{
    ui->txt_id_local->setText(QString::number(id));
}
/**
 * @fn addResum(QString resum)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage du resumél du film
 *
 * @param resum
 */
void C_details::addResum(QString resum)
{
    ui->txt_resum->setText(resum);
}

/**
 * @brief
 *
 * @param video
 */
void C_details::addVideo(QString video)
{
    m_video=video;
}

/**
 * @brief
 *
 * @param icone
 */
void C_details::addDispo(QString icone)
{
    ui->lbl_dispo->setPixmap(icone);
}

/**
 * @fn setLocal(bool value)
 * @author: Mercier Laurent
 * @date 05/05/2020
 * @brief flag indiquant si c'est un film local
 *
 * @param value true si film local
 */
void C_details::setLocal(bool value)
{
    m_local = value;
    if(value){
        ui->btn_enregistrer->setEnabled(false);
    }
}

/**
 * @fn addTitre(QString titre)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage du titre du film
 *
 * @param titre
 */
void C_details::addTitre(QString titre)
{
    ui->txt_titre->setText(titre);
}

/**
 * @fn on_btn_modifier_clicked()
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief active les controle pour modification des information du film avant enregistrement en database
 *
 */
void C_details::on_btn_modifier_clicked()
{
    ui->txt_titre->setEnabled(true);
    ui->txt_titreOri->setEnabled(true);
    ui->txt_adult->setEnabled(true);
    ui->txt_resum->setEnabled(true);
    ui->txt_langue->setEnabled(true);
    ui->chk_soustitre->setEnabled(true);
    ui->cbb_stockage->setEnabled(true);
    if(m_local){
        ui->btn_enregistrer->setEnabled(true);
    }
}
/**
 * @fn getFilm()
 * @author: Mercier Laurent
 * @date 08/05/2020
 * @brief retourne le minifilm correspondant au détails
 *
 * @return C_miniFilm minifilm correspondant au détails actuels
 */
C_miniFilm & C_details::getFilm()
{
    return   *m_film;
}
/**
 * @fn on_btn_enregistrer_clicked()
 * @author: Mercier Laurent
 * @date 08/05/2020
 * @brief gere l'evenement click sur le bouton enregistrer et démarre la procédure d'enregistrement dans la base de données.
 *
 */
void C_details::on_btn_enregistrer_clicked()
{
    sql =new C_MySQLManager();
    m_film->setStockage(ui->txt_stock->text());
    sql->saveFilm(getFilm());
}

/**
 * @brief
 *
 * @param arg1
 */
void C_details::on_cbb_stockage_currentIndexChanged(const QString &arg1)
{
    ui->txt_stock->setText(arg1);
}
