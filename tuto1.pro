QT       += core gui sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = dvd.ico
SOURCES += \
    C_censure.cpp \
    C_details.cpp \
    C_downloadmanager.cpp \
    C_minifilm.cpp \
    C_mysqlmanager.cpp \
    c_bddsecu.cpp \
    c_biblio.cpp \
    c_dbconfig.cpp \
    c_detail_ajout.cpp \
    c_options.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    C_censure.h \
    C_details.h \
    C_downloadmanager.h \
    C_minifilm.h \
    C_mysqlmanager.h \
    c_bddsecu.h \
    c_biblio.h \
    c_dbconfig.h \
    c_detail_ajout.h \
    c_options.h \
    mainwindow.h

FORMS += \
    C_censure.ui \
    C_details.ui \
    C_minifilm.ui \
    c_detail_ajout.ui \
    c_options.ui \
    mainwindow.ui

TRANSLATIONS += \
    tuto1_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../tuto1/lib_img/censored.png \
    ../../tuto1/lib_img/dvdflixSearch.png \
    ../../tuto1/lib_img/home.png \
    ../../tuto1/lib_img/logo.png \
    ../../tuto1/lib_img/logodvdflix.png \
    ../../tuto1/lib_img/noPicture.png \
    ../../tuto1/lib_img/online.png \
    ../build-tuto1-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/dvdflix.ini \
    dvd.ico \
    dvdflix.ini \
    img_tempo/dummy.txt \
    lib_img/censored.png \
    lib_img/dummy.txt \
    lib_img/dvdflixSearch.png \
    lib_img/home.png \
    lib_img/logo.png \
    lib_img/logodvdflix.png \
    lib_img/noPicture.png \
    lib_img/online.png \
    model-wsBCTe.qmodel \
    movie0.json
