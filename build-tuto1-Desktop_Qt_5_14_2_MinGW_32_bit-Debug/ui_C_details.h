/********************************************************************************
** Form generated from reading UI file 'C_details.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_DETAILS_H
#define UI_C_DETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_details
{
public:
    QLabel *lbl_front;
    QLabel *lbl_back;
    QLabel *lbl_titre;
    QLabel *lbl_titreOriginal;
    QLabel *lbl_dateReal;
    QLabel *lbl_genre;
    QLabel *lbl_adulte;
    QLabel *lbl_resume;
    QTextEdit *txt_resum;
    QPushButton *btn_enregistrer;
    QPushButton *btn_modifier;
    QComboBox *cbb_stockage;
    QLabel *lbl_stockge;
    QLabel *lbl_support;
    QComboBox *comboBox_2;
    QDateEdit *dateEdit;
    QLabel *lbl_dateEnregistrement;
    QPushButton *btn_trailer;
    QLabel *lbl_language;
    QLabel *lbl_id_distant;
    QGroupBox *groupBox;
    QLabel *lbl_acteur;
    QLabel *lbl_metteurEnScene;
    QLabel *lbl_sousTitrage;
    QCheckBox *chk_soustitre;
    QTextEdit *txt_acteur;
    QLabel *lbl_realisateur;
    QLabel *lbl_producteur;
    QLineEdit *txt_metteurEnScene;
    QLineEdit *txt_realisateur;
    QLineEdit *txt_producteur;
    QPushButton *btn_acteur;
    QPushButton *btn_metteurEnScene;
    QPushButton *btn_realisateur;
    QPushButton *btn_producteur;
    QLineEdit *txt_titre;
    QLineEdit *txt_titreOri;
    QLineEdit *txt_real;
    QLineEdit *txt_genre;
    QLineEdit *txt_langue;
    QLineEdit *txt_id_distant;
    QLabel *lbl_id_local;
    QLineEdit *txt_id_local;
    QLabel *lbl_dispo;
    QLabel *lbl_T_note;
    QLabel *lbl_note;
    QLabel *lbl_T_vote;
    QLabel *lbl_vote;
    QLineEdit *txt_stock;
    QLabel *lbl_stock;
    QCheckBox *chk_adult;

    void setupUi(QWidget *C_details)
    {
        if (C_details->objectName().isEmpty())
            C_details->setObjectName(QString::fromUtf8("C_details"));
        C_details->setWindowModality(Qt::WindowModal);
        C_details->resize(810, 919);
        lbl_front = new QLabel(C_details);
        lbl_front->setObjectName(QString::fromUtf8("lbl_front"));
        lbl_front->setGeometry(QRect(40, 20, 311, 421));
        lbl_back = new QLabel(C_details);
        lbl_back->setObjectName(QString::fromUtf8("lbl_back"));
        lbl_back->setGeometry(QRect(360, 20, 311, 421));
        lbl_titre = new QLabel(C_details);
        lbl_titre->setObjectName(QString::fromUtf8("lbl_titre"));
        lbl_titre->setGeometry(QRect(20, 460, 47, 13));
        lbl_titreOriginal = new QLabel(C_details);
        lbl_titreOriginal->setObjectName(QString::fromUtf8("lbl_titreOriginal"));
        lbl_titreOriginal->setGeometry(QRect(20, 490, 71, 16));
        lbl_dateReal = new QLabel(C_details);
        lbl_dateReal->setObjectName(QString::fromUtf8("lbl_dateReal"));
        lbl_dateReal->setGeometry(QRect(20, 520, 101, 16));
        lbl_genre = new QLabel(C_details);
        lbl_genre->setObjectName(QString::fromUtf8("lbl_genre"));
        lbl_genre->setGeometry(QRect(20, 550, 47, 13));
        lbl_adulte = new QLabel(C_details);
        lbl_adulte->setObjectName(QString::fromUtf8("lbl_adulte"));
        lbl_adulte->setGeometry(QRect(288, 520, 101, 16));
        lbl_resume = new QLabel(C_details);
        lbl_resume->setObjectName(QString::fromUtf8("lbl_resume"));
        lbl_resume->setGeometry(QRect(20, 600, 47, 13));
        lbl_resume->setLineWidth(1);
        lbl_resume->setWordWrap(true);
        txt_resum = new QTextEdit(C_details);
        txt_resum->setObjectName(QString::fromUtf8("txt_resum"));
        txt_resum->setEnabled(false);
        txt_resum->setGeometry(QRect(20, 620, 771, 131));
        btn_enregistrer = new QPushButton(C_details);
        btn_enregistrer->setObjectName(QString::fromUtf8("btn_enregistrer"));
        btn_enregistrer->setGeometry(QRect(700, 540, 91, 23));
        btn_modifier = new QPushButton(C_details);
        btn_modifier->setObjectName(QString::fromUtf8("btn_modifier"));
        btn_modifier->setGeometry(QRect(700, 510, 91, 23));
        cbb_stockage = new QComboBox(C_details);
        cbb_stockage->setObjectName(QString::fromUtf8("cbb_stockage"));
        cbb_stockage->setGeometry(QRect(680, 780, 111, 22));
        lbl_stockge = new QLabel(C_details);
        lbl_stockge->setObjectName(QString::fromUtf8("lbl_stockge"));
        lbl_stockge->setGeometry(QRect(680, 760, 91, 16));
        lbl_support = new QLabel(C_details);
        lbl_support->setObjectName(QString::fromUtf8("lbl_support"));
        lbl_support->setGeometry(QRect(680, 810, 91, 16));
        comboBox_2 = new QComboBox(C_details);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(680, 830, 111, 22));
        dateEdit = new QDateEdit(C_details);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(680, 880, 110, 22));
        lbl_dateEnregistrement = new QLabel(C_details);
        lbl_dateEnregistrement->setObjectName(QString::fromUtf8("lbl_dateEnregistrement"));
        lbl_dateEnregistrement->setGeometry(QRect(680, 860, 121, 16));
        btn_trailer = new QPushButton(C_details);
        btn_trailer->setObjectName(QString::fromUtf8("btn_trailer"));
        btn_trailer->setGeometry(QRect(700, 480, 91, 23));
        lbl_language = new QLabel(C_details);
        lbl_language->setObjectName(QString::fromUtf8("lbl_language"));
        lbl_language->setGeometry(QRect(288, 460, 81, 16));
        lbl_id_distant = new QLabel(C_details);
        lbl_id_distant->setObjectName(QString::fromUtf8("lbl_id_distant"));
        lbl_id_distant->setGeometry(QRect(288, 490, 101, 16));
        groupBox = new QGroupBox(C_details);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 760, 651, 151));
        lbl_acteur = new QLabel(groupBox);
        lbl_acteur->setObjectName(QString::fromUtf8("lbl_acteur"));
        lbl_acteur->setGeometry(QRect(10, 20, 47, 13));
        lbl_metteurEnScene = new QLabel(groupBox);
        lbl_metteurEnScene->setObjectName(QString::fromUtf8("lbl_metteurEnScene"));
        lbl_metteurEnScene->setGeometry(QRect(10, 50, 81, 16));
        lbl_sousTitrage = new QLabel(groupBox);
        lbl_sousTitrage->setObjectName(QString::fromUtf8("lbl_sousTitrage"));
        lbl_sousTitrage->setGeometry(QRect(10, 110, 61, 16));
        chk_soustitre = new QCheckBox(groupBox);
        chk_soustitre->setObjectName(QString::fromUtf8("chk_soustitre"));
        chk_soustitre->setEnabled(false);
        chk_soustitre->setGeometry(QRect(80, 110, 70, 17));
        txt_acteur = new QTextEdit(groupBox);
        txt_acteur->setObjectName(QString::fromUtf8("txt_acteur"));
        txt_acteur->setEnabled(false);
        txt_acteur->setGeometry(QRect(90, 20, 481, 31));
        lbl_realisateur = new QLabel(groupBox);
        lbl_realisateur->setObjectName(QString::fromUtf8("lbl_realisateur"));
        lbl_realisateur->setGeometry(QRect(10, 70, 61, 16));
        lbl_realisateur->setFrameShape(QFrame::NoFrame);
        lbl_producteur = new QLabel(groupBox);
        lbl_producteur->setObjectName(QString::fromUtf8("lbl_producteur"));
        lbl_producteur->setGeometry(QRect(10, 90, 71, 16));
        txt_metteurEnScene = new QLineEdit(groupBox);
        txt_metteurEnScene->setObjectName(QString::fromUtf8("txt_metteurEnScene"));
        txt_metteurEnScene->setEnabled(false);
        txt_metteurEnScene->setGeometry(QRect(90, 50, 231, 20));
        txt_realisateur = new QLineEdit(groupBox);
        txt_realisateur->setObjectName(QString::fromUtf8("txt_realisateur"));
        txt_realisateur->setEnabled(false);
        txt_realisateur->setGeometry(QRect(90, 70, 231, 20));
        txt_producteur = new QLineEdit(groupBox);
        txt_producteur->setObjectName(QString::fromUtf8("txt_producteur"));
        txt_producteur->setEnabled(false);
        txt_producteur->setGeometry(QRect(90, 90, 231, 20));
        btn_acteur = new QPushButton(groupBox);
        btn_acteur->setObjectName(QString::fromUtf8("btn_acteur"));
        btn_acteur->setGeometry(QRect(570, 20, 75, 31));
        btn_metteurEnScene = new QPushButton(groupBox);
        btn_metteurEnScene->setObjectName(QString::fromUtf8("btn_metteurEnScene"));
        btn_metteurEnScene->setGeometry(QRect(320, 50, 75, 23));
        btn_realisateur = new QPushButton(groupBox);
        btn_realisateur->setObjectName(QString::fromUtf8("btn_realisateur"));
        btn_realisateur->setGeometry(QRect(320, 70, 75, 23));
        btn_producteur = new QPushButton(groupBox);
        btn_producteur->setObjectName(QString::fromUtf8("btn_producteur"));
        btn_producteur->setGeometry(QRect(320, 90, 75, 23));
        txt_titre = new QLineEdit(C_details);
        txt_titre->setObjectName(QString::fromUtf8("txt_titre"));
        txt_titre->setEnabled(false);
        txt_titre->setGeometry(QRect(50, 460, 231, 20));
        txt_titreOri = new QLineEdit(C_details);
        txt_titreOri->setObjectName(QString::fromUtf8("txt_titreOri"));
        txt_titreOri->setEnabled(false);
        txt_titreOri->setGeometry(QRect(90, 490, 191, 20));
        txt_real = new QLineEdit(C_details);
        txt_real->setObjectName(QString::fromUtf8("txt_real"));
        txt_real->setEnabled(false);
        txt_real->setGeometry(QRect(120, 520, 161, 20));
        txt_genre = new QLineEdit(C_details);
        txt_genre->setObjectName(QString::fromUtf8("txt_genre"));
        txt_genre->setEnabled(false);
        txt_genre->setGeometry(QRect(60, 550, 221, 20));
        txt_langue = new QLineEdit(C_details);
        txt_langue->setObjectName(QString::fromUtf8("txt_langue"));
        txt_langue->setEnabled(false);
        txt_langue->setGeometry(QRect(338, 460, 351, 20));
        txt_id_distant = new QLineEdit(C_details);
        txt_id_distant->setObjectName(QString::fromUtf8("txt_id_distant"));
        txt_id_distant->setEnabled(false);
        txt_id_distant->setGeometry(QRect(388, 490, 101, 20));
        lbl_id_local = new QLabel(C_details);
        lbl_id_local->setObjectName(QString::fromUtf8("lbl_id_local"));
        lbl_id_local->setGeometry(QRect(498, 490, 81, 16));
        txt_id_local = new QLineEdit(C_details);
        txt_id_local->setObjectName(QString::fromUtf8("txt_id_local"));
        txt_id_local->setEnabled(false);
        txt_id_local->setGeometry(QRect(588, 490, 101, 20));
        lbl_dispo = new QLabel(C_details);
        lbl_dispo->setObjectName(QString::fromUtf8("lbl_dispo"));
        lbl_dispo->setGeometry(QRect(720, 50, 81, 81));
        lbl_dispo->setScaledContents(true);
        lbl_T_note = new QLabel(C_details);
        lbl_T_note->setObjectName(QString::fromUtf8("lbl_T_note"));
        lbl_T_note->setGeometry(QRect(720, 209, 75, 19));
        QFont font;
        font.setPointSize(12);
        lbl_T_note->setFont(font);
        lbl_T_note->setAlignment(Qt::AlignCenter);
        lbl_note = new QLabel(C_details);
        lbl_note->setObjectName(QString::fromUtf8("lbl_note"));
        lbl_note->setGeometry(QRect(720, 230, 75, 25));
        QFont font1;
        font1.setPointSize(16);
        lbl_note->setFont(font1);
        lbl_note->setAlignment(Qt::AlignCenter);
        lbl_T_vote = new QLabel(C_details);
        lbl_T_vote->setObjectName(QString::fromUtf8("lbl_T_vote"));
        lbl_T_vote->setGeometry(QRect(720, 270, 81, 20));
        lbl_T_vote->setFont(font);
        lbl_T_vote->setAlignment(Qt::AlignCenter);
        lbl_vote = new QLabel(C_details);
        lbl_vote->setObjectName(QString::fromUtf8("lbl_vote"));
        lbl_vote->setGeometry(QRect(720, 290, 75, 25));
        lbl_vote->setFont(font1);
        lbl_vote->setAlignment(Qt::AlignCenter);
        txt_stock = new QLineEdit(C_details);
        txt_stock->setObjectName(QString::fromUtf8("txt_stock"));
        txt_stock->setEnabled(false);
        txt_stock->setGeometry(QRect(590, 520, 101, 20));
        lbl_stock = new QLabel(C_details);
        lbl_stock->setObjectName(QString::fromUtf8("lbl_stock"));
        lbl_stock->setGeometry(QRect(500, 520, 91, 16));
        chk_adult = new QCheckBox(C_details);
        chk_adult->setObjectName(QString::fromUtf8("chk_adult"));
        chk_adult->setEnabled(false);
        chk_adult->setGeometry(QRect(390, 520, 21, 17));

        retranslateUi(C_details);

        QMetaObject::connectSlotsByName(C_details);
    } // setupUi

    void retranslateUi(QWidget *C_details)
    {
        C_details->setWindowTitle(QCoreApplication::translate("C_details", "Form", nullptr));
        lbl_front->setText(QString());
        lbl_back->setText(QString());
        lbl_titre->setText(QCoreApplication::translate("C_details", "Titre :", nullptr));
        lbl_titreOriginal->setText(QCoreApplication::translate("C_details", "Titre original :", nullptr));
        lbl_dateReal->setText(QCoreApplication::translate("C_details", "Date de r\303\251alisation :", nullptr));
        lbl_genre->setText(QCoreApplication::translate("C_details", "Genre :", nullptr));
        lbl_adulte->setText(QCoreApplication::translate("C_details", "Cat\303\251gorie adulte  :", nullptr));
        lbl_resume->setText(QCoreApplication::translate("C_details", "R\303\251sum\303\251 : ", nullptr));
        btn_enregistrer->setText(QCoreApplication::translate("C_details", "ENREGISTRER", nullptr));
        btn_modifier->setText(QCoreApplication::translate("C_details", "MODIFER", nullptr));
        lbl_stockge->setText(QCoreApplication::translate("C_details", "Lieu de stockage:", nullptr));
        lbl_support->setText(QCoreApplication::translate("C_details", "Type de support :", nullptr));
        lbl_dateEnregistrement->setText(QCoreApplication::translate("C_details", "Date d'enregistrement : ", nullptr));
        btn_trailer->setText(QCoreApplication::translate("C_details", "Bande-annonce", nullptr));
        lbl_language->setText(QCoreApplication::translate("C_details", "Langue :", nullptr));
        lbl_id_distant->setText(QCoreApplication::translate("C_details", "Identifiant mondial :", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_details", "Informations compl\303\251mentaires", nullptr));
        lbl_acteur->setText(QCoreApplication::translate("C_details", "Acteur :", nullptr));
        lbl_metteurEnScene->setText(QCoreApplication::translate("C_details", "Met. en sc\303\250ne :", nullptr));
        lbl_sousTitrage->setText(QCoreApplication::translate("C_details", "Sous-titres :", nullptr));
        chk_soustitre->setText(QCoreApplication::translate("C_details", "oui", nullptr));
        lbl_realisateur->setText(QCoreApplication::translate("C_details", "R\303\251alisateur :", nullptr));
        lbl_producteur->setText(QCoreApplication::translate("C_details", "Producteur :", nullptr));
        btn_acteur->setText(QCoreApplication::translate("C_details", "Ajouter", nullptr));
        btn_metteurEnScene->setText(QCoreApplication::translate("C_details", "Ajouter", nullptr));
        btn_realisateur->setText(QCoreApplication::translate("C_details", "Ajouter", nullptr));
        btn_producteur->setText(QCoreApplication::translate("C_details", "Ajouter", nullptr));
        lbl_id_local->setText(QCoreApplication::translate("C_details", "Identifiant local :", nullptr));
        lbl_dispo->setText(QString());
        lbl_T_note->setText(QCoreApplication::translate("C_details", "Note:", nullptr));
        lbl_note->setText(QCoreApplication::translate("C_details", "0", nullptr));
        lbl_T_vote->setText(QCoreApplication::translate("C_details", "Nb. votes :", nullptr));
        lbl_vote->setText(QCoreApplication::translate("C_details", "0", nullptr));
        lbl_stock->setText(QCoreApplication::translate("C_details", "Lieu de stockage :", nullptr));
        chk_adult->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class C_details: public Ui_C_details {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_DETAILS_H
