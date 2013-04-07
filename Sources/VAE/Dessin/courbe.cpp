#include "courbe.h"

Courbe::Courbe():QGraphicsPathItem()
{
    debut = QPointF();
    pointUn = QPointF();
    pointDeux = QPointF();
    fin = QPointF();

}

Courbe::Courbe(const QPainterPath &path)
{
    setPath(path);
}

Courbe::Courbe(const Courbe &autreCourbe) {
    this->debut = autreCourbe.debut;
    this->pointUn = autreCourbe.pointUn;
    this->pointDeux = autreCourbe.pointDeux;
    this->fin = autreCourbe.fin;
    this->setPath(autreCourbe.path());

}

QPointF Courbe::getDebut()
{return debut;}

QPointF Courbe::getPointUn()
{return pointUn;}

QPointF Courbe::getPointDeux()
{return pointDeux;}

QPointF Courbe::getFin()
{return fin;}

void Courbe::setDebut(QPointF point)
{debut = point;}

void Courbe::setPointUn(QPointF point)
{pointUn = point;}

void Courbe::setPointDeux(QPointF point)
{pointDeux = point;}

void Courbe::setFin(QPointF point)
{fin = point;}

Courbe& Courbe::operator =(const Courbe& autreCourbe){
    if(this != &autreCourbe){
        this->debut = autreCourbe.debut;
        this->pointUn = autreCourbe.pointUn;
        this->pointDeux = autreCourbe.pointDeux;
        this->fin = autreCourbe.fin;
        this->setPath(autreCourbe.path());
    }
    return *this;
}

void Courbe::bougerLesPoints(qreal dx, qreal dy) {
    debut.setX(debut.x() + dx);
    debut.setY(debut.y() + dy);
    pointUn.setX(pointUn.x() + dx);
    pointUn.setY(pointUn.y() + dy);
    pointDeux.setX(pointDeux.x() + dx);
    pointDeux.setY(pointDeux.y() + dy);
    fin.setX(fin.x() + dx);
    fin.setY(fin.y() + dy);
}


