#include "objet3d.h"

Objet3D::Objet3D(TypeObjet type)
{
    typeObjet = type;



    pen = QPen(QBrush(QColor(20,20,20)),3);

}

Objet3D::Objet3D(Objet3D &autreObjet){
    this->typeObjet = autreObjet.typeObjet;
    pen = autreObjet.pen;
    qDebug() << "pos objet = " << this->pos() << ", pos autre = " << autreObjet.pos();
    this->setPos(autreObjet.scenePos());
}

void Objet3D::setType(TypeObjet type){
    typeObjet = type;
}

Objet3D::TypeObjet Objet3D::getType(){
    return typeObjet;
}

void Objet3D::setPen(QPen pen){
    this->pen = pen;
    update();
}

void Objet3D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){



    QRectF rect;


    painter->setPen(pen);

    switch(typeObjet){

    case Colonne:


        rect.setCoords(0,0,50*0.4,50*0.4);
        painter->drawEllipse(rect);

        break;

    default:
        ;
    }



}

QRectF Objet3D::getRect(){
    return this->boundingRect();
}

QRectF Objet3D::boundingRect() const{

    QRectF rect;

    switch(typeObjet){


    case Colonne:


        rect.setCoords(0,0,50,50);

        break;


    default:
        ;
    }

    return rect;
}
