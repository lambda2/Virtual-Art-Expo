#include "qpoint3d.h"

QPoint3D::QPoint3D(QObject *parent) :
    QObject(parent)
    {}

    QPoint3D::QPoint3D():
        x(0),
        y(0),
        z(0)
    {}

    QPoint3D::QPoint3D(const QPoint3D &point):
        x(point.x),
        y(point.y),
        z(point.z)
    {}

    QPoint3D::QPoint3D(qreal xa, qreal ya, qreal za):
        x(xa),
        y(ya),
        z(za)
    {}

    bool QPoint3D::isNull() const
    {return (x==0 && y==0 && z==0);}

    void QPoint3D::setX(qreal xa)
    {x=xa;}

    void QPoint3D::setY(qreal ya)
    {y=ya;}

    void QPoint3D::setZ(qreal za)
    {z=za;}

    qreal QPoint3D::getx() const
    {return x;}

    qreal QPoint3D::gety() const
    {return y;}

    qreal QPoint3D::getz() const
    {return z;}

    bool QPoint3D::operator== ( const QPoint3D & p1)
    {return (p1.getx()==x && p1.gety()==y && p1.getz()==z);}

    QPointF QPoint3D::toQPoint(){
        QPointF point;
        point.setX(this->x);
        point.setY(this->y);
        return point;
    }

    void QPoint3D::setPos(QPointF point, qreal z) {
        this->x = point.x();
        this->y = point.y();
        this->z = z;
    }

    void QPoint3D::moveTo(QLineF trans) {
        this->setPos(this->toQPoint() + QPointF(trans.dx(), trans.dy()), this->z);
    }
