#ifndef QPOINT3D_H
#define QPOINT3D_H

#include <QtGui>

class QPoint3D : public QObject
{
    Q_OBJECT

private:
    qreal x;
    qreal y;
    qreal z;
    QPoint3D ();

public:
    explicit QPoint3D(QObject *parent = 0);

    QPoint3D ( const QPoint3D & point );
    QPoint3D ( qreal x, qreal y, qreal z );
    bool	isNull () const;
    void	setX ( qreal x );
    void	setY ( qreal y );
    void    setZ ( qreal z );
    qreal	getx () const;
    qreal	gety () const;
    qreal	getz () const;
    bool	operator== ( const QPoint3D & p1);
    QPointF toQPoint();
    void moveTo(QLineF trans);
    void setPos(QPointF point, qreal z = 1);


    
signals:
    
public slots:
    
};

#endif // QPOINT3D_H
