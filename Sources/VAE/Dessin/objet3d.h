#ifndef OBJET3D_H
#define OBJET3D_H

#include <QtGui>
#include <QGraphicsItem>

class Objet3D : public QGraphicsItem
{

public:

    enum TypeObjet {
        Colonne
    };


    explicit Objet3D(TypeObjet type);
    Objet3D(Objet3D &autreObjet);
    TypeObjet typeObjet;
    QPen pen;

    
signals:
    
public slots:

    TypeObjet getType();
    void setType(TypeObjet type);
    void setPen(QPen pen);
    QRectF getRect();


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    
};

#endif // OBJET3D_H
