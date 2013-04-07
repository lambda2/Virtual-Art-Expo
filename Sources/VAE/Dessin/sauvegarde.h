#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QtXml>
#include <QtGui>
#include "mur.h"
#include "vuehaut.h"
#include "grille.h"

class VueHaut;

class Sauvegarde
{

    public:
        Sauvegarde(VueHaut *s);
        bool Sauvegarder(QString fichier);
        bool Charger(QString fichier);

    private:
        QDomDocument *doc;
        VueHaut *maSalle;
};

#endif // SAUVEGARDE_H
