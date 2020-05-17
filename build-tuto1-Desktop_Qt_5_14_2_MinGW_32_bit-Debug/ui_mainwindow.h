/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_rechercher;
    QPushButton *btn_ajouter;
    QPushButton *btn_option;
    QLineEdit *ln_titre;
    QLabel *lbl_titre;
    QLabel *lbl__Acteur;
    QLineEdit *ln_titre_2;
    QLabel *lbl_date;
    QLineEdit *ln_titre_3;
    QComboBox *cb_genre;
    QLabel *lbl_date_2;
    QPushButton *btn_previous;
    QPushButton *btn_next;
    QWidget *gridLayoutWidget;
    QGridLayout *hl_minifilm;
    QStackedWidget *dvdtek;
    QWidget *page_1;
    QWidget *gridLayoutWidget_2;
    QGridLayout *grd1;
    QWidget *page_2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *grd2;
    QWidget *page_3;
    QWidget *gridLayoutWidget_4;
    QGridLayout *grd3;
    QWidget *page_4;
    QWidget *gridLayoutWidget_5;
    QGridLayout *grd4;
    QWidget *page_5;
    QWidget *gridLayoutWidget_6;
    QGridLayout *grd5;
    QWidget *page_6;
    QWidget *gridLayoutWidget_7;
    QGridLayout *grd6;
    QWidget *page_7;
    QWidget *gridLayoutWidget_8;
    QGridLayout *grd7;
    QWidget *page_8;
    QWidget *gridLayoutWidget_9;
    QGridLayout *grd8;
    QWidget *page_9;
    QWidget *gridLayoutWidget_10;
    QGridLayout *grd9;
    QWidget *page_10;
    QWidget *gridLayoutWidget_11;
    QGridLayout *grd10;
    QWidget *page_11;
    QWidget *gridLayoutWidget_12;
    QGridLayout *grd11;
    QWidget *page_12;
    QWidget *gridLayoutWidget_13;
    QGridLayout *grd12;
    QWidget *page_13;
    QWidget *gridLayoutWidget_14;
    QGridLayout *grd13;
    QWidget *page_14;
    QWidget *gridLayoutWidget_15;
    QGridLayout *grd14;
    QWidget *page_15;
    QWidget *gridLayoutWidget_16;
    QGridLayout *grd15;
    QWidget *page_16;
    QWidget *gridLayoutWidget_17;
    QGridLayout *grd16;
    QWidget *page_17;
    QWidget *gridLayoutWidget_18;
    QGridLayout *grd17;
    QWidget *page_18;
    QWidget *gridLayoutWidget_19;
    QGridLayout *grd18;
    QWidget *page_19;
    QWidget *gridLayoutWidget_20;
    QGridLayout *grd19;
    QWidget *page_20;
    QWidget *gridLayoutWidget_21;
    QGridLayout *grd20;
    QWidget *page_21;
    QWidget *gridLayoutWidget_22;
    QGridLayout *grd21;
    QLabel *lbl_db_status;
    QGroupBox *grp_rechercheType;
    QRadioButton *rdb_rechLoc;
    QRadioButton *rdb_rechDist;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1368, 800);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_rechercher = new QPushButton(centralwidget);
        btn_rechercher->setObjectName(QString::fromUtf8("btn_rechercher"));
        btn_rechercher->setGeometry(QRect(300, 650, 101, 31));
        btn_ajouter = new QPushButton(centralwidget);
        btn_ajouter->setObjectName(QString::fromUtf8("btn_ajouter"));
        btn_ajouter->setGeometry(QRect(410, 650, 101, 31));
        btn_option = new QPushButton(centralwidget);
        btn_option->setObjectName(QString::fromUtf8("btn_option"));
        btn_option->setGeometry(QRect(0, 10, 61, 31));
        ln_titre = new QLineEdit(centralwidget);
        ln_titre->setObjectName(QString::fromUtf8("ln_titre"));
        ln_titre->setGeometry(QRect(80, 650, 211, 20));
        lbl_titre = new QLabel(centralwidget);
        lbl_titre->setObjectName(QString::fromUtf8("lbl_titre"));
        lbl_titre->setGeometry(QRect(20, 650, 47, 13));
        QFont font;
        font.setPointSize(12);
        lbl_titre->setFont(font);
        lbl__Acteur = new QLabel(centralwidget);
        lbl__Acteur->setObjectName(QString::fromUtf8("lbl__Acteur"));
        lbl__Acteur->setGeometry(QRect(20, 680, 47, 13));
        lbl__Acteur->setFont(font);
        ln_titre_2 = new QLineEdit(centralwidget);
        ln_titre_2->setObjectName(QString::fromUtf8("ln_titre_2"));
        ln_titre_2->setGeometry(QRect(80, 680, 211, 20));
        lbl_date = new QLabel(centralwidget);
        lbl_date->setObjectName(QString::fromUtf8("lbl_date"));
        lbl_date->setGeometry(QRect(20, 710, 47, 13));
        lbl_date->setFont(font);
        ln_titre_3 = new QLineEdit(centralwidget);
        ln_titre_3->setObjectName(QString::fromUtf8("ln_titre_3"));
        ln_titre_3->setGeometry(QRect(80, 710, 211, 20));
        cb_genre = new QComboBox(centralwidget);
        cb_genre->addItem(QString());
        cb_genre->addItem(QString());
        cb_genre->addItem(QString());
        cb_genre->addItem(QString());
        cb_genre->addItem(QString());
        cb_genre->setObjectName(QString::fromUtf8("cb_genre"));
        cb_genre->setGeometry(QRect(80, 740, 211, 22));
        lbl_date_2 = new QLabel(centralwidget);
        lbl_date_2->setObjectName(QString::fromUtf8("lbl_date_2"));
        lbl_date_2->setGeometry(QRect(20, 740, 47, 13));
        lbl_date_2->setFont(font);
        btn_previous = new QPushButton(centralwidget);
        btn_previous->setObjectName(QString::fromUtf8("btn_previous"));
        btn_previous->setGeometry(QRect(560, 660, 75, 23));
        btn_next = new QPushButton(centralwidget);
        btn_next->setObjectName(QString::fromUtf8("btn_next"));
        btn_next->setGeometry(QRect(680, 660, 75, 23));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(690, 0, 791, 571));
        hl_minifilm = new QGridLayout(gridLayoutWidget);
        hl_minifilm->setObjectName(QString::fromUtf8("hl_minifilm"));
        hl_minifilm->setContentsMargins(0, 0, 0, 0);
        dvdtek = new QStackedWidget(centralwidget);
        dvdtek->setObjectName(QString::fromUtf8("dvdtek"));
        dvdtek->setGeometry(QRect(66, 10, 1235, 630));
        dvdtek->setMinimumSize(QSize(1235, 0));
        dvdtek->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 255);\n"
"background-color: rgb(0, 85, 255);"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        gridLayoutWidget_2 = new QWidget(page_1);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 1241, 631));
        grd1 = new QGridLayout(gridLayoutWidget_2);
        grd1->setSpacing(10);
        grd1->setObjectName(QString::fromUtf8("grd1"));
        grd1->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayoutWidget_3 = new QWidget(page_2);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 0, 1241, 631));
        grd2 = new QGridLayout(gridLayoutWidget_3);
        grd2->setObjectName(QString::fromUtf8("grd2"));
        grd2->setContentsMargins(0, 0, 0, 0);
        dvdtek->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayoutWidget_4 = new QWidget(page_3);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 0, 1241, 631));
        grd3 = new QGridLayout(gridLayoutWidget_4);
        grd3->setSpacing(10);
        grd3->setObjectName(QString::fromUtf8("grd3"));
        grd3->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd3->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        gridLayoutWidget_5 = new QWidget(page_4);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 0, 1241, 631));
        grd4 = new QGridLayout(gridLayoutWidget_5);
        grd4->setSpacing(10);
        grd4->setObjectName(QString::fromUtf8("grd4"));
        grd4->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd4->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        gridLayoutWidget_6 = new QWidget(page_5);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 0, 1241, 631));
        grd5 = new QGridLayout(gridLayoutWidget_6);
        grd5->setSpacing(10);
        grd5->setObjectName(QString::fromUtf8("grd5"));
        grd5->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd5->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        gridLayoutWidget_7 = new QWidget(page_6);
        gridLayoutWidget_7->setObjectName(QString::fromUtf8("gridLayoutWidget_7"));
        gridLayoutWidget_7->setGeometry(QRect(0, 0, 1241, 631));
        grd6 = new QGridLayout(gridLayoutWidget_7);
        grd6->setSpacing(10);
        grd6->setObjectName(QString::fromUtf8("grd6"));
        grd6->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd6->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        gridLayoutWidget_8 = new QWidget(page_7);
        gridLayoutWidget_8->setObjectName(QString::fromUtf8("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(0, 0, 1241, 631));
        grd7 = new QGridLayout(gridLayoutWidget_8);
        grd7->setSpacing(10);
        grd7->setObjectName(QString::fromUtf8("grd7"));
        grd7->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd7->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        gridLayoutWidget_9 = new QWidget(page_8);
        gridLayoutWidget_9->setObjectName(QString::fromUtf8("gridLayoutWidget_9"));
        gridLayoutWidget_9->setGeometry(QRect(0, 0, 1241, 631));
        grd8 = new QGridLayout(gridLayoutWidget_9);
        grd8->setSpacing(10);
        grd8->setObjectName(QString::fromUtf8("grd8"));
        grd8->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd8->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        gridLayoutWidget_10 = new QWidget(page_9);
        gridLayoutWidget_10->setObjectName(QString::fromUtf8("gridLayoutWidget_10"));
        gridLayoutWidget_10->setGeometry(QRect(0, 0, 1241, 631));
        grd9 = new QGridLayout(gridLayoutWidget_10);
        grd9->setSpacing(10);
        grd9->setObjectName(QString::fromUtf8("grd9"));
        grd9->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd9->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        gridLayoutWidget_11 = new QWidget(page_10);
        gridLayoutWidget_11->setObjectName(QString::fromUtf8("gridLayoutWidget_11"));
        gridLayoutWidget_11->setGeometry(QRect(0, 0, 1241, 631));
        grd10 = new QGridLayout(gridLayoutWidget_11);
        grd10->setSpacing(10);
        grd10->setObjectName(QString::fromUtf8("grd10"));
        grd10->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd10->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_10);
        page_11 = new QWidget();
        page_11->setObjectName(QString::fromUtf8("page_11"));
        gridLayoutWidget_12 = new QWidget(page_11);
        gridLayoutWidget_12->setObjectName(QString::fromUtf8("gridLayoutWidget_12"));
        gridLayoutWidget_12->setGeometry(QRect(0, 0, 1241, 631));
        grd11 = new QGridLayout(gridLayoutWidget_12);
        grd11->setSpacing(10);
        grd11->setObjectName(QString::fromUtf8("grd11"));
        grd11->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd11->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_11);
        page_12 = new QWidget();
        page_12->setObjectName(QString::fromUtf8("page_12"));
        gridLayoutWidget_13 = new QWidget(page_12);
        gridLayoutWidget_13->setObjectName(QString::fromUtf8("gridLayoutWidget_13"));
        gridLayoutWidget_13->setGeometry(QRect(0, 0, 1241, 631));
        grd12 = new QGridLayout(gridLayoutWidget_13);
        grd12->setSpacing(10);
        grd12->setObjectName(QString::fromUtf8("grd12"));
        grd12->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd12->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_12);
        page_13 = new QWidget();
        page_13->setObjectName(QString::fromUtf8("page_13"));
        gridLayoutWidget_14 = new QWidget(page_13);
        gridLayoutWidget_14->setObjectName(QString::fromUtf8("gridLayoutWidget_14"));
        gridLayoutWidget_14->setGeometry(QRect(0, 0, 1241, 631));
        grd13 = new QGridLayout(gridLayoutWidget_14);
        grd13->setSpacing(10);
        grd13->setObjectName(QString::fromUtf8("grd13"));
        grd13->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd13->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName(QString::fromUtf8("page_14"));
        gridLayoutWidget_15 = new QWidget(page_14);
        gridLayoutWidget_15->setObjectName(QString::fromUtf8("gridLayoutWidget_15"));
        gridLayoutWidget_15->setGeometry(QRect(0, 0, 1241, 631));
        grd14 = new QGridLayout(gridLayoutWidget_15);
        grd14->setSpacing(10);
        grd14->setObjectName(QString::fromUtf8("grd14"));
        grd14->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd14->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_14);
        page_15 = new QWidget();
        page_15->setObjectName(QString::fromUtf8("page_15"));
        gridLayoutWidget_16 = new QWidget(page_15);
        gridLayoutWidget_16->setObjectName(QString::fromUtf8("gridLayoutWidget_16"));
        gridLayoutWidget_16->setGeometry(QRect(0, 0, 1241, 631));
        grd15 = new QGridLayout(gridLayoutWidget_16);
        grd15->setSpacing(10);
        grd15->setObjectName(QString::fromUtf8("grd15"));
        grd15->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd15->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_15);
        page_16 = new QWidget();
        page_16->setObjectName(QString::fromUtf8("page_16"));
        gridLayoutWidget_17 = new QWidget(page_16);
        gridLayoutWidget_17->setObjectName(QString::fromUtf8("gridLayoutWidget_17"));
        gridLayoutWidget_17->setGeometry(QRect(0, 0, 1241, 631));
        grd16 = new QGridLayout(gridLayoutWidget_17);
        grd16->setSpacing(10);
        grd16->setObjectName(QString::fromUtf8("grd16"));
        grd16->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd16->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_16);
        page_17 = new QWidget();
        page_17->setObjectName(QString::fromUtf8("page_17"));
        gridLayoutWidget_18 = new QWidget(page_17);
        gridLayoutWidget_18->setObjectName(QString::fromUtf8("gridLayoutWidget_18"));
        gridLayoutWidget_18->setGeometry(QRect(0, 0, 1241, 631));
        grd17 = new QGridLayout(gridLayoutWidget_18);
        grd17->setSpacing(10);
        grd17->setObjectName(QString::fromUtf8("grd17"));
        grd17->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd17->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_17);
        page_18 = new QWidget();
        page_18->setObjectName(QString::fromUtf8("page_18"));
        gridLayoutWidget_19 = new QWidget(page_18);
        gridLayoutWidget_19->setObjectName(QString::fromUtf8("gridLayoutWidget_19"));
        gridLayoutWidget_19->setGeometry(QRect(0, 0, 1241, 631));
        grd18 = new QGridLayout(gridLayoutWidget_19);
        grd18->setSpacing(10);
        grd18->setObjectName(QString::fromUtf8("grd18"));
        grd18->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd18->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_18);
        page_19 = new QWidget();
        page_19->setObjectName(QString::fromUtf8("page_19"));
        gridLayoutWidget_20 = new QWidget(page_19);
        gridLayoutWidget_20->setObjectName(QString::fromUtf8("gridLayoutWidget_20"));
        gridLayoutWidget_20->setGeometry(QRect(0, 0, 1241, 631));
        grd19 = new QGridLayout(gridLayoutWidget_20);
        grd19->setSpacing(10);
        grd19->setObjectName(QString::fromUtf8("grd19"));
        grd19->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd19->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_19);
        page_20 = new QWidget();
        page_20->setObjectName(QString::fromUtf8("page_20"));
        gridLayoutWidget_21 = new QWidget(page_20);
        gridLayoutWidget_21->setObjectName(QString::fromUtf8("gridLayoutWidget_21"));
        gridLayoutWidget_21->setGeometry(QRect(0, 0, 1241, 631));
        grd20 = new QGridLayout(gridLayoutWidget_21);
        grd20->setSpacing(10);
        grd20->setObjectName(QString::fromUtf8("grd20"));
        grd20->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd20->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_20);
        page_21 = new QWidget();
        page_21->setObjectName(QString::fromUtf8("page_21"));
        gridLayoutWidget_22 = new QWidget(page_21);
        gridLayoutWidget_22->setObjectName(QString::fromUtf8("gridLayoutWidget_22"));
        gridLayoutWidget_22->setGeometry(QRect(0, 0, 1241, 631));
        grd21 = new QGridLayout(gridLayoutWidget_22);
        grd21->setSpacing(10);
        grd21->setObjectName(QString::fromUtf8("grd21"));
        grd21->setSizeConstraint(QLayout::SetDefaultConstraint);
        grd21->setContentsMargins(10, 0, 10, 0);
        dvdtek->addWidget(page_21);
        lbl_db_status = new QLabel(centralwidget);
        lbl_db_status->setObjectName(QString::fromUtf8("lbl_db_status"));
        lbl_db_status->setGeometry(QRect(830, 640, 141, 16));
        lbl_db_status->setTextFormat(Qt::PlainText);
        grp_rechercheType = new QGroupBox(centralwidget);
        grp_rechercheType->setObjectName(QString::fromUtf8("grp_rechercheType"));
        grp_rechercheType->setGeometry(QRect(300, 690, 211, 51));
        rdb_rechLoc = new QRadioButton(grp_rechercheType);
        rdb_rechLoc->setObjectName(QString::fromUtf8("rdb_rechLoc"));
        rdb_rechLoc->setGeometry(QRect(10, 20, 82, 17));
        rdb_rechDist = new QRadioButton(grp_rechercheType);
        rdb_rechDist->setObjectName(QString::fromUtf8("rdb_rechDist"));
        rdb_rechDist->setGeometry(QRect(100, 20, 82, 17));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(830, 680, 75, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1368, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_rechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        btn_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btn_option->setText(QCoreApplication::translate("MainWindow", "OPTION", nullptr));
        ln_titre->setText(QCoreApplication::translate("MainWindow", "rambo", nullptr));
        lbl_titre->setText(QCoreApplication::translate("MainWindow", "Titre", nullptr));
        lbl__Acteur->setText(QCoreApplication::translate("MainWindow", "Acteur", nullptr));
        lbl_date->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        cb_genre->setItemText(0, QCoreApplication::translate("MainWindow", "Com\303\251die", nullptr));
        cb_genre->setItemText(1, QCoreApplication::translate("MainWindow", "Trhiller", nullptr));
        cb_genre->setItemText(2, QCoreApplication::translate("MainWindow", "Horreur", nullptr));
        cb_genre->setItemText(3, QCoreApplication::translate("MainWindow", "Fiction", nullptr));
        cb_genre->setItemText(4, QCoreApplication::translate("MainWindow", "Romantique", nullptr));

        lbl_date_2->setText(QCoreApplication::translate("MainWindow", "Genre", nullptr));
        btn_previous->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        btn_next->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        lbl_db_status->setText(QCoreApplication::translate("MainWindow", "Database non connect\303\251e", nullptr));
        grp_rechercheType->setTitle(QCoreApplication::translate("MainWindow", "Type de recherche", nullptr));
        rdb_rechLoc->setText(QCoreApplication::translate("MainWindow", "Locale", nullptr));
        rdb_rechDist->setText(QCoreApplication::translate("MainWindow", "Locale +web", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
