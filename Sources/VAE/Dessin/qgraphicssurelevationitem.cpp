#include "qgraphicssurelevationitem.h"

QGraphicsSurelevationItem::QGraphicsSurelevationItem(Surelevation *elev) :
    QGraphicsPolygonItem()
{
    assoc = elev;
    qDebug() << "SURELEVATIOOOOOON (elev = " << elev << ")" ;
}

Surelevation* QGraphicsSurelevationItem::getSurelevation() {
    return assoc;
}

void QGraphicsSurelevationItem::setSurelevation(Surelevation *surelev) {
    assoc = surelev;
}

void QGraphicsSurelevationItem::setHauteur(qreal hauteur) {
    foreach (QPoint3D *pt, *assoc->getListeDesPoints()) {
        pt->setZ(hauteur);
        qDebug() << "-> changement de hauteur point surelevation : " << hauteur;
    }
    assoc->majSurelevation();
}

QGraphicsSurelevationItem::~QGraphicsSurelevationItem() {
    if(assoc != NULL){
        delete assoc;
    }
}
