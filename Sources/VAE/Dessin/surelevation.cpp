#include "surelevation.h"

Surelevation::Surelevation()
{
    maSurelevation = new QGraphicsSurelevationItem(this);
    points.clear();
}

Surelevation::Surelevation(const Surelevation &other) {
    foreach (QPoint3D *pt, other.points) {
        QPoint3D *point;
        point = new QPoint3D(*pt);
        this->points.append(point);
    }
    qDebug() << "nouvelle surelevation";
    maSurelevation = new QGraphicsSurelevationItem(this);
    majSurelevation();

}

Surelevation::Surelevation(QList<QPoint3D *> _points) {
    points = _points;
    maSurelevation = new QGraphicsSurelevationItem(this);
    majSurelevation();
}

QList<QPoint3D *>* Surelevation::getListeDesPoints() {
    return &points;
}

void Surelevation::setListeDesPoints(QList<QPoint3D *> liste) {
    points = liste;
}

QGraphicsSurelevationItem* Surelevation::getGraphicsSurelevation() {
    if(!points.isEmpty() && maSurelevation!=NULL) {
        if(points.count()>=3) {
            QPolygonF forme;
            foreach (QPoint3D *pt, points) {
                forme.append(pt->toQPoint());
            }

            maSurelevation->setPolygon(forme);
            maSurelevation->setSurelevation(this);
            maSurelevation->setBrush(QBrush(this->genererRelief()));
//            maSurelevation->setBrush(QBrush(QColor(0,0,0,50)));
        }
        else
            qDebug() << "ERREUR : la surélévation ne compte pas 3 points (en compte " << points.count() << ")";
    }
    else
        qDebug() << "ERREUR : la surélévation est vide ou non instanciée";

    return maSurelevation;
}

void Surelevation::majSurelevation() {
    if(!points.isEmpty() && maSurelevation!=NULL) {
        if(points.count()>=3) {
            QPolygonF forme;
            foreach (QPoint3D *pt, points) {
                forme.append(pt->toQPoint());
            }
            maSurelevation->setPolygon(forme);
            maSurelevation->setBrush(QBrush(this->genererRelief()));
            qDebug() << " --> Application de la brush";
        }
    }
}

void Surelevation::ajouterUnPoint(QPoint3D *point) {
    if(point->getz() >= 0) {
        points.append(point);
    }
    else
        qDebug() << "ERREUR : le point ajouté a une hauteur négative";
}

void Surelevation::ajouterUnPoint(QPointF *point, qreal _hauteur) {
    if(_hauteur >= 0) {
        QPoint3D* pt = new QPoint3D(point->x(),point->y(), _hauteur);
        points.append(pt);
    }
    else
        qDebug() << "ERREUR : le point ajouté a une hauteur négative";

}

void Surelevation::ajouterUnPoint(qreal x, qreal y, qreal z) {
    if(z >= 0) {
        QPoint3D* pt = new QPoint3D(x,y,z);
        points.append(pt);
    }
    else
        qDebug() << "ERREUR : le point ajouté a une hauteur négative";
}

void Surelevation::debug() {
    qDebug() << "-------- Surelevation Ã  l'adresse : " << this << "------------";
    qDebug() << "Nombre de points : " << points.count();
    qDebug() << "Liste des points :";
    int i=0;
    foreach (QPoint3D *pt, points) {
        qDebug() << "Point nÂ°" << i << " : [" << pt->getx() << "][" << pt->gety() << "][" << pt->getz() << "]";
    }
}

//QImage Surelevation::genererRelief() {
//    QPolygonF forme;
//    foreach (QPoint3D *pt, points) {
//        forme.append(pt->toQPoint());
//    }
//    QImage image(int(forme.boundingRect().width()),
//                 int(forme.boundingRect().height()),
//                 QImage::Format_ARGB32);


//    return image;
//}

QColor Surelevation::genererRelief() {
    qreal hauteur = points.last()->getz();
    qDebug() << "   ---> relief généré avec une hauteur de : " << hauteur;
    qreal valeur = 255-((hauteur * 255) /3);
    QColor colo;
    colo.setRgb(valeur, valeur, valeur);
    return colo;
}

void Surelevation::moveTo(QLineF trans) {
    foreach (QPoint3D *item, *this->getListeDesPoints()) {
        item->moveTo(trans);
    }
    maSurelevation->setBrush(QBrush(this->genererRelief()));
}
