#-------------------------------------------------
#
# Project created by QtCreator 2011-12-20T22:11:39
#
#-------------------------------------------------

QT       += core gui\
        xml\
        svg\
        opengl

TARGET = Dessin
TEMPLATE = app


SOURCES += main.cpp\
        fenetre.cpp \
    vuehaut.cpp \
    mur.cpp \
    grille.cpp \
    sauvegarde.cpp \
    qpoint3d.cpp \
    courbe.cpp \
    surelevation.cpp \
    qgraphicssurelevationitem.cpp \
    objet3d.cpp \
    vueface.cpp \
    paramsalledial.cpp \
    tableau.cpp \
    daiconmachina.cpp \
    listeimages.cpp \
    qnotification.cpp \
    echelle.cpp \
    accueil.cpp \
    projet.cpp \
    nouveauprojet.cpp

HEADERS  += fenetre.h \
    vuehaut.h \
    mur.h \
    grille.h \
    sauvegarde.h \
    qpoint3d.h \
    courbe.h \
    surelevation.h \
    qgraphicssurelevationitem.h \
    objet3d.h \
    vueface.h \
    paramsalledial.h \
    tableau.h \
    daiconmachina.h \
    listeimages.h \
    qnotification.h \
    echelle.h \
    accueil.h \
    projet.h \
    nouveauprojet.h

FORMS    += \
    form.ui \
    paramsalledial.ui \
    accueil.ui

OTHER_FILES += \
    style.qcss

RESOURCES += \
    ressources.qrc


