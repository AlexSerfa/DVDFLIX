/********************************************************************************
** Form generated from reading UI file 'C_minifilm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_MINIFILM_H
#define UI_C_MINIFILM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_miniFilm
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lbl_genre;
    QLabel *lbl_T_annee;
    QLabel *lbl_ico;
    QPushButton *btn_details;
    QLabel *lbl_affiche;
    QLabel *lbl_T_note;
    QLabel *lbl_titre;
    QLabel *lbl_note;
    QLabel *lbl_annee;
    QLabel *lbl_T_genre;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *C_miniFilm)
    {
        if (C_miniFilm->objectName().isEmpty())
            C_miniFilm->setObjectName(QString::fromUtf8("C_miniFilm"));
        C_miniFilm->resize(230, 300);
        C_miniFilm->setStyleSheet(QString::fromUtf8("background-color : rgb(255, 255, 255)"));
        layoutWidget = new QWidget(C_miniFilm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 231, 301));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lbl_genre = new QLabel(layoutWidget);
        lbl_genre->setObjectName(QString::fromUtf8("lbl_genre"));

        gridLayout->addWidget(lbl_genre, 5, 1, 1, 1);

        lbl_T_annee = new QLabel(layoutWidget);
        lbl_T_annee->setObjectName(QString::fromUtf8("lbl_T_annee"));

        gridLayout->addWidget(lbl_T_annee, 6, 0, 1, 1);

        lbl_ico = new QLabel(layoutWidget);
        lbl_ico->setObjectName(QString::fromUtf8("lbl_ico"));
        lbl_ico->setMinimumSize(QSize(75, 75));
        lbl_ico->setBaseSize(QSize(50, 50));
        lbl_ico->setScaledContents(true);

        gridLayout->addWidget(lbl_ico, 1, 2, 1, 1);

        btn_details = new QPushButton(layoutWidget);
        btn_details->setObjectName(QString::fromUtf8("btn_details"));

        gridLayout->addWidget(btn_details, 5, 2, 2, 1);

        lbl_affiche = new QLabel(layoutWidget);
        lbl_affiche->setObjectName(QString::fromUtf8("lbl_affiche"));
        lbl_affiche->setScaledContents(true);

        gridLayout->addWidget(lbl_affiche, 1, 0, 4, 2);

        lbl_T_note = new QLabel(layoutWidget);
        lbl_T_note->setObjectName(QString::fromUtf8("lbl_T_note"));
        QFont font;
        font.setPointSize(12);
        lbl_T_note->setFont(font);
        lbl_T_note->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_T_note, 3, 2, 1, 1);

        lbl_titre = new QLabel(layoutWidget);
        lbl_titre->setObjectName(QString::fromUtf8("lbl_titre"));
        lbl_titre->setFont(font);
        lbl_titre->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_titre, 0, 0, 1, 3);

        lbl_note = new QLabel(layoutWidget);
        lbl_note->setObjectName(QString::fromUtf8("lbl_note"));
        QFont font1;
        font1.setPointSize(16);
        lbl_note->setFont(font1);
        lbl_note->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lbl_note, 4, 2, 1, 1);

        lbl_annee = new QLabel(layoutWidget);
        lbl_annee->setObjectName(QString::fromUtf8("lbl_annee"));

        gridLayout->addWidget(lbl_annee, 6, 1, 1, 1);

        lbl_T_genre = new QLabel(layoutWidget);
        lbl_T_genre->setObjectName(QString::fromUtf8("lbl_T_genre"));

        gridLayout->addWidget(lbl_T_genre, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 2, 1, 1);


        retranslateUi(C_miniFilm);

        QMetaObject::connectSlotsByName(C_miniFilm);
    } // setupUi

    void retranslateUi(QWidget *C_miniFilm)
    {
        C_miniFilm->setWindowTitle(QCoreApplication::translate("C_miniFilm", "Form", nullptr));
        lbl_genre->setText(QCoreApplication::translate("C_miniFilm", "inconu", nullptr));
        lbl_T_annee->setText(QCoreApplication::translate("C_miniFilm", "Ann\303\251e:", nullptr));
        lbl_ico->setText(QString());
        btn_details->setText(QCoreApplication::translate("C_miniFilm", "D\303\251tails", nullptr));
        lbl_affiche->setText(QCoreApplication::translate("C_miniFilm", "TextLabel", nullptr));
        lbl_T_note->setText(QCoreApplication::translate("C_miniFilm", "Note:", nullptr));
        lbl_titre->setText(QCoreApplication::translate("C_miniFilm", "Inconnu", nullptr));
        lbl_note->setText(QCoreApplication::translate("C_miniFilm", "0", nullptr));
        lbl_annee->setText(QCoreApplication::translate("C_miniFilm", "inconnue", nullptr));
        lbl_T_genre->setText(QCoreApplication::translate("C_miniFilm", "Genre:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_miniFilm: public Ui_C_miniFilm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_MINIFILM_H
