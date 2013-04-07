#include "mur.h"

Mur::Mur() : QGraphicsLineItem()
{
//    distA = 10;
//    mobile=false;
//    affichable=true;
//    this->setAffichable(true);
//    this->setMobile(false);
    throw "Mur instancié sans paramàtres !";
}

Mur::Mur(const QLineF &ligne, VueHaut *haut) : QGraphicsLineItem()
{
    this->setLine(ligne);
    distA = 10;
    mobile=false;
    affichable=true;
    if(haut != NULL)
        maVueDeHaut = haut;
    else
        throw "pointeur NULL sur vue de haut lors de l'instanciation d'un mur";
    maVueDeFace = new VueFace(this);
    maDeuxiemeVueDeFace = new VueFace(this);
    vueSelect = maVueDeFace;
}

Mur::Mur(Mur &autreMur) {
    this->distA = autreMur.distA;
    this->mobile = autreMur.mobile;
    this->affichable = autreMur.affichable;
    this->setLine(autreMur.line());
    this->maVueDeFace = autreMur.getPremiereVueFace();
    this->maDeuxiemeVueDeFace = autreMur.getDeuxiemeVueFace();
    this->vueSelect=autreMur.getVueFace();
    this->maVueDeHaut = autreMur.getVueHaut();

}

bool Mur::debutEstProche(const Mur &mur, QPointF *point){
    if((abs(this->line().x1()-mur.line().x1()) <= 10)
            && (abs(this->line().y1()-mur.line().y1()) <= 10))
    {
        *point = mur.line().p1();
        return true;
    }
    else if((abs(this->line().x1()-mur.line().x2()) <= 10)
            && (abs(this->line().y1()-mur.line().y2()) <= 10))
    {
        *point = mur.line().p2();
        return true;
    }
    else {
        return false;
    }
}

bool Mur::finEstProche(const Mur &mur, QPointF *point){
    if((abs(this->line().x2()-mur.line().x1()) <= 10)
            && (abs(this->line().y2()-mur.line().y1()) <= 10))
    {
        *point = mur.line().p1();
        return true;
    }
    else if((abs(this->line().x2()-mur.line().x2()) <= 10)
            && (abs(this->line().y2()-mur.line().y2()) <= 10))
    {
        *point = mur.line().p2();
        return true;
    }
    else {
        return false;
    }
}

bool Mur::finEstProche(Courbe &courbe, QPointF *point){
    if((abs(this->line().x2()-courbe.getDebut().x()) <= 10)
            && (abs(this->line().y2()-courbe.getDebut().y()) <= 10))
    {
        *point = courbe.getDebut();
        return true;
    }
    else if((abs(this->line().x2()-courbe.getFin().x()) <= 10)
            && (abs(this->line().y2()-courbe.getFin().y()) <= 10))
    {
        *point = courbe.getFin();
        return true;
    }
    else {
        return false;

    }
}

bool Mur::debutEstProche(Courbe &courbe, QPointF *point){
    if((abs(this->line().x1()-courbe.getDebut().x()) <= 10)
            && (abs(this->line().y1()-courbe.getDebut().y()) <= 10))
    {
        *point = courbe.getDebut();
        return true;
    }
    else if((abs(this->line().x1()-courbe.getFin().x()) <= 10)
            && (abs(this->line().y1()-courbe.getFin().y()) <= 10))
    {
        *point = courbe.getFin();
        return true;
    }
    else {
        return false;
    }

}

void Mur::setAffichable(bool affichable){
    this->affichable = affichable;
}

void Mur::setMobile(bool mobile){
    this->mobile = mobile;
}

bool Mur::isMobile(){
    return mobile;
}

bool Mur::isAffichable(){
    return affichable;
}

Mur& Mur::operator =(Mur& autreMur){
    if(this != &autreMur){
        this->distA = autreMur.distA;
        this->mobile = autreMur.mobile;
        this->affichable = autreMur.affichable;
        this->setLine(autreMur.line());
        this->maVueDeFace = autreMur.getPremiereVueFace();
        this->maDeuxiemeVueDeFace = autreMur.getDeuxiemeVueFace();
        this->maVueDeHaut = autreMur.getVueHaut();
    }
    return *this;
}

VueFace* Mur::getVueFace() {
    return vueSelect;
}

VueHaut* Mur::getVueHaut() {
    return maVueDeHaut;
}

QList<Tableau *> Mur::listeDesTableaux(){
    return maVueDeFace->listeDesTableaux();
}

QList<Tableau *> Mur::listeDesTableauxDeux(){
    return maDeuxiemeVueDeFace->listeDesTableaux();
}

QList<QGraphicsLineItem *> Mur::calculerRepresentations(){
    QList<QGraphicsLineItem *> lst;
//    lst.clear();
//    foreach (Tableau *tab, listeDesTableaux()) {
//        QLineF base;
//        base.setP1(this->line().p1());
//        base.setP2(QPointF(this->line().p1().x()+tab->pixmap().width(),this->line().p2().y()));
//        QGraphicsLineItem *line = new QGraphicsLineItem(base);
//        qDebug() << "Représentation de tableau calculée ! pos = " << base;
//        line->setPen(QPen(QBrush(QColor(0,255,0)),3));
//        lst.append(line);
//    }
    return lst;
}

void Mur::changerVueFace(bool premiere){
    if(premiere)
        vueSelect=maVueDeFace;
    else
        vueSelect=maDeuxiemeVueDeFace;
    qDebug()<<premiere;
    qDebug()<<"premiere : " << maVueDeFace;
    qDebug()<<"deuxieme : " << maDeuxiemeVueDeFace;
    qDebug()<<"courrante : " << vueSelect;
}

VueFace* Mur::getPremiereVueFace(){
    return maVueDeFace;
}

VueFace* Mur::getDeuxiemeVueFace() {
    return maDeuxiemeVueDeFace;
}
