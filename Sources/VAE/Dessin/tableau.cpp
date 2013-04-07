#include "tableau.h"

Tableau::Tableau() {

}

Tableau::Tableau(const Tableau &other) {

}

Tableau::Tableau(const QString fich) {
    fichier=fich;
    QPixmap *img = new QPixmap(fichier);
    this->setPixmap(*img);
    x=0;
    y=0;
}

QString Tableau::getFichier() {
    return fichier;
}

