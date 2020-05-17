/********************************************************************************
** Form generated from reading UI file 'c_options.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_OPTIONS_H
#define UI_C_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_options
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *txt_utilisateur;
    QLineEdit *txt_mdp;
    QLineEdit *txt_adresse;
    QLineEdit *txt_port;
    QLineEdit *txt_tempo;
    QLineEdit *txt_fixe;
    QLabel *label_13;
    QLabel *error_list;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txt_adrDbSecu;
    QLineEdit *txt_portDbSecu;
    QPushButton *pushButton_modifier;
    QLabel *label_9;

    void setupUi(QDialog *C_options)
    {
        if (C_options->objectName().isEmpty())
            C_options->setObjectName(QString::fromUtf8("C_options"));
        C_options->resize(392, 692);
        formLayoutWidget = new QWidget(C_options);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 20, 321, 341));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        pushButton = new QPushButton(formLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(150, 30));

        formLayout->setWidget(6, QFormLayout::FieldRole, pushButton);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        txt_utilisateur = new QLineEdit(formLayoutWidget);
        txt_utilisateur->setObjectName(QString::fromUtf8("txt_utilisateur"));

        formLayout->setWidget(0, QFormLayout::FieldRole, txt_utilisateur);

        txt_mdp = new QLineEdit(formLayoutWidget);
        txt_mdp->setObjectName(QString::fromUtf8("txt_mdp"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txt_mdp);

        txt_adresse = new QLineEdit(formLayoutWidget);
        txt_adresse->setObjectName(QString::fromUtf8("txt_adresse"));
        txt_adresse->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, txt_adresse);

        txt_port = new QLineEdit(formLayoutWidget);
        txt_port->setObjectName(QString::fromUtf8("txt_port"));
        txt_port->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, txt_port);

        txt_tempo = new QLineEdit(formLayoutWidget);
        txt_tempo->setObjectName(QString::fromUtf8("txt_tempo"));

        formLayout->setWidget(4, QFormLayout::FieldRole, txt_tempo);

        txt_fixe = new QLineEdit(formLayoutWidget);
        txt_fixe->setObjectName(QString::fromUtf8("txt_fixe"));

        formLayout->setWidget(5, QFormLayout::FieldRole, txt_fixe);

        label_13 = new QLabel(C_options);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(340, 600, 201, 111));
        error_list = new QLabel(C_options);
        error_list->setObjectName(QString::fromUtf8("error_list"));
        error_list->setGeometry(QRect(90, 370, 191, 51));
        formLayoutWidget_2 = new QWidget(C_options);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(60, 500, 241, 161));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(formLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(formLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_8);

        txt_adrDbSecu = new QLineEdit(formLayoutWidget_2);
        txt_adrDbSecu->setObjectName(QString::fromUtf8("txt_adrDbSecu"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, txt_adrDbSecu);

        txt_portDbSecu = new QLineEdit(formLayoutWidget_2);
        txt_portDbSecu->setObjectName(QString::fromUtf8("txt_portDbSecu"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, txt_portDbSecu);

        pushButton_modifier = new QPushButton(formLayoutWidget_2);
        pushButton_modifier->setObjectName(QString::fromUtf8("pushButton_modifier"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, pushButton_modifier);

        label_9 = new QLabel(C_options);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(110, 470, 201, 21));

        retranslateUi(C_options);

        QMetaObject::connectSlotsByName(C_options);
    } // setupUi

    void retranslateUi(QDialog *C_options)
    {
        C_options->setWindowTitle(QCoreApplication::translate("C_options", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("C_options", "Mot de passe", nullptr));
        label_3->setText(QCoreApplication::translate("C_options", "Adresse", nullptr));
        label_4->setText(QCoreApplication::translate("C_options", "Port", nullptr));
        label_5->setText(QCoreApplication::translate("C_options", "Chemin tempo", nullptr));
        label_6->setText(QCoreApplication::translate("C_options", "Chemin fixe", nullptr));
        pushButton->setText(QCoreApplication::translate("C_options", "Enregistrer", nullptr));
        label->setText(QCoreApplication::translate("C_options", "Utilisateur", nullptr));
        txt_utilisateur->setText(QCoreApplication::translate("C_options", "root", nullptr));
        txt_mdp->setText(QCoreApplication::translate("C_options", "admin", nullptr));
        txt_adresse->setText(QString());
        txt_port->setText(QString());
        txt_tempo->setText(QCoreApplication::translate("C_options", "a", nullptr));
        txt_fixe->setText(QCoreApplication::translate("C_options", "b", nullptr));
        label_13->setText(QString());
        error_list->setText(QString());
        label_7->setText(QCoreApplication::translate("C_options", "Adresse DB Securit\303\251", nullptr));
        label_8->setText(QCoreApplication::translate("C_options", "Port DB Securit\303\251", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("C_options", "Modifier", nullptr));
        label_9->setText(QCoreApplication::translate("C_options", "Modification adresse et port ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_options: public Ui_C_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_OPTIONS_H
