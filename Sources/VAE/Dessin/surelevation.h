#ifndef SURELEVATION_H
#define SURELEVATION_H

#include <QtGui>
#include <qpoint3d.h>
#include <qgraphicssurelevationitem.h>

/**
  * Classe représantant une surélévation
  */
class QGraphicsSurelevationItem;

class Surelevation
{
public:
    Surelevation(); // Constructeur par défaut
    Surelevation(QList<QPoint3D *> _points); // Surcharge
    Surelevation(const Surelevation &other);
    // Accesseurs de la liste des points

    QList<QPoint3D *> *getListeDesPoints();
    void setListeDesPoints(QList<QPoint3D *> liste);

    QGraphicsSurelevationItem* getGraphicsSurelevation();
    void majSurelevation();
    void moveTo(QLineF trans);

    void debug();


public slots:

    void ajouterUnPoint(QPoint3D *point);
    void ajouterUnPoint(QPointF *point, qreal _hauteur=1);
    void ajouterUnPoint(qreal x, qreal y, qreal z=1);


signals:


private:
//    QImage genererRelief();
    QColor genererRelief();

    QList<QPoint3D *> points;
    QGraphicsSurelevationItem *maSurelevation;
};

#endif // SURELEVATION_H
