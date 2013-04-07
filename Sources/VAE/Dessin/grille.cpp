#include "grille.h"

Grille::Grille()
{
    pas=calculerRapport(1.00);
    magnetisme=true;
    penGrille = new QPen(QColor(200,200,200,100), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
}

void Grille::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QDesktopWidget deskt;
    QRect taille = deskt.geometry();

    painter->setPen(*penGrille);
    for(int i=0;i<taille.width();i+=pas){
        painter->drawLine(0,i,taille.width(),i);
    }
    for(int i=0;i<taille.height();i+=pas){
        painter->drawLine(i,0,i,taille.height());
    }
}

QRectF Grille::boundingRect() const{
QRectF rect=QRectF();
return rect;
}

void Grille::setPas(double pas){
    this->pas = calculerRapport(pas);
}

int Grille::getPas(){
    return pas;
}

bool Grille::getMagnetisme(){
    return magnetisme;
}

void Grille::setMagnetisme(bool magn){
    magnetisme=magn;
}

int Grille::calculerRapport(double m){
    double conv = m*(100/2);
    // 1,96m = 100px
    return int(conv);
}
