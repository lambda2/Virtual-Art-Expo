#include "vueface.h"

VueFace::VueFace(QObject *parent) :
    QGraphicsScene(parent)
{
    vueDeHaut = NULL;
    this->initialiser();
}

VueFace::VueFace(VueHaut *maVueDeHaut) {
    vueDeHaut = maVueDeHaut;
    this->initialiser();
}

VueFace::VueFace(Mur *monMur) {
    this->monMur = monMur;
    initialiser();
    this->setMurCourant(monMur);
}

void VueFace::initialiser() {
    brush = new QBrush(QColor(200,200,200));
    mesure = new QGraphicsTextItem;
    mesureHauteur = new QGraphicsTextItem;
    mesureLargeurTab = new QGraphicsTextItem;
    mesureHauteurTab = new QGraphicsTextItem;
    this->setBackgroundBrush(*brush);
    coef=7;
    decalage=20;
    ratio=0;
    haut=true;
    bas=true;
    gauche=true;
    droite=true;
    coinHG=new QGraphicsRectItem;
    coinHD=new QGraphicsRectItem;
    coinBD=new QGraphicsRectItem;
    coinBG=new QGraphicsRectItem;
    translation = new QLineF(0,0,0,0);
    widthRedimentionnement=0;
    monMode=VueFace::Select;
    coin=VueFace::Base;
    penSelection = new QPen(QColor(20,90,20,0), 10, Qt::DotLine, Qt::RoundCap, Qt::MiterJoin);
    graphiqueSelection.setPen(*penSelection);
    graphiqueSelection.setBrush(QBrush(QColor(80,80,20,40)));
    menuTab = new QMenu;
    supprTab = new QAction(QIcon(":/res/supprimer.png"), tr("Supprimer"), this);
    supprTab->setStatusTip(tr("Supprimer"));
    penRedimentionnement = new QPen(QColor(0,0,0,0), 3);
    graphiqueRedimentionnement = new QGraphicsRectItem;
    graphiqueRedimentionnement->setPen(*penRedimentionnement);
    graphiqueRedimentionnement->setBrush(QBrush(QColor(80,80,20,40)));

    connect(supprTab, SIGNAL(triggered()), this , SLOT(supprimerTableauxSelect()));
    connect(this->monMur->getVueHaut()->getFenetre()->spinHTab, SIGNAL(valueChanged(double)), this, SLOT(setHeight(double)));
    connect(this->monMur->getVueHaut()->getFenetre()->spinLTab, SIGNAL(valueChanged(double)), this, SLOT(setWidth(double)));
    connect(this->monMur->getVueHaut()->getFenetre()->spinHDistTab, SIGNAL(valueChanged(double)), this, SLOT(setHauteur(double)));
    connect(this->monMur->getVueHaut()->getFenetre()->spinLDistTab, SIGNAL(valueChanged(double)), this, SLOT(setLargeur(double)));

    connect(this, SIGNAL(tableauModifie()), this->monMur->getVueHaut(), SLOT(majTableaux()));


    menuTab->addAction(supprTab);
    //maNot = new QNotification();
    wa=0;
    ha=0;
    tableauSelectionne=new Tableau();
}

void VueFace::setMurCourant(Mur *mur) {
    if(mur != NULL){
        monMur = mur;
        vueDeHaut = monMur->getVueHaut();
        QRect rect;
        // //qDebug() << "MUR ENVOYE = @" << mur <<", & longueur = " << mur->line().length();
        rect.setWidth(mur->line().length()*coef);
        double hauteur=vueDeHaut->getHauteurSalle()*100;
        rect.setHeight(hauteur*coef/2);
        graphiqueMur.setPos(decalage,decalage);
        graphiqueMur.setRect(rect);
        graphiqueMur.setBrush(QBrush(QColor(230,230,230,255)));
        this->addItem(&graphiqueMur);

        mesure->setPlainText(QString(QString::number(monMur->line().length()/50,'g',3)+" m"));
        QPointF coord((rect.width()/2)+decalage,(rect.height())+decalage);
        mesure->setPos(coord);
        this->addItem(mesure);

        mesureHauteur->setPlainText(QString(QString::number(hauteur/100,'g',3)+" m"));
        QPointF coord2((rect.width())+decalage,(rect.height()/2)+decalage);
        mesureHauteur->setPos(coord2);
        this->addItem(mesureHauteur);
    }
    else {
        throw "mur == NULL";
    }
}

void VueFace::enleverMurCourant() {
    if(this->items().contains(&graphiqueMur)){
        removeItem(&graphiqueMur);
    }
    if(monMur != NULL) {
        monMur = NULL;
    }
}

void VueFace::ajouterTableau(QString fichier, QPointF pos) {

    double murHeight = ((vueDeHaut->getHauteurSalle()*100)*coef/2)+decalage;
    double murWidth = (monMur->line().length()*coef)+decalage;
    Tableau *tableau = new Tableau(fichier);
    tableau->setPixmap(QPixmap(tableau->getFichier()).scaledToHeight(graphiqueMur.rect().height()/5));

    if(pos.x()+tableau->pixmap().width()>murWidth)
    {
        if(pos.y()+tableau->pixmap().height()>murHeight)
            tableau->setPos(murWidth-tableau->pixmap().width(),murHeight-tableau->pixmap().height());
        else if(pos.y()<decalage)
            tableau->setPos(murWidth-tableau->pixmap().width(),decalage);
        else
            tableau->setPos(murWidth-tableau->pixmap().width(),pos.y());
    }
    else if(pos.y()+tableau->pixmap().height()>murHeight)
    {
        if(pos.x()+tableau->pixmap().width()>murWidth)
            tableau->setPos(murWidth-tableau->pixmap().width(),murHeight-tableau->pixmap().height());
        else if(pos.x()<decalage)
            tableau->setPos(decalage,murHeight-tableau->pixmap().height());
        else
            tableau->setPos(pos.x(),murHeight-tableau->pixmap().height());
    }
    else if(pos.x()<decalage)
    {
        if(pos.y()+tableau->pixmap().height()>murHeight)
            tableau->setPos(decalage,murHeight-tableau->pixmap().height());
        else if(pos.y()<decalage)
            tableau->setPos(decalage,decalage);
        else
            tableau->setPos(decalage,pos.y());
    }
    else if(pos.y()<decalage)
    {
        if(pos.x()+tableau->pixmap().width()>murWidth)
            tableau->setPos(murWidth-tableau->pixmap().width(),decalage);
        else if(pos.x()<decalage)
            tableau->setPos(decalage,decalage);
        else
            tableau->setPos(pos.x(),decalage);
    }
    else
        tableau->setPos(pos);

    this->addItem(tableau);
    emit tableauModifie();

}

void VueFace::supprimerTableauxSelect() {
    supprimerMesure();
    supprimerCoins();
    if(!objets.isEmpty()){
        foreach (Tableau *item, listeDesTableauxDans(objets)) {
            this->removeItem(item);
        }
    }
    objets.clear();
    setMode(VueFace::Select);
    emit tableauModifie();

}

void VueFace::ajouterMesure(Tableau *item) {
    if(item != NULL){
        supprimerMesure();
        Tableau *tableauSelect = item;
        mesureLargeurTab->setPlainText(QString(QString::number(tableauSelect->pixmap().width()/350.0,'g',3)+" m"));
        QPointF coord((tableauSelect->pos().x()+(tableauSelect->pos().x()+tableauSelect->pixmap().width()))/2,tableauSelect->pos().y()-decalage);
        mesureLargeurTab->setPos(coord);
        this->addItem(mesureLargeurTab);
        mesureHauteurTab->setPlainText(QString(QString::number(tableauSelect->pixmap().height()/350.0,'g',3)+" m"));
        QPointF coordh(tableauSelect->pos().x()-decalage*2,(tableauSelect->pos().y()+(tableauSelect->pos().y()+tableauSelect->pixmap().height()))/2);
        mesureHauteurTab->setPos(coordh);
        this->addItem(mesureHauteurTab);
    }
}

void VueFace::supprimerMesure() {
    if(this->items().contains(mesureLargeurTab))
        removeItem(mesureLargeurTab);
    if(this->items().contains(mesureHauteurTab))
        removeItem(mesureHauteurTab);
}

QList<Tableau *> VueFace::listeDesTableauxDans(QList<QGraphicsItem *> lst) {
    QList<Tableau *> liste;
    liste.clear();
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Tableau::Type)
            liste.append(qgraphicsitem_cast<Tableau *>(item));
    }
    return liste;
}

void VueFace::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

}

void VueFace::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton){
        translation->setP1(mouseEvent->scenePos());
        switch (monMode) {

        case Select:

            if(nombreDeTableauxDans(objets) != 0){

                if(nombreDeTableauxDans(objets) == 1){
                    ajouterMesure(listeDesTableauxDans(objets).first());
                    ajouterCoins(listeDesTableauxDans(objets).first());
                    unTableauEstSelectionne();
                    setMode(VueFace::TableauEnMouvement);
                }
                else if(nombreDeTableauxDans(objets)>1){
                    setMode(VueFace::TableauxEnMouvement);
                }

            }
            //qDebug()<<"objets aux clic : " << objets;
            // On récupàre le ou les tableaux présents dans la sélection
            objets = items(mouseEvent->scenePos());
            // //qDebug() << "Il y a " << listeDesTableauxDans(objets).count() << " tableau(x) sélectionné(s)";
            if(nombreDeTableauxDans(objets) != 0){
                if(nombreDeTableauxDans(objets) == 1){
                    Tableau *tableauSelect = qgraphicsitem_cast<Tableau *>(listeDesTableauxDans(objets).first());
                    ajouterMesure(tableauSelect);
                    ajouterCoins(tableauSelect);
                    unTableauEstSelectionne();
                    if(approxProches(mouseEvent->scenePos()).contains(QPointF(tableauSelect->scenePos().x()+tableauSelect->pixmap().width(),tableauSelect->scenePos().y()+tableauSelect->pixmap().height()))){
                        setCoin(VueFace::BD);
                        widthRedimentionnement=tableauSelect->pixmap().width();
                        zoneRedimentionnement.setTopLeft(tableauSelect->scenePos());
                        zoneRedimentionnement.setBottomRight(QPointF(tableauSelect->scenePos().x()+tableauSelect->pixmap().width(),tableauSelect->scenePos().y()+tableauSelect->pixmap().height()));
                        ratio=double(tableauSelect->pixmap().width())/double(tableauSelect->pixmap().height());
                        setMode(VueFace::redimensionnement);
                    }
                    else
                        setMode(VueFace::TableauEnMouvement);
                }
                else if(nombreDeTableauxDans(objets) > 1){
                    setMode(VueFace::TableauxEnMouvement);

                }

            }

            else {

                setMode(VueFace::SelectionEnCours);
                pointSelection = mouseEvent->scenePos();
            }

            peindre();
            break;
        case TableauSelectionne:
            if(nombreDeTableauxDans(objets)==1){
                Tableau *tableauSelect = qgraphicsitem_cast<Tableau *>(listeDesTableauxDans(objets).first());
                ajouterMesure(tableauSelect);
                setMode(VueFace::TableauEnMouvement);
            }
            break;
        case TableauxSelectionnes:
            if(nombreDeTableauxDans(objets)>1){
                // //qDebug() << "On essaye de bouger plusieurs tableaux ";
                setMode(VueFace::TableauxEnMouvement);
            }
            break;

        default:

            break;

        }
    }
    if (mouseEvent->button() == Qt::RightButton){

        // //qDebug() << "Clic droiiiit ! Hohoho !";

        if(nombreDeTableauxDans(objets) > 0){
            menuTab->exec(QPoint(mouseEvent->screenPos().x(),mouseEvent->screenPos().y()));
        }
    }
}

void VueFace::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    translation->setP2(mouseEvent->scenePos());
    switch (monMode) {

    case SelectionEnCours:
        peindre();
        zoneSelection.setTopLeft(pointSelection);
        zoneSelection.setBottomRight(mouseEvent->scenePos());


        if(zoneSelection.topLeft().y() > zoneSelection.bottomLeft().y())
        {
            QPointF topL= zoneSelection.topLeft();
            QPointF topR= zoneSelection.topRight();
            zoneSelection.setTopLeft(zoneSelection.bottomLeft());
            zoneSelection.setTopRight(zoneSelection.bottomRight());
            zoneSelection.setBottomLeft(topL);
            zoneSelection.setBottomRight(topR);
        }


        if(zoneSelection.topLeft().x() > zoneSelection.topRight().x())
        {
            QPointF leftT= zoneSelection.topLeft();
            QPointF leftB= zoneSelection.bottomLeft();
            zoneSelection.setTopLeft(zoneSelection.topRight());
            zoneSelection.setBottomLeft(zoneSelection.bottomRight());
            zoneSelection.setTopRight(leftT);
            zoneSelection.setBottomRight(leftB);
        }


        if(this->items().contains(&graphiqueSelection))
            removeItem(&graphiqueSelection);
        graphiqueSelection.setRect(zoneSelection);
        graphiqueSelection.setPen(*penSelection);
        this->addItem(&graphiqueSelection);
        objets.clear();
        objets = this->items(zoneSelection);
        //qDebug()<<"objets aux move (Selection) : " << objets <<endl;

        break;

    case TableauEnMouvement:

        if(nombreDeTableauxDans(objets)!=0){


            if(nombreDeTableauxDans(objets)==1){
                Tableau *tableauSelect = qgraphicsitem_cast<Tableau *>(listeDesTableauxDans(objets).first());

                ajouterMesure(tableauSelect);
                ajouterCoins(tableauSelect);

                double murHeight = ((vueDeHaut->getHauteurSalle()*100)*coef/2)+decalage;
                double murWidth = (monMur->line().length()*coef)+decalage;

                if(tableauSelect->scenePos().x()+translation->dx() > decalage
                        && tableauSelect->scenePos().y()+translation->dy() > decalage
                        && tableauSelect->scenePos().x()+translation->dx()+tableauSelect->pixmap().width() < murWidth
                        && tableauSelect->scenePos().y()+translation->dy()+tableauSelect->pixmap().height() < murHeight)
                    tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());

                else if(tableauSelect->scenePos().x()+translation->dx() < decalage
                        && tableauSelect->scenePos().y()+translation->dy() > decalage
                        && tableauSelect->scenePos().x()+translation->dx()+tableauSelect->pixmap().width() < murWidth
                        && tableauSelect->scenePos().y()+translation->dy()+tableauSelect->pixmap().height() < murHeight)
                    tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());

                else if(tableauSelect->scenePos().x()+translation->dx() > decalage
                        && tableauSelect->scenePos().y()+translation->dy() < decalage
                        && tableauSelect->scenePos().x()+translation->dx()+tableauSelect->pixmap().width() < murWidth
                        && tableauSelect->scenePos().y()+translation->dy()+tableauSelect->pixmap().height() < murHeight)
                    tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());

                else if(tableauSelect->scenePos().x()+translation->dx() > decalage
                        && tableauSelect->scenePos().y()+translation->dy() > decalage
                        && tableauSelect->scenePos().x()+translation->dx()+tableauSelect->pixmap().width() > murWidth
                        && tableauSelect->scenePos().y()+translation->dy()+tableauSelect->pixmap().height() < murHeight)
                    tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());

                else if(tableauSelect->scenePos().x()+translation->dx() > decalage
                        && tableauSelect->scenePos().y()+translation->dy() > decalage
                        && tableauSelect->scenePos().x()+translation->dx()+tableauSelect->pixmap().width() < murWidth
                        && tableauSelect->scenePos().y()+translation->dy()+tableauSelect->pixmap().height() > murHeight)
                    tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());

                update();
                translation->setP1(translation->p2());

            }

        }
        break;

    case TableauxEnMouvement:

        if(nombreDeTableauxDans(objets)!=0){

            if(nombreDeTableauxDans(objets)>1){

                double murHeight = ((vueDeHaut->getHauteurSalle()*100)*coef/2)+decalage;
                double murWidth = (monMur->line().length()*coef)+decalage;

                foreach (Tableau *item, listeDesTableauxDans(objets)){
                    Tableau *tableauSelect = qgraphicsitem_cast<Tableau *>(item);

                    if(tableauSelect->scenePos().x()+translation->dx() < decalage)
                        gauche=false;


                    if(tableauSelect->scenePos().y()+translation->dy() < decalage)
                        haut=false;


                    if(tableauSelect->scenePos().x()+translation->dx()+tableauSelect->pixmap().width() > murWidth)
                        droite=false;


                    if(tableauSelect->scenePos().y()+translation->dy()+tableauSelect->pixmap().height() > murHeight)
                        bas=false;

                }
                foreach (Tableau *item, listeDesTableauxDans(objets)){
                    Tableau *tableauSelect = qgraphicsitem_cast<Tableau *>(item);
                    if(gauche && haut && bas && droite)
                        tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());

                    else if(droite && haut && bas){
                        if(translation->dx()>0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            gauche=true;
                        }
                        else
                            tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());
                    }

                    else if(droite && gauche && bas){
                        if(translation->dy()>0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            haut=true;
                        }
                        else
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());
                    }

                    else if(droite && gauche && haut){
                        if(translation->dy()<0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            bas=true;
                        }
                        else
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());
                    }
                    else if(gauche && haut && bas){
                        if(translation->dx()<0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            droite=true;
                        }
                        else
                            tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());
                    }
                    else if(droite && bas){
                        if(translation->dx()>0 && translation->dy()>0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            haut=gauche=true;
                        }
                        else if(translation->dx()>0 && translation->dy()<=0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());
                            gauche=true;
                        }
                        else if(translation->dx()<=0 && translation->dy()>0){
                            tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());
                            haut=true;
                        }
                    }
                    else if(droite && haut){
                        if(translation->dx()>0 && translation->dy()<0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            bas=gauche=true;
                        }
                        else if(translation->dx()>0 && translation->dy()>=0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());
                            gauche=true;
                        }
                        else if(translation->dx()<=0 && translation->dy()<0){
                            tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());
                            bas=true;
                        }
                    }
                    else if(gauche && bas){
                        if(translation->dx()<0 && translation->dy()>0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            haut=droite=true;
                        }
                        else if(translation->dx()<0 && translation->dy()<=0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());
                            droite=true;
                        }
                        else if(translation->dx()>=0 && translation->dy()>0){
                            tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());
                            haut=true;
                        }
                    }
                    else if(gauche && haut){
                        if(translation->dx()<0 && translation->dy()<0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y()+translation->dy());
                            bas=droite=true;
                        }
                        else if(translation->dx()<0 && translation->dy()>=0){
                            tableauSelect->setPos(tableauSelect->scenePos().x()+translation->dx(),tableauSelect->scenePos().y());
                            droite=true;
                        }
                        else if(translation->dx()>=0 && translation->dy()<0){
                            tableauSelect->setPos(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+translation->dy());
                            bas=true;
                        }
                    }


                }

                update();
                translation->setP1(translation->p2());

            }

        }
        break;

    case redimensionnement:

        if(nombreDeTableauxDans(objets)==1) {
            double murHeight = ((vueDeHaut->getHauteurSalle()*100)*coef/2)+decalage;
            double murWidth = (monMur->line().length()*coef)+decalage;
            switch (coin) {

            case BD :
                if(this->items().contains(graphiqueRedimentionnement))
                    removeItem(graphiqueRedimentionnement);
                haut=false;

                wa=zoneRedimentionnement.topLeft().x()+(zoneRedimentionnement.bottomRight().x()-zoneRedimentionnement.topLeft().x()+translation->dx());
                ha=zoneRedimentionnement.topLeft().y()+int((zoneRedimentionnement.bottomRight().x()-zoneRedimentionnement.topLeft().x()+translation->dx())/ratio);

                if(wa<=murWidth && ha<=murHeight && zoneRedimentionnement.topLeft().x()<zoneRedimentionnement.bottomRight().x()+translation->dx())
                    zoneRedimentionnement.setBottomRight(QPointF(zoneRedimentionnement.topLeft().x()+(zoneRedimentionnement.bottomRight().x()-zoneRedimentionnement.topLeft().x()+translation->dx()),
                                                                 zoneRedimentionnement.topLeft().y()+int((zoneRedimentionnement.bottomRight().x()-zoneRedimentionnement.topLeft().x()+translation->dx())/ratio)));
                else if(wa<=murWidth && ha>murHeight)
                    zoneRedimentionnement.setBottomRight(QPointF(zoneRedimentionnement.bottomRight().x(),zoneRedimentionnement.bottomRight().y()));
                else if(wa>murWidth && ha<=murHeight)
                    zoneRedimentionnement.setBottomRight(QPointF(zoneRedimentionnement.bottomRight().x(),zoneRedimentionnement.bottomRight().y()));
                else if(zoneRedimentionnement.topLeft().x()>zoneRedimentionnement.bottomRight().x()+translation->dx())
                    haut=true;

                graphiqueRedimentionnement->setRect(zoneRedimentionnement);

                this->addItem(graphiqueRedimentionnement);


                supprimerMesure();
                mesureLargeurTab->setPlainText(QString(QString::number(zoneRedimentionnement.width()/350.0,'g',3)+" m"));
                pointSelection= QPointF((zoneRedimentionnement.topRight().x()+zoneRedimentionnement.topLeft().x())/2,zoneRedimentionnement.topRight().y()-decalage);
                mesureLargeurTab->setPos(pointSelection);
                this->addItem(mesureLargeurTab);
                mesureHauteurTab->setPlainText(QString(QString::number(zoneRedimentionnement.height()/350.0,'g',3)+" m"));
                pointSelection= QPointF(zoneRedimentionnement.topLeft().x()-decalage*2,(zoneRedimentionnement.bottomLeft().y()-(zoneRedimentionnement.height()/2)));
                mesureHauteurTab->setPos(pointSelection);
                this->addItem(mesureHauteurTab);


                widthRedimentionnement= (zoneRedimentionnement.bottomRight().x()-zoneRedimentionnement.topLeft().x());


                break;
            default :

                break;

            }
            translation->setP1(translation->p2());
        }


        break;

    default:

        break;
    }




}

void VueFace::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    peindre();
    supprimerMesure();
    emit tableauModifie();
    supprimerCoins();
    aucunTableauSelectionne();
    switch(monMode) {
    case SelectionEnCours:

        if(this->items().contains(&graphiqueSelection))
            removeItem(&graphiqueSelection);

        if(nombreDeTableauxDans(objets) == 0){
            // //qDebug() << "objets au relachement : " << nombreDeTableauxDans(objets);
            setMode(VueFace::Select);
        }

        else if(nombreDeTableauxDans(objets)==1) {
            Tableau *tableauSelect = qgraphicsitem_cast<Tableau *>(listeDesTableauxDans(objets).first());
            ajouterCoins(tableauSelect);
            ajouterMesure(tableauSelect);
            unTableauEstSelectionne();
            tableauSelectionne=tableauSelect;
            majSpin();
            setMode(VueFace::TableauSelectionne);


        }
        else if(nombreDeTableauxDans(objets)>1) {
            // //qDebug() << "La sélection comporte plusieurs tableaux : " << nombreDeTableauxDans(objets);
            setMode(VueFace::TableauxSelectionnes);


        }

        //qDebug()<<"objets aux release (Select): " << objets;

        break;


    case TableauEnMouvement:
        ////qDebug()<<"objets aux release (Tableau en mouvement): " << objets;
        //this->monMur->getVueHaut()->getFenetre()->spinHTab->setValue(this->monMur->getVueHaut()->getFenetre()->spinHTab->value()+0.5);
        //        setHeight(200,listeDesTableauxDans(objets).first());
        unTableauEstSelectionne();
        tableauSelectionne=listeDesTableauxDans(objets).first();
        ajouterMesure(listeDesTableauxDans(objets).first());
        ajouterCoins(listeDesTableauxDans(objets).first());
        majSpin();
        setMode(VueFace::Select);

        break;

    case TableauxEnMouvement:

        haut=bas=gauche=droite=true;
        setMode(VueFace::Select);

        break;

    case TableauSelectionne:
        unTableauEstSelectionne();
        ajouterMesure(listeDesTableauxDans(objets).first());
        ajouterCoins(listeDesTableauxDans(objets).first());
        setMode(VueFace::Select);

        break;

    case redimensionnement:

        if(!haut){
        if(this->items().contains(graphiqueRedimentionnement))
            removeItem(graphiqueRedimentionnement);


        unTableauEstSelectionne();
        listeDesTableauxDans(objets).first()->setPixmap(QPixmap(listeDesTableauxDans(objets).first()->getFichier()).scaledToWidth(widthRedimentionnement));
        ajouterCoins(listeDesTableauxDans(objets).first());
        ajouterMesure(listeDesTableauxDans(objets).first());
        setMode(VueFace::Select);

        majSpin();}
        else
            supprimerTableauxSelect();
        break;
    default:

        break;

    }

}

void VueFace::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Delete:
        supprimerTableauxSelect();
        break;
    default:
        break;

    }
}

void VueFace::keyReleaseEvent(QKeyEvent *event) {

}

void VueFace::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if(event->delta() > 0){
        this->monMur->getVueHaut()->getFenetre()->zoomer();
    }
    else if(event->delta() < 0){
        this->monMur->getVueHaut()->getFenetre()->dezoomer();
    }
}

void VueFace::setMode(Mode mode) {
    monMode = mode;
    //qDebug() << "mode = " << mode;
}

void VueFace::setCoin(CoinTab mode) {
    coin = mode;
    // //qDebug() << "coin = " << mode;
}

QList<Tableau *> VueFace::listeDesTableaux(){
    QList<Tableau *> liste;

    if(!items().isEmpty()){
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == Tableau::Type){
                liste.append(qgraphicsitem_cast<Tableau *>(item));
            }
        }

    }
    return liste;
}

bool VueFace::contientTableaux(){
    QList<Tableau *> lst = this->listeDesTableaux();
    if(lst.count()>0)
        return true;
    return false;
}

int VueFace::nombreDeTableauxDans(QList<QGraphicsItem *> lst){
    int nb=0;
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Tableau::Type)
            nb++;
    }
    return nb;
}

void VueFace::peindre() {


    if(!listeDesTableauxDans(items()).isEmpty())
        foreach (Tableau *item, listeDesTableauxDans(items())) {
            if(item->graphicsEffect() != NULL){
                delete item->graphicsEffect();
            }
        }

    if(!listeDesTableauxDans(objets).isEmpty())
        foreach (Tableau *item, listeDesTableauxDans(objets)) {
            QGraphicsColorizeEffect *eff = new QGraphicsColorizeEffect;
            eff->setColor(QColor(130,0,0));
            item->setGraphicsEffect(eff);
        }
}

QRectF VueFace::approxProches(const QPointF &point){
    QPointF topLeft(point.x()-8,point.y()-8);
    QPointF botRight(point.x()+5,point.y()+5);
    QRectF rect(topLeft,botRight);

    return rect;
}


/**

  Debut modifs andre

  **/

void VueFace::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {

    if(event->mimeData()->hasUrls()){
        QList<QUrl> urlList = event->mimeData()->urls();
        // //qDebug() << "URL : " << urlList;
        foreach (QUrl url, urlList) {
            QFileInfo f(url.path());
            if(f.exists()){
                event->accept();
                this->setBackgroundBrush(QBrush(QColor(0,0,0,200)));
            }
            else {
                event->ignore();
            }
        }
    }
}

void VueFace::dropEvent(QGraphicsSceneDragDropEvent *event) {
    if(event->mimeData()->hasUrls()){
        QList<QUrl> urlList = event->mimeData()->urls();
        // //qDebug() << "URL : " << urlList;
        foreach (QUrl url, urlList) {
            QFileInfo f(url.path());
            if(f.exists()){
                event->accept();
                this->setBackgroundBrush(*brush);
                /** Ajoute le tableau f */
                this->ajouterTableau(f.absoluteFilePath(),event->scenePos());
                //                maNot->setDelai(20);
                //                maNot->setMessage(tr("Tableau ajouté"));
                //                maNot->lancer();
            }
            else {
                event->ignore();
            }
        }
    }
}

void VueFace::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    event->acceptProposedAction();
}

void VueFace::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    event->accept();
    this->setBackgroundBrush(*brush);
}

void VueFace::initialiserEffets() {

}

void VueFace::ajouterCoins(Tableau* tableauSelect) {
    supprimerCoins();
    //    coinHG->setRect(approxProches(tableauSelect->scenePos()));
    //    coinHD->setRect(approxProches(QPointF(tableauSelect->scenePos().x()+tableauSelect->pixmap().width(),tableauSelect->pos().y())));
    //    coinBG->setRect(approxProches(QPointF(tableauSelect->scenePos().x(),tableauSelect->scenePos().y()+tableauSelect->pixmap().height())));
    coinBD->setRect(approxProches(QPointF(tableauSelect->scenePos().x()+tableauSelect->pixmap().width(),tableauSelect->scenePos().y()+tableauSelect->pixmap().height())));
    //    this->addItem(coinHG);
    //    this->addItem(coinHD);
    //    this->addItem(coinBG);
    this->addItem(coinBD);
}

void VueFace::supprimerCoins() {
    //    if(this->items().contains(coinHG))
    //        removeItem(coinHG);
    //    if(this->items().contains(coinHD))
    //        removeItem(coinHD);
    //    if(this->items().contains(coinBG))
    //        removeItem(coinBG);
    if(this->items().contains(coinBD))
        removeItem(coinBD);
}

void VueFace::setHauteur(double hauteur) {
    double murHeight = vueDeHaut->getHauteurSalle()*350+decalage;
    if(tableauSelectionne!=NULL){
    if(murHeight-(hauteur*350)+tableauSelectionne->pixmap().height()<=murHeight && murHeight-(hauteur*350)>=decalage){
        tableauSelectionne->setPos(tableauSelectionne->scenePos().x(),murHeight-(hauteur*350));
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
    else if(murHeight-(hauteur*350)+tableauSelectionne->pixmap().height()<=murHeight) {
        tableauSelectionne->setPos(tableauSelectionne->scenePos().x(),decalage);ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
    else if(murHeight-(hauteur*350)>=decalage){
        tableauSelectionne->setPos(tableauSelectionne->scenePos().x(),murHeight-tableauSelectionne->pixmap().height());
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
    }
}

void VueFace::setLargeur(double largeur) {
    double murWidth = (monMur->line().length()*coef)+decalage;
    if(tableauSelectionne!=NULL)
    if(largeur*350+decalage+tableauSelectionne->pixmap().width()<=murWidth && largeur*350+decalage>=decalage){
        tableauSelectionne->setPos(largeur*350+decalage,tableauSelectionne->scenePos().y());
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
    else if(largeur*350+decalage+tableauSelectionne->pixmap().width()>=murWidth) {
        tableauSelectionne->setPos(murWidth-tableauSelectionne->pixmap().width(),tableauSelectionne->scenePos().y());
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
    else if(largeur*350+decalage>=decalage){
        tableauSelectionne->setPos(decalage,tableauSelectionne->scenePos().y());
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
}

void VueFace::setHeight(double height) {
    double murHeight = vueDeHaut->getHauteurSalle()*350+decalage;
    double murWidth = (monMur->line().length()*coef)+decalage;
    if(tableauSelectionne!=NULL)
    if(tableauSelectionne->scenePos().x()+tableauSelectionne->pixmap().scaledToHeight(int(height*350)).width() < murWidth && tableauSelectionne->scenePos().y()+tableauSelectionne->pixmap().scaledToHeight(int(height*350)).height() < murHeight) {
        tableauSelectionne->setPixmap(QPixmap(tableauSelectionne->getFichier()).scaledToHeight(int(height*350)));
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }

}

void VueFace::setWidth(double width) {
    double murHeight = vueDeHaut->getHauteurSalle()*350+decalage;
    double murWidth = (monMur->line().length()*coef)+decalage;
    if(tableauSelectionne!=NULL)
    if(tableauSelectionne->scenePos().x()+tableauSelectionne->pixmap().scaledToWidth(int(width*350)).width() < murWidth && tableauSelectionne->scenePos().y()+tableauSelectionne->pixmap().scaledToWidth(int(width*350)).height() < murHeight) {
        tableauSelectionne->setPixmap(QPixmap(tableauSelectionne->getFichier()).scaledToWidth(int(width*350)));
        ajouterMesure(tableauSelectionne);
        ajouterCoins(tableauSelectionne);
    }
}

void VueFace::unTableauEstSelectionne() {

}

void VueFace::aucunTableauSelectionne() {

}

void VueFace::majSpin() {
    double murHeight = vueDeHaut->getHauteurSalle()*350+decalage;
    this->monMur->getVueHaut()->getFenetre()->spinHTab->setValue(tableauSelectionne->pixmap().height()/350.0);
    this->monMur->getVueHaut()->getFenetre()->spinLTab->setValue(tableauSelectionne->pixmap().width()/350.0);
    this->monMur->getVueHaut()->getFenetre()->spinHDistTab->setValue((murHeight-(tableauSelectionne->scenePos().y()))/350);
    this->monMur->getVueHaut()->getFenetre()->spinLDistTab->setValue((tableauSelectionne->scenePos().x()-decalage)/350);
}

void VueFace::tuerLaVariable() {
    objets.clear();
    tableauSelectionne=NULL;
}
