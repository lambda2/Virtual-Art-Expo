#include "echelle.h"

Echelle::Echelle(QWidget *parent) :
    QWidget(parent)
{
    this->setMaximumHeight(50);
    this->setMinimumHeight(50);
    ech = 50;
    penRouge = new QPen(QColor(200,0,0,200));
    penNoir = new QPen(QColor(0,0,0,200));
    penPolice = new QPen(QColor(20,20,20));
    fontPolice = new QFont("arial");
    this->update();
}

void Echelle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);

    bool alt = false;
    for(int i=10; i<=1*ech+10; i++){
        if(i%10 == 0){
            if(alt){
            painter.setPen(*penRouge);
            alt = false;
            }
            else {
                painter.setPen(*penNoir);
                alt = true;
            }
        }
        painter.drawLine(i,30,i,45);
    }

    painter.setPen(*penPolice);
    painter.drawLine(10,18,10,26);
    painter.drawLine(10+1*ech,18,10+1*ech,26);
    painter.drawLine(10,22,10+1*ech,22);
    painter.drawText(QRectF(10,0,1*ech*10,18)," Un mètre ");

}

void Echelle::majEchelle(qreal coef) {
    ech = coef;
    update();
}

qreal Echelle::getEchelle(){
    return ech;
}
