#include "C_details.h"
#include "ui_C_details.h"

/**
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
 * @brief destructeur
 *
 */
C_details::~C_details()
{
    delete ui;
}

/**
 * @brief stockage du nom du fichier le l'affiche
 *
 * @param affiche
 */
void C_details::addAffiche(QString affiche)
{
    m_affiche=affiche;
}
/**
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
 * @brief affichage du titre original
 *
 * @param titreOri
 */
void C_details::addTitreOri(QString titreOri)
{
    ui->txt_titreOri->setText(titreOri);
}

/**
 * @brief affichage de la langue du film
 *
 * @param language
 */
void C_details::addLanguage(QString language)
{
    ui->txt_langue->setText(language);
}

/**
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
 * @brief stockage du nom  du fichier de l'image de l'arrière de la jacquette
 *
 * @param backdrop
 */
void C_details::addBackdrop(QString backdrop)
{
    m_backdrop=backdrop;
}

/**
 * @brief affichage de film adulte ou non
 *
 * @param adult
 */
void C_details::addAdult(QString adult)
{
    ui->txt_adult->setText(adult);
}

/**
 * @brief affichage de la note obtenue par le film
 *
 * @param note
 */
void C_details::addNote(QString note)
{
    ui->lbl_note->setText(note);
}

/**
 * @brief affichage du nombre de vote
 *
 * @param vote
 */
void C_details::addVote(QString vote)
{
    ui->lbl_vote->setText(vote);
}

/**
 * @brief affichage des genres du film et ajout du genre passé en paramètre a un QVector
 *
 * @param genre
 */
void C_details::addGenre(QString genre)
{
    ui->txt_genre->setText(ui->txt_genre->text()+=genre);
    m_genres->append(genre);
}

/**
 * @brief date de réalisation du film
 *
 * @param date
 */
void C_details::addDateReal(QString date)
{
    ui->txt_real->setText(date);
}

/**
 * @brief affichage de l'id mondial du film
 *
 * @param id
 */
void C_details::addIdDistant(int id)
{
    ui->txt_id_distant->setText(QString::number(id));
}

/**
 * @brief affichage de l'id local du film en database
 *
 * @param id
 */
void C_details::addIdLocal(int id)
{
    ui->txt_id_local->setText(QString::number(id));
}
/**
 * @brief affichage du resumél du film
 *
 * @param resum
 */
void C_details::addResum(QString resum)
{
    ui->txt_resum->setText(resum);
}

void C_details::addVideo(QString video)
{
    m_video=video;
}

/**
 * @brief affichage du titre du film
 *
 * @param titre
 */
void C_details::addTitre(QString titre)
{
    ui->txt_titre->setText(titre);
}

/**
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

}
