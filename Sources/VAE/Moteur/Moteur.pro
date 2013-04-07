SOURCES += \
    main.cpp \
    gestionnaireentree.cpp \
    loader.cpp \
    CollisionTools.cpp \
    myraycasting.cpp

HEADERS += \
    gestionnaireentree.h \
    loader.h \
    CollisionTools.h \
    myraycasting.h

unix:LIBS += -lOgreMain \
             -lOIS

INCLUDEPATH += . /usr/include/OGRE/

DEPENDPATH += .

CONFIG += console

QT       += core gui\
        xml\
