#ifndef QGRAPHICSSURELEVATIONITEM_H
#define QGRAPHICSSURELEVATIONITEM_H

#include <QGraphicsPolygonItem>
#include "surelevation.h"
#include "qpoint3d.h"

class Surelevation;

class QGraphicsSurelevationItem : public QGraphicsPolygonItem
{

public:
    explicit QGraphicsSurelevationItem(Surelevation *elev = 0);
    Surelevation* getSurelevation();
    void setSurelevation(Surelevation *surelev);
    void setHauteur(qreal hauteur);
    ~QGraphicsSurelevationItem();

private:
    Surelevation *assoc;
    
signals:
    
public slots:
    
};

#endif // QGRAPHICSSURELEVATIONITEM_H
