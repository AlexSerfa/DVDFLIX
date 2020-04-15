#include "C_minifilm.h"
#include "ui_C_minifilm.h"
#include <QDebug>
C_miniFilm::C_miniFilm(QWidget *parent) :
    QWidget(parent)
   , ui(new Ui::C_miniFilm),m_Affiche("")
{
    ui->setupUi(this);

}

C_miniFilm::~C_miniFilm()
{
    delete ui;
}

void C_miniFilm::on_btn_details_clicked()
{

}
void C_miniFilm::setTitre(QString titre)
{
    ui->lbl_titre->setText(titre);

}
void C_miniFilm::setAnnee(QString annee)
{
    ui->lbl_annee->setText(annee);


}

void C_miniFilm::setGenre(QString genre)
{
    ui->lbl_genre->setText(genre);
}
void C_miniFilm::setAffiche(QString img){
    //ui->lbl_affiche->setPixmap(img);
    m_Affiche=img;
}
void C_miniFilm::addAffiche(){
    ui->lbl_affiche->setPixmap(m_Affiche);
}
void C_miniFilm::setNote(QString note)
{
    ui->lbl_note->setText(note);
}

QString C_miniFilm::getAffiche(){
    return m_Affiche;
}
