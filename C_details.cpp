#include "C_details.h"
#include "ui_C_details.h"
#include <C_mysqlmanager.h>
#include <C_minifilm.h>
#include "c_detail_ajout.h"
#include <QSqlQuery>



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
 * @fn idLocalDetail()
 * @author: Jovanovic Milan
 * @date 09/06/2020
 * @brief récupère les valeurs (acteur, réalisateur, metteur en scène, producteur) depuis la base local
 *        et les affiches dans l'appli "Film local" (dans les champs: acteur, réalisateur etc..)
 *
 */

void C_details::idLocalDetail()
{
    qDebug()<<"appel fn";
        this->idLocal= ui->txt_id_local->text();
        qDebug()<<"id= "+ui->txt_id_local->text();
        qDebug()<<ui->lbl_vote->text();
        qDebug()<<ui->txt_resum->toPlainText();

        /*QSqlDatabase base = QSqlDatabase::addDatabase("QMYSQL","rrr");
        base.setHostName(adress);
        base.setDatabaseName(database);
        base.setPort(port);
        base.setUserName(user);
        base.setPassword(password);
        base.open();*/

        QSqlQuery query;
        query.exec("SELECT * FROM `acteur` WHERE `id_film`="+this->idLocal);

        int i=0;
        while (query.next())
        {
            if(i==0)
            {
                ui->txt_acteur->setText(query.value(2).toString());
            }else
            {
                ui->txt_acteur->setText(ui->txt_acteur->toPlainText()+", "+query.value(2).toString());
            }
            i++;
        }
        query.exec("SELECT * FROM `scene` WHERE `id_film`="+this->idLocal);
        i=0;
        while (query.next())
        {
            if(i==0)
            {
                ui->txt_metteurEnScene->setText(query.value(2).toString());
            }else
            {
                ui->txt_metteurEnScene->setText(ui->txt_metteurEnScene->toPlainText()+", "+query.value(2).toString());
            }
            i++;
        }


        query.exec("SELECT * FROM `realis` WHERE `id_film`="+this->idLocal);
        i=0;
        while (query.next())
        {
            if(i==0)
            {
                ui->txt_realisateur->setText(query.value(2).toString());
            }else
            {
                ui->txt_realisateur->setText(ui->txt_realisateur->toPlainText()+", "+query.value(2).toString());
            }
            i++;
        }
        query.exec("SELECT * FROM `prod` WHERE `id_film`="+this->idLocal);
        i=0;
        while (query.next())
        {
            if(i==0)
            {
                ui->txt_producteur->setText(query.value(2).toString());
            }else
            {
                ui->txt_producteur->setText(ui->txt_producteur->toPlainText()+", "+query.value(2).toString());
            }
            i++;
        }
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

    idLocalDetail();// <---------------------- appel de la fonction ?????

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
 * @fn addTitreOri(QString titreOri)
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
 * @fn addAdult(bool value)
 * @author: Mercier Laurent
 * @date 01/05/2020
 * @brief affichage de film adulte ou non
 *
 * @param adult
 */
void C_details::addAdult(bool value)
{
        ui->chk_adult->setChecked(value);
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
    m_modif=true;
    ui->txt_titre->setEnabled(true);
    ui->txt_titreOri->setEnabled(true);
    ui->chk_adult->setEnabled(true);
    ui->txt_resum->setEnabled(true);
    ui->txt_langue->setEnabled(true);
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

void C_details::modification()
{

    //DEBUG
    qWarning()<<"SLOT modification de la classe c_detail";
    connect(this,SIGNAL(modifier()),m_film,SLOT(modification()));
    emit modifier();
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
    if(m_modif==false)
    {
    sql->saveFilm(getFilm());
    }
   else{
        m_film->setTitre(ui->txt_titre->text());
        m_film->setLanguage(ui->txt_langue->text());
        m_film->setTitreOri(ui->txt_titreOri->text());
        m_film->setResum(ui->txt_resum->toPlainText());
        m_film->setStockage(ui->txt_stock->text());
        sql->updateFilm(getFilm());

        //on bloque tous les controles
        m_modif=true;
        ui->txt_titre->setEnabled(false);
        ui->txt_titreOri->setEnabled(false);
        ui->chk_adult->setEnabled(false);
        ui->txt_resum->setEnabled(false);
        ui->txt_langue->setEnabled(false);
        ui->cbb_stockage->setEnabled(false);
    }
    ui->btn_enregistrer->setEnabled(false);
    //DEBUG
    qWarning()<<"emission du signal de details enregister";
    emit modifier();

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

void C_details::on_chk_adult_stateChanged(int arg1)
{
    if(ui->chk_adult->isChecked()){
        m_film->setAdult(true);
    }else{
        m_film->setAdult(false);
    }
}


void C_details::on_btn_acteur_clicked()
{
    QString ID = ui->txt_id_local->text();
    C_detail_ajout *acteur = new C_detail_ajout(this,"Ajouter acteur",ID,this->ui->txt_acteur);
    acteur->setWindowTitle("Acteur");
    acteur->show();
}

void C_details::on_btn_metteurEnScene_clicked()
{
    QString ID = ui->txt_id_local->text();
    C_detail_ajout *metteur = new C_detail_ajout(this,"Ajouter metteur en scène",ID,this->ui->txt_metteurEnScene);
    metteur->setWindowTitle("Metteur en scène");
    metteur->show();
}

void C_details::on_btn_realisateur_clicked()
{
    QString ID = ui->txt_id_local->text();
    C_detail_ajout *realisateur = new C_detail_ajout(this,"Ajouter réalisateur",ID,this->ui->txt_realisateur);
    realisateur->setWindowTitle("Réalisateur");
    realisateur->show();
}

void C_details::on_btn_producteur_clicked()
{
    QString ID = ui->txt_id_local->text();
    C_detail_ajout *producteur = new C_detail_ajout(this,"Ajouter producteur",ID,this->ui->txt_producteur);
    producteur->setWindowTitle("Producteur");
    producteur->show();
}
