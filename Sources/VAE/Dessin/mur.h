#ifndef MUR_H
#define MUR_H

#include <QtGui>
#include <qmath.h>
#include "courbe.h"
#include "vueface.h"
#include "tableau.h"
#include "vuehaut.h"

class VueFace;
class VueHaut;
class Courbe;

class Mur : public QGraphicsLineItem
{
public:
    explicit Mur();
    Mur(const QLineF &ligne, VueHaut *haut);
    Mur(Mur &autreMur);
    bool debutEstProche(const Mur &mur, QPointF *point);
    bool finEstProche(const Mur &mur, QPointF *point);
    bool debutEstProche(Courbe &courbe, QPointF *point);
    bool finEstProche(Courbe &courbe, QPointF *point);
    void setMobile(bool mobile);
    void setAffichable(bool affichable);
    bool isMobile();
    bool isAffichable();
    VueFace* getVueFace();
    VueHaut* getVueHaut();
    Mur& operator =(Mur& autreMur);
    QList<Tableau *> listeDesTableaux();
    QList<Tableau *> listeDesTableauxDeux();
    QList<QGraphicsLineItem *> calculerRepresentations();
    void changerVueFace(bool premiere);
    VueFace* getPremiereVueFace();
    VueFace* getDeuxiemeVueFace();

private:

    int distA;
    bool mobile;
    bool affichable;
    VueFace *maVueDeFace;
    VueFace *maDeuxiemeVueDeFace;
    VueFace *vueSelect;
    VueHaut *maVueDeHaut;


signals:

public slots:

};

#endif // MUR_H
