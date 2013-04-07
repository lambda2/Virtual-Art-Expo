#ifndef COURBE_H
#define COURBE_H

#include <QtGui>
#include <QGraphicsPathItem>
#include <mur.h>

class Mur;

class Courbe : public QGraphicsPathItem
{
public:
    explicit Courbe();
    Courbe(const QPainterPath &path);
    Courbe(const Courbe &courbe);
    QPointF getDebut();
    QPointF getPointUn();
    QPointF getPointDeux();
    QPointF getFin();
    void setDebut(QPointF point);
    void setPointUn(QPointF point);
    void setPointDeux(QPointF point);
    void setFin(QPointF point);
    Courbe& operator =(const Courbe& autreCourbe);
    void bougerLesPoints(qreal dx, qreal dy);



signals:
    
public slots:
    
private:
    QPointF debut;
    QPointF pointUn;
    QPointF pointDeux;
    QPointF fin;
};

#endif // COURBE_H
