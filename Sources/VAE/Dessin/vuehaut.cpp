#include "vuehaut.h"


VueHaut::VueHaut(Fenetre *fentre, QObject *parent) :
    QGraphicsScene(parent)
{
    main = parent;
    maFenetre = fentre;
    fantome = new Mur(QLineF(0,0,0,0),this);
    initialiser();
    initialiserMenus();
}

/**
  * Constructeur de copie !
  *
  */

VueHaut::VueHaut(VueHaut &other) {

    //qDebug() << "############################################ Constructeur !";


    maFenetre = other.getFenetre();
    initialiser();
    initialiserMenus();
    hauteurSalle= other.getHauteurSalle();
    fantome = new Mur(QLineF(0,0,0,0),this);
    typeObjet3D = other.typeObjet3D;
    foreach(QGraphicsItem *item,other.items()) {

        if(item->type() == Mur::Type)
        {
            Mur *mur = qgraphicsitem_cast<Mur *>(item);
            Mur *obj = new Mur(*mur);
            this->addItem(obj);

            //qDebug() << "Mur : [(" << obj->line().x1() << "," << obj->line().y1() <<") || (" << obj->line().x2() << "," << obj->line().y2() <<")]" ;
        }
        else if(item->type() == Courbe::Type)
        {
            Courbe *courbe = qgraphicsitem_cast<Courbe *>(item);
            Courbe *obj= new Courbe(*courbe);
            this->addItem(obj);

            //qDebug() << "Courbe : [(" << obj->getDebut().x() << "," << obj->getDebut().y() <<") || (" << obj->getPointUn().x() << "," << obj->getPointUn().y() <<") || ("<< obj->getPointDeux().x() << "," << obj->getPointDeux().y() <<") || ("<< obj->getFin().x() << "," << obj->getFin().y() <<")]" ;
        }
        else if(item->type() == typeObjet3D)
        {
            Objet3D *objet = qgraphicsitem_cast<Objet3D *>(item);
            Objet3D *obj= new Objet3D(*objet);
            this->addItem(obj);

            //qDebug() << "Courbe : [(" << obj->getDebut().x() << "," << obj->getDebut().y() <<") || (" << obj->getPointUn().x() << "," << obj->getPointUn().y() <<") || ("<< obj->getPointDeux().x() << "," << obj->getPointDeux().y() <<") || ("<< obj->getFin().x() << "," << obj->getFin().y() <<")]" ;
        }

        main = other.main;

        fantome->setLine(QLineF(0,0,0,0));

    }

    surelevations.clear();
    foreach (Surelevation *surelev, other.surelevations) {
        Surelevation *sur;
        sur = new Surelevation(*surelev);
        this->surelevations.append(sur);
        this->addItem(sur->getGraphicsSurelevation());
        sur->majSurelevation();
        //qDebug() << "Surelevation";
    }
}

/**
  *
  * Operateur = ( marche pas )
  *
  */

//VueHaut& VueHaut::operator =(const VueHaut& other){

//    //qDebug() << "############################################ operateur = !";

//    foreach(QGraphicsItem *item,other.items()) {

//        if(item->type() == Mur::Type)
//        {
//            Mur *obj = qgraphicsitem_cast<Mur *>(item);
//            this->addItem(obj);

//            //qDebug() << "Mur : [(" << obj->line().x1() << "," << obj->line().y1() <<") || (" << obj->line().x2() << "," << obj->line().y2() <<")]" ;
//        }
//        else if(item->type() == Courbe::Type)
//        {
//            Courbe *courbe = qgraphicsitem_cast<Courbe *>(item);
//            Courbe *obj= new Courbe(*courbe);
//            this->addItem(obj);

//            //qDebug() << "Courbe : [(" << obj->getDebut().x() << "," << obj->getDebut().y() <<") || (" << obj->getPointUn().x() << "," << obj->getPointUn().y() <<") || ("<< obj->getPointDeux().x() << "," << obj->getPointDeux().y() <<") || ("<< obj->getFin().x() << "," << obj->getFin().y() <<")]" ;
//        }
//        else if(item->type() == QGraphicsSurelevationItem::Type)
//        {
//            QGraphicsSurelevationItem *obj = qgraphicsitem_cast<QGraphicsSurelevationItem *>(item);
//            this->addItem(obj);

//            //qDebug() << "Surelevation";
//        }

//    }
//    return *this;
//}




VueHaut::Mode VueHaut::getMode(){
    return monMode;
}

QRectF VueHaut::approxProches(const QPointF &point){
    QPointF topLeft(point.x()-5,point.y()+5);
    QPointF botRight(point.x()+5,point.y()-5);
    QRectF rect(topLeft,botRight);

    return rect;
}

QRectF VueHaut::cerclePoint(const QPointF &point){
    QPointF topLeft(point.x()-4,point.y()+4);
    QPointF botRight(point.x()+4,point.y()-4);
    QRectF rect(topLeft,botRight);

    return rect;
}

bool VueHaut::getModifing()
{
    return modifing;
}

void VueHaut::setModifing(bool modif) {
    modifing = modif;
}

void VueHaut::changerTypeObjetSelect(int index){
    if(nombreDObjetsDans(objets) == nombreDElementsDans(objets)) {
        foreach (Objet3D *obj, listeDesObjetsDans(objets)) {
            obj->setType(Objet3D::TypeObjet(index));
        }
    }
}

void VueHaut::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // On definit le centre de la salle

    if(!verouille){
        centreCamera.setPos(QPointF(this->genererCentreVueHaut().x()-5,this->genererCentreVueHaut().y()-5));

        if (mouseEvent->button() == Qt::LeftButton){

            // Si on appuie sur CTRL
            if(monModificateur == this->CTRL){
                translation.setP1(mouseEvent->scenePos());
                translation.setP2(mouseEvent->scenePos());
                //qDebug() << "On vient de cliquer avec le modificateur Ctrl enclenché";
            }
            else {


                QPointF *liaison;
                //qDebug() << "mode = " << monMode;
                switch (monMode) {

                // --------- Si on a préalablement sélectionné des murs --------------- //

                case MursSelectionnes:
                    if(this->items().contains(mesure))
                        this->removeItem(mesure);
                    if(nombreDeMursDans(objets)>1){
                        foreach (QGraphicsItem *item, listeDesMursDans(objets)) {
                            // On instancie un nouveau mur en le castant depuis la sélection
                            Mur *murSelect = qgraphicsitem_cast<Mur *>(item);
                            murSelect->setPen(*penMurSelectionne);

                            // On ajoute la mesure du mur
                            //                    emit unMurEstSelectionne();

                        }
                        translation.setP1(mouseEvent->scenePos());
                        //qDebug() << "on essaye de bouger les murs (il y en a " << nombreDeMursDans(objets) << ")";
                        partieSelectionnee = Base;
                        //                    setMode(VueHaut::MurSelectionne);
                        setMode(VueHaut::ElementsSelectionnesEnMouvement);
                    }
                    break;


                case ElementsSelectionnes:
                    if(this->items().contains(mesure))
                        this->removeItem(mesure);
                    if(nombreDElementsDans(objets)>1){
                        peindre(*penMurSelectionne, objets);
                        translation.setP1(mouseEvent->scenePos());
                        //qDebug() << "on essaye de bouger les Objets (il y en a " << nombreDElementsDans(objets) << ")";
                        partieSelectionnee = Base;
                        //                    setMode(VueHaut::MurSelectionne);
                        setMode(VueHaut::ElementsSelectionnesEnMouvement);
                    }
                    break;


                    // ------------------- Si on ajoute un nouveau mur -------------------- //

                case AjoutMur:
                    Mur *murEnCours;
                    if(this->items().contains(selectPoint))
                        this->removeItem(selectPoint);

                    if(this->items().contains(mesure))
                        this->removeItem(mesure);
                    ligneDeMur->setPoints(mouseEvent->scenePos(),mouseEvent->scenePos());

                    liaison = new QPointF(0,0);
                    murEnCours = new Mur(*ligneDeMur,this);
                    emit murAffichable(murEnCours->isAffichable());
                    emit murMobile(murEnCours->isMobile());

                    if(!this->items().contains(mesure))
                        this->addItem(mesure);
                    if(mesure != NULL)
                        mesure->setPos(mouseEvent->scenePos());
                    foreach (QGraphicsItem *item, items()) {
                        if (item->type() == Mur::Type && item!=murEnCours){
                            if(murEnCours->debutEstProche(*qgraphicsitem_cast<Mur *>(item),liaison)){
                                ligneDeMur->setP1(*liaison);
                                murEnCours->setLine(*ligneDeMur);
                            }

                        }
                        else if (item->type() == Courbe::Type && item!=fantome){
                            if(murEnCours->debutEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison)){
                                ligneDeMur->setP1(*liaison);
                                murEnCours->setLine(*ligneDeMur);
                            }
                        }

                    }
                    murEnCours->setPen(*penMurEnCours);
                    //            murEnCours->setFlag(QGraphicsItem::ItemIsSelectable);
                    this->addItem(murEnCours);
                    //qDebug() <<" on ajoute en press : " << murEnCours;
                    monMode = DessinMur;
                    break;


                    // ------------------- Si on ajoute un nouvel objet -------------------- //

                case AjoutObjet:
                    Objet3D *objetEnCours;
                    //                    if(this->items().contains(selectPoint))
                    //                        this->removeItem(selectPoint);

                    //                    if(this->items().contains(mesure))
                    //                        this->removeItem(mesure);
                    ligneDeMur->setPoints(mouseEvent->scenePos(),mouseEvent->scenePos());

                    //                    liaison = new QPointF(0,0);
                    objetEnCours = new Objet3D(Objet3D::Colonne);
                    objetEnCours->setPos(mouseEvent->scenePos());


                    //                    if(!this->items().contains(mesure))
                    //                        this->addItem(mesure);
                    //                    if(mesure != NULL)
                    //                        mesure->setPos(mouseEvent->scenePos());
                    //                    foreach (QGraphicsItem *item, items()) {
                    //                        if (item->type() == Mur::Type && item!=murEnCours){
                    //                            if(murEnCours->debutEstProche(*qgraphicsitem_cast<Mur *>(item),liaison)){
                    //                                ligneDeMur->setP1(*liaison);
                    //                                murEnCours->setLine(*ligneDeMur);
                    //                            }

                    //                        }
                    //                        else if (item->type() == Courbe::Type && item!=fantome){
                    //                            if(murEnCours->debutEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison)){
                    //                                ligneDeMur->setP1(*liaison);
                    //                                murEnCours->setLine(*ligneDeMur);
                    //                            }
                    //                        }

                    //                    }
                    //                    murEnCours->setPen(*penMurEnCours);
                    //            murEnCours->setFlag(QGraphicsItem::ItemIsSelectable);
                    this->addItem(objetEnCours);
                    //qDebug() <<" on ajoute en press : " << murEnCours;
                    monMode = Select;
                    break;


                    // ------------------- Si on ajoute une nouvelle courbe -------------------- //

                case AjoutCourbe:
                    Courbe *courbeEnCour;
                    cheminCourbe = new QPainterPath(mouseEvent->scenePos());

                    if(this->items().contains(selectPoint))
                        this->removeItem(selectPoint);

                    if(this->items().contains(mesure))
                        this->removeItem(mesure);

                    ligneDeMur->setPoints(mouseEvent->scenePos(),mouseEvent->scenePos());
                    fantome->setLine(*ligneDeMur);
                    fantome->setPen(*penMurEnCours);

                    liaison = new QPointF(0,0);
                    foreach (QGraphicsItem *item, items()) {
                        if (item->type() == Mur::Type && item!=fantome){
                            QPointF *liaison = new QPointF(0,0);
                            if(fantome->debutEstProche(*qgraphicsitem_cast<Mur *>(item),liaison)){
                                ligneDeMur->setP1(*liaison);
                                fantome->setLine(*ligneDeMur);
                            }
                        }
                        else if (item->type() == Courbe::Type && item!=fantome){
                            QPointF *liaison = new QPointF(0,0);
                            if(fantome->debutEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison)){
                                ligneDeMur->setP1(*liaison);
                                fantome->setLine(*ligneDeMur);
                            }
                        }
                    }



                    courbeEnCour = new Courbe(*cheminCourbe);

                    courbeEnCour->setPen(*penMurEnCours);

                    this->addItem(courbeEnCour);
                    this->addItem(fantome);
                    monMode = DessinCourbe;
                    break;

                    // --------------- Si on selectionne un objet de la scene -------------- //

                case Select:

                    // on enlàve la mesure si elle est affichée
                    if(this->items().contains(mesure))
                        this->removeItem(mesure);
                    if(items().contains(pointCourbeUn))
                        removeItem(pointCourbeUn);
                    if(items().contains(pointCourbeDeux))
                        removeItem(pointCourbeDeux);

                    //                    cacherNormale();
                    // Si on a sélectionné un ou plusieurs murs
                    if(!objets.isEmpty()){

                        // Si on a selectionné UN et UN SEUL mur
                        if(nombreDeMursDans(objets) == 1 && nombreDElementsDans(objets) == 1){

                            // On récupÃÂ¨re le mur
                            Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());

                            // On coche les cases [Affichable] et [Mobile] en conséquence
                            emit murAffichable(murSelect->isAffichable());
                            emit murMobile(murSelect->isMobile());

                            // On le dessine avec la couleur corresondant a ses attributs
                            murSelect->setPen(*penMurFini);
                            if(murSelect->isMobile()){
                                murSelect->setPen(*penMurMobile);
                            }
                            else if(!murSelect->isAffichable()){
                                murSelect->setPen(*penMurNonAffichable);
                            }

                            // On définit le mode : un (ou des) mur(s) sélectionnés
                            setMode(VueHaut::MurSelectionne);
                        }
                        else if(nombreDeMursDans(objets)>1){
                            // Si on a sélectionné plus d'un mur, pour chaque mur sélectionné...
                            foreach (QGraphicsItem *item, listeDesMursDans(objets)) {

                                // On récupÃÂ¨re le mur
                                Mur *murSelect = qgraphicsitem_cast<Mur *>(item);
                                // On coche les cases [Affichable] et [Mobile] en conséquence
                                emit murAffichable(murSelect->isAffichable());
                                emit murMobile(murSelect->isMobile());
                                // On le dessine avec la couleur corresondant a ses attributs
                                murSelect->setPen(*penMurFini);
                                if(murSelect->isMobile()){
                                    murSelect->setPen(*penMurMobile);
                                }
                                else if(!murSelect->isAffichable()){
                                    murSelect->setPen(*penMurNonAffichable);
                                }
                            }
                            // On définit le mode : un (ou des) mur(s) sélectionnés
                            setMode(VueHaut::ElementsSelectionnesEnMouvement);
                        }

                        if(nombreDeSurelevationsDans(objets) == 1){
                            QGraphicsSurelevationItem *surelevSelect = qgraphicsitem_cast<QGraphicsSurelevationItem *>(listeDesSurelevationsDans(objets).first());
                            surelevSelect->setPen(*penMurSelectionne);
                        }

                        if(nombreDObjetsDans(objets) == 1){
                            Objet3D *objetSelect = qgraphicsitem_cast<Objet3D *>(listeDesObjetsDans(objets).first());
                            objetSelect->setPen(*penMurSelectionne);
                            setMode(VueHaut::ObjetSelectionne);
                        }

                        if(nombreDeCourbesDans(objets) == 1){

                            Courbe *courbeSelect = qgraphicsitem_cast<Courbe *>(listeDesCourbesDans(objets).first());

                            translation.setP1(mouseEvent->scenePos());
                            courbeSelect->setPen(*penMurFini);


                            setMode(VueHaut::CourbeSelectionne);
                        }
                        else if(nombreDeCourbesDans(objets)>1){
                            foreach (QGraphicsItem *item, listeDesCourbesDans(objets)) {

                                Courbe *CourbeSelect = qgraphicsitem_cast<Courbe *>(item);

                                CourbeSelect->setPen(*penMurFini);

                            }
                            setMode(VueHaut::ElementsSelectionnesEnMouvement);
                        }

                    }

                    // On récupÃÂ¨re le ou les murs présents dans la sélection
                    objets = items(approxProches(mouseEvent->scenePos()));
                    qDebug() << "Il y a " << objets.count() << " objets sélectionnés : ";
                    foreach (QGraphicsItem *item, objets) {
                        Objet3D *obj = new Objet3D(Objet3D::Colonne);
                        qDebug() << "- type = " << item->type() << " et obj.type() = " << typeObjet3D;
                        qDebug() << "assert : " << bool(item->type()==typeObjet3D);
                    }
                    // Si la selection n'est pas vide
                    if(!objets.isEmpty()){
                        // Si il y a un ou plusieurs murs sélectionnés
                        if(nombreDeMursDans(objets) >= 1){

                            // Si on a plus d'un objet sélectionné
                            if(objets.count()>1)
                                superpose=true;
                            else
                                superpose=false;

                            // On instancie un nouveau mur en le castant depuis la sélection
                            // puis on le colorie dans la couleur [sélectionné]
                            Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());
                            murSelect->setPen(*penMurSelectionne);
                            //                            afficherNormaleMurSelect();


                            // On définit le premier point de la translation a effectuer pour déplacer la ligne
                            translation.setP1(mouseEvent->scenePos());

                            // Si on a sélectionné une extrémité du mur...
                            if(approxProches(mouseEvent->scenePos()).contains(murSelect->line().p1())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(murSelect->line().p1()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionnee = Debut;
                                //qDebug() << "On a selectionné le début !";
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(murSelect->line().p2())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(murSelect->line().p2()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionnee = Fin;
                                //qDebug() << "On a selectionné la fin !";
                            }
                            else {
                                // Si on a selectionné le mur lui mÃÂªme...
                                partieSelectionnee = Base;
                            }
                            setMode(VueHaut::MurSelectionne);
                            // On ajoute la mesure du mur
                            mesure->setPlainText(QString(QString::number(murSelect->line().length()/echelle,'g',3)+" m"));
                            QPointF coord((murSelect->line().x1()+murSelect->line().x2())/2,(murSelect->line().y1()+murSelect->line().y2())/2);
                            mesure->setPos(coord);
                            mesure->setFlag(QGraphicsItem::ItemIsSelectable,false);
                            this->addItem(mesure);
                            emit unMurEstSelectionne();

                            //Met a jour les spinBox de mesure et de longueur du mur selectionné
                            setModifing(true);
                            emit angleSelectModifie(murSelect->line().angle());
                            emit longueurSelectModifiee(double(murSelect->line().length()/echelle));
                            setModifing(false);
                        }
                        else if(nombreDeCourbesDans(objets) >= 1){

                            // Si on a plus d'un objet sélectionné
                            if(objets.count()>1)
                                superpose=true;
                            else
                                superpose=false;

                            // On instancie un nouveau mur en le castant depuis la sélection
                            // puis on le colorie dans la couleur [sélectionné]
                            //qDebug() << "COURBES : " << listeDesCourbes();
                            Courbe *courbeSelect = qgraphicsitem_cast<Courbe *>(listeDesCourbesDans(objets).first());
                            courbeSelect->setPen(*penMurSelectionne);

                            if(items().contains(pointCourbeUn))
                                removeItem(pointCourbeUn);
                            if(items().contains(pointCourbeDeux))
                                removeItem(pointCourbeDeux);

                            pointCourbeUn->setRect(approxProches(courbeSelect->getPointUn()));
                            pointCourbeDeux->setRect(approxProches(courbeSelect->getPointDeux()));
                            this->addItem(pointCourbeUn);
                            this->addItem(pointCourbeDeux);

                            // On définit le premier point de la translation a effectuer pour déplacer la ligne
                            translation.setP1(mouseEvent->scenePos());

                            // Si on a sélectionné une extrémité du mur...
                            if(approxProches(mouseEvent->scenePos()).contains(courbeSelect->getDebut())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(courbeSelect->getDebut()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionneeC = DebutC;
                                //qDebug() << "On a selectionné le début !";
                                bouge=true;
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(courbeSelect->getFin())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(courbeSelect->getFin()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionneeC = FinC;
                                //qDebug() << "On a selectionné la fin !";
                                bouge=true;
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(courbeSelect->getPointUn())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(courbeSelect->getPointUn()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionneeC = PointUn;
                                //qDebug() << "On a selectionné le point un !";
                                bouge=true;
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(courbeSelect->getPointDeux())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(courbeSelect->getPointDeux()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionneeC = PointDeux;
                                //qDebug() << "On a selectionné le point deux !";
                                bouge=true;
                            }
                            else {
                                // Si on a selectionné le mur lui mÃÂªme...
                                partieSelectionneeC = BaseC;
                                bouge=true;
                            }
                            setMode(VueHaut::CourbeSelectionne);
                            // On ajoute la mesure du mur
                            emit unMurEstSelectionne();
                        }
                        else if(nombreDeSurelevationsDans(objets) >= 1) {
                            surelevEnCours = NULL;
                            selectPoint = NULL;

                            foreach (Surelevation *it, surelevations) {
                                if(it->getGraphicsSurelevation()->polygon().containsPoint(mouseEvent->scenePos(),Qt::OddEvenFill)) {
                                    surelevEnCours = it;
                                }
                            }
                            setMode(VueHaut::SurelevationSelectionne);
                            if(surelevEnCours != NULL) {
                                foreach (QPoint3D *item, *surelevEnCours->getListeDesPoints()) {
                                    if(approxProches(mouseEvent->scenePos()).contains(item->toQPoint())){
                                        if(items().contains(selectPoint))
                                            removeItem(selectPoint);
                                        pointSurelev = item;
                                        selectPoint = new QGraphicsRectItem(approxProches(item->toQPoint()));
                                        addItem(selectPoint);
                                        setMode(VueHaut::PointSurelevationSelectionne);
                                    }
                                }
                            }
                            translation.setP1(mouseEvent->scenePos());
                            emit uneSurelevationEstSelectionnee();
                        }
                        else if(nombreDObjetsDans(objets) >= 1){

                            Objet3D *objetSelect = qgraphicsitem_cast<Objet3D *>(listeDesObjetsDans(objets).first());
                            objetSelect->setPen(*penMurSelectionne);
                            translation.setP1(mouseEvent->scenePos());
                            setMode(VueHaut::ObjetSelectionne);
                            //                            pointRotationObjet->setPos(objetSelect->getRect().topRight());
                            //                            this->addItem(pointRotationObjet);
                            emit unObjetEstSelectionne();
                            emit angleObjetSelectModifie(objetSelect->rotation());

                        }

                    }
                    else {
                        if(this->items().contains(pointRotationObjet))
                            this->removeItem(pointRotationObjet);
                        if(this->items().contains(mesure))
                            this->removeItem(mesure);
                        emit aucunMurEstSelectionne();
                        setMode(VueHaut::SelectionEnCours);
                        pointSelection = mouseEvent->scenePos();
                    }
                    break;

                case CourbeSelectionne:

                    setMode(Select);

                    translation.setP1(mouseEvent->scenePos());
                    translation.setP2(mouseEvent->scenePos());

                    if(!objets.isEmpty()){

                        if(listeDesCourbesDans(objets).count() == 1){
                            if((approxProches(mouseEvent->scenePos()).contains(listeDesCourbesDans(objets).first()->getPointUn()))){
                                unDeux=true;
                                this->setMode(PointControleSelectionne);
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(listeDesCourbesDans(objets).first()->getPointDeux())){
                                unDeux=false;
                                this->setMode(PointControleSelectionne);
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(listeDesCourbesDans(objets).first()->getDebut())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(listeDesCourbesDans(objets).first()->getDebut()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionneeC = DebutC;
                                //qDebug() << "On a selectionné le début !";
                                bouge=true;
                                this->setMode(CourbeSelectionne);
                            }
                            else if(approxProches(mouseEvent->scenePos()).contains(listeDesCourbesDans(objets).first()->getFin())){
                                selectPoint = new QGraphicsRectItem(cerclePoint(listeDesCourbesDans(objets).first()->getFin()));
                                selectPoint->setFlag(QGraphicsItem::ItemIsSelectable,false);
                                this->addItem(selectPoint);
                                partieSelectionneeC = FinC;
                                //qDebug() << "On a selectionné le début !";
                                bouge=true;
                                this->setMode(CourbeSelectionne);
                            }
                            else if(items(approxProches(mouseEvent->scenePos())).contains(listeDesCourbesDans(objets).first())){
                                // Si on a selectionné le mur lui mÃÂªme...
                                partieSelectionneeC = BaseC;
                                bouge=true;
                                this->setMode(CourbeSelectionne);
                            }
                        }
                    }

                    if(getMode() == VueHaut::CourbeSelectionne)
                        bouge=true;

                    if(getMode() == VueHaut::Select){
                        foreach (Courbe *item, listeDesCourbesDans(items())) {
                            item->setPen(*penMurFini);
                            if(items().contains(pointCourbeUn))
                                removeItem(pointCourbeUn);
                            if(items().contains(pointCourbeDeux))
                                removeItem(pointCourbeDeux);
                        }
                    }
                    break;


                case ObjetSelectionne:

                    setMode(Select);

                    translation.setP1(mouseEvent->scenePos());
                    translation.setP2(mouseEvent->scenePos());


                    if(!objets.isEmpty()){

                        if(listeDesObjetsDans(objets).count() == 1){
                            //                            pointRotationObjet->setPos(listeDesObjetsDans(objets).first()->getRect().topRight());
                            //                            if(!this->items().contains(pointRotationObjet))
                            //                                this->addItem(pointRotationObjet);
                            this->setMode(ObjetSelectionne);
                            emit unObjetEstSelectionne();
                            emit angleObjetSelectModifie(listeDesObjetsDans(objets).first()->rotation());

                        }
                    }

                    break;

                case AjoutSurelevation:

                    // On crée un nouveau point a partir du curseur de la souris
                    QPointF *pointa;
                    pointa = new QPointF(mouseEvent->scenePos());

                    // On vérifie que l'on n'a pas rejoint le premier point
                    if(approxProches(*pointa).contains(surelevations.last()->getListeDesPoints()->first()->toQPoint())) {
                        if(surelevations.last()->getListeDesPoints()->count()>= 3) {
                            delete pointa;
                            foreach (QGraphicsEllipseItem *item, pointsSurelevation) {
                                if(this->items().contains(item))
                                    removeItem(item);
                                delete item;
                            }
                            pointsSurelevation.clear();
                            this->addItem(surelevations.last()->getGraphicsSurelevation());
                            //qDebug() << "Inspection des surelev : " << surelevations;
                            setMode(VueHaut::CreationSurelevation);
                            emit aucunMurEstSelectionne();
                            objets.clear();
                        }
                        else
                            qDebug() << "Il faut au moins trois points !";
                    }
                    else {
                        // On l'ajoute a la surélévation
                        surelevations.last()->ajouterUnPoint(pointa);

                        // Puis on l'affiche
                        QGraphicsEllipseItem *pta;
                        pta = new QGraphicsEllipseItem(approxProches(mouseEvent->scenePos()));
                        pointsSurelevation.append(pta);
                        this->addItem(pta);

                        setMode(VueHaut::AjoutSurelevation);
                    }
                    update();

                    break;

                case CreationSurelevation:

                    // On vide la lise de points affichés
                    foreach (QGraphicsEllipseItem *item, pointsSurelevation) {
                        if(this->items().contains(item))
                            removeItem(item);
                        delete item;
                    }
                    pointsSurelevation.clear();

                    // On crée une nouvelle surélevation
                    Surelevation *surelev;
                    surelev = new Surelevation;

                    // On l'ajoute a la liste des surélévations de la scene
                    surelevations.append(surelev);

                    // On crée un nouveau point a partir du curseur de la souris
                    QPointF *point;
                    point = new QPointF(mouseEvent->scenePos());

                    // On l'ajoute a la surélévation
                    surelev->ajouterUnPoint(point);

                    // Puis on l'affiche
                    QGraphicsEllipseItem *pt;
                    pt = new QGraphicsEllipseItem(approxProches(mouseEvent->scenePos()));
                    pointsSurelevation.append(pt);
                    this->addItem(pt);

                    setMode(VueHaut::AjoutSurelevation);
                    update();
                    break;

                case SurelevationSelectionne:
                    this->peindre(*penMurFini,this->items());
                    foreach (QGraphicsEllipseItem *item, pointsSurelevation) {
                        this->addItem(item);
                        if(approxProches(mouseEvent->scenePos()).contains(item->scenePos())){
                            item->setPen(*penMurSelectionne);
                        }
                    }
                    foreach (QPoint3D *item, *surelevations.last()->getListeDesPoints()) {
                        if(approxProches(mouseEvent->scenePos()).contains(item->toQPoint())){
                            pointSelection = item->toQPoint();
                        }

                    }
                    break;

                default:
                    ;
                }
                QGraphicsScene::mousePressEvent(mouseEvent);
            }
        }
        if (mouseEvent->button() == Qt::RightButton){
            // Si on a un clic droit, on affiche le menu contextuel

            if(nombreDElementsDans(objets) > 0){
                menuUnMur->exec(QPoint(mouseEvent->screenPos().x(),mouseEvent->screenPos().y()));
            }
        }
    }
    else {

        // Si la salle est verouillee :

        if (mouseEvent->button() == Qt::RightButton){
            if(nombreDeMursDans(objets) > 0){
                menuUnMurVerr->exec(QPoint(mouseEvent->screenPos().x(),mouseEvent->screenPos().y()));
            }
        }
        else {

            if(monMode == VueHaut::PlacementDepart){
                        centreCamera.setPos(mouseEvent->scenePos().x()-5,mouseEvent->scenePos().y()-5);
                        setMode(VueHaut::Select);


            }

            if(nombreDeMursDans(objets)==1 && murSelectionne()->isAffichable()){
                Mur *murSelect=murSelectionne();
                objets = items(approxProches(mouseEvent->scenePos()));
                objets.append(murSelect);
                if(objets.contains(rectDeux) && objets.contains(rectUn)){
                    murSelect->changerVueFace(false);
                    maFenetre->passerEnVueDeFace();}

                else if(objets.contains(rectUn)){
                    murSelect->changerVueFace(true);
                    maFenetre->passerEnVueDeFace();
                }
                else if(objets.contains(rectDeux)){
                    murSelect->changerVueFace(false);
                    maFenetre->passerEnVueDeFace();
                }
            }
            else {
                cacherRectFace();
                objets = items(approxProches(mouseEvent->scenePos()));

                if(nombreDeMursDans(objets)==0 && !objets.contains(rectUn) && !objets.contains(rectDeux)){
                    cacherRectFace();
                }
                foreach (Mur *mur, listeDesMursDans(objets)) {
                    //qDebug() << mur;
                }

                if(items().contains(mesure))
                    removeItem(mesure);
                peindre(*penMurFini, listeDesElementsDans(items()));
                // Si la selection n'est pas vide
                if(!objets.isEmpty()){
                    // Si il y a un ou plusieurs murs sélectionnés
                    if(nombreDeMursDans(objets) >= 1){

                        // On instancie un nouveau mur en le castant depuis la sélection
                        // puis on le colorie dans la couleur [sélectionné]
                        Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());
                        murSelect->setPen(*penMurSelectionne);

                        setMode(VueHaut::MurSelectionne);
                        afficherRectFace();
                        emit unMurEstSelectionne();

                    }
                    else if(nombreDeCourbesDans(objets) >= 1){

                        // On instancie un nouveau mur en le castant depuis la sélection
                        // puis on le colorie dans la couleur [sélectionné]
                        Courbe *courbeSelect = qgraphicsitem_cast<Courbe *>(listeDesCourbesDans(objets).first());
                        courbeSelect->setPen(*penMurSelectionne);

                        if(items().contains(pointCourbeUn))
                            removeItem(pointCourbeUn);
                        if(items().contains(pointCourbeDeux))
                            removeItem(pointCourbeDeux);

                        setMode(VueHaut::CourbeSelectionne);
                        // On ajoute la mesure du mur
                        emit unMurEstSelectionne();
                    }
                    else if(nombreDeSurelevationsDans(objets) >= 1) {
                        surelevEnCours = NULL;
                        selectPoint = NULL;

                        setMode(VueHaut::SurelevationSelectionne);

                        emit uneSurelevationEstSelectionnee();
                    }
                    else {
                        setMode(VueHaut::Select);
                        emit aucunMurEstSelectionne();
                        cacherRectFace();
                        objets.clear();
                    }
                }
                else {
                    objets.clear();
                    peindre(*penMurFini, listeDesElementsDans(items()));
                    cacherRectFace();
                    emit aucunMurEstSelectionne();
                }
            }
        }
    }
}

void VueHaut::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Mur *monMur;
    if(!isVerouille()){
        // Si on appuie sur CTRL
        if(monModificateur == this->CTRL){
            if(mouseEvent->button() == Qt::LeftButton)
                translation.setP2(mouseEvent->scenePos());
        }
        else {

            switch (monMode) {

            // -------------------------- Si on était en train de dessiner un mur --------

            case DessinMur:
                ligneDeMur->setP2(mouseEvent->scenePos());
                if(this->monModificateur == this->MAJ){
                    ligneDeMur->setAngle(this->getAngleBrique(ligneDeMur->angle()));
                    ligneDeMur->setLength(this->getLongueurBrique(ligneDeMur->length()));
                }
                if (!items().empty()) {
                    if(listeDesMursDans(items()).first()->type() == Mur::Type)
                    {
                        monMur = qgraphicsitem_cast<Mur *>(listeDesMursDans(items()).first());
                        //qDebug() <<" on opere en move sur " << monMur;
                        monMur->setLine(*ligneDeMur);
                        mesure->setPlainText(QString(QString::number(monMur->line().length()/echelle,'g',3)+" m"));
                        QPointF coord((monMur->line().x1()+monMur->line().x2())/2,(monMur->line().y1()+monMur->line().y2())/2);
                        mesure->setPos(coord);
                        QPointF *liaison = new QPointF(0,0);
                        foreach (QGraphicsItem *item, items()) {
                            if (item->type() == Mur::Type && item!=monMur){
                                if(monMur->finEstProche(*qgraphicsitem_cast<Mur *>(item),liaison)){
                                    ligneDeMur->setP2(*liaison);
                                    monMur->setLine(*ligneDeMur);
                                }
                            }
                            else if (item->type() == Courbe::Type && item!=monMur){
                                if(monMur->finEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison)){
                                    ligneDeMur->setP2(*liaison);
                                    monMur->setLine(*ligneDeMur);
                                }
                            }
                        }
                    }
                }
                break;

                // -------------------------- Si on était en train de dessiner une courbe --------

            case DessinCourbe:
                ligneDeMur->setP2(mouseEvent->scenePos());
                fantome->setLine(*ligneDeMur);

                foreach (QGraphicsItem *item, items()) {
                    if (item->type() == Mur::Type && item!=fantome){
                        QPointF *liaison = new QPointF(0,0);
                        if(fantome->finEstProche(*qgraphicsitem_cast<Mur *>(item),liaison)){
                            ligneDeMur->setP2(*liaison);
                            fantome->setLine(*ligneDeMur);
                        }
                    }
                    else if (item->type() == Courbe::Type && item!=fantome){
                        QPointF *liaison = new QPointF(0,0);
                        if(fantome->finEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison)){
                            ligneDeMur->setP2(*liaison);
                            fantome->setLine(*ligneDeMur);
                        }
                    }
                }

                break;
                // ------------------------ Si on avait sélectionné un mur -------------------

            case MurSelectionne:

                // Si la sélection n'est pas vide...
                if(!objets.isEmpty()){

                    // Si elle ne contient qu'un seul Mur
                    if((nombreDeMursDans(objets)==1 || superpose) && nombreDElementsDans(objets) == nombreDeMursDans(objets)){

                        // On récupÃÂ¨re le mur
                        Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());

                        // On définit le deuxiàme point de la translation
                        translation.setP2(mouseEvent->scenePos());
                        //                        this->afficherNormaleMurSelect();

                        QLineF clone = murSelect->line();
                        QLineF base = murSelect->line();
                        QPointF *liaison = new QPointF(0,0);

                        // On définit quelles translations / transformations va subir le mur en fonction de la partie sélectionnée
                        switch(partieSelectionnee){
                        case Debut:
                            clone.setP1(QPointF(base.x1()+(translation.x2()-translation.x1()),
                                                base.y1()+(translation.y2()-translation.y1())));
                            if(this->monModificateur == this->MAJ){
                                clone.setAngle(this->getAngleBrique(clone.angle()));
                            }
                            setModifing(true);
                            emit angleSelectModifie(clone.angle());
                            setModifing(false);
                            break;
                        case Fin:
                            clone.setP2(QPointF(base.x2()+(translation.x2()-translation.x1()),
                                                base.y2()+(translation.y2()-translation.y1())));
                            if(this->monModificateur == this->MAJ){
                                clone.setAngle(this->getAngleBrique(clone.angle()));
                            }
                            setModifing(true);
                            emit angleSelectModifie(clone.angle());
                            setModifing(false);
                            break;
                        case Base:
                            clone.setP1(QPointF(base.x1()+(translation.x2()-translation.x1()),
                                                base.y1()+(translation.y2()-translation.y1())));
                            clone.setP2(QPointF(base.x2()+(translation.x2()-translation.x1()),
                                                base.y2()+(translation.y2()-translation.y1())));
                            if(this->monModificateur == this->MAJ){
                                clone.setAngle(this->getAngleBrique(clone.angle()));
                            }
                            break;
                        default:

                            break;
                        }


                        // Gere l'opposition de résistance lors de l'éssai de déplacement d'un
                        // point magnétisé
                        if(force<100){
                            foreach (QGraphicsItem *item, listeDesMurs()) {
                                if (item!=murSelect)
                                {
                                    if(murSelect->finEstProche(*qgraphicsitem_cast<Mur *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Fin)){
                                        force++;
                                        clone.setP2(*liaison);
                                    }
                                    else if(murSelect->debutEstProche(*qgraphicsitem_cast<Mur *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Debut)){
                                        clone.setP1(*liaison);
                                        force++;
                                    }
                                }
                            }
                            foreach (QGraphicsItem *item, listeDesCourbes()) {
                                if (item!=murSelect)
                                {
                                    if(murSelect->finEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Fin)){
                                        force++;
                                        clone.setP2(*liaison);
                                    }
                                    else if(murSelect->debutEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Debut)){
                                        clone.setP1(*liaison);
                                        force++;
                                    }
                                }
                            }
                        }

                        // Dessine les petits rectangles sympathiques ornant l'extrémité d'un mur selectionné
                        if(partieSelectionnee == Debut){
                            selectPoint->setRect(cerclePoint(murSelect->line().p1()));

                        }
                        else if(partieSelectionnee == Fin){
                            selectPoint->setRect(cerclePoint(murSelect->line().p2()));
                        }



                        // Met a jour la position du mur
                        murSelect->setLine(clone);

                        // Change la longueur du mur dans la spinBox
                        emit longueurSelectModifiee(double(clone.length()/echelle));

                        // Dessine la mesure du mur
                        mesure->setPlainText(QString(QString::number(murSelect->line().length()/echelle,'g',3)+" m"));
                        QPointF coord((murSelect->line().x1()+murSelect->line().x2())/2,(murSelect->line().y1()+murSelect->line().y2())/2);
                        mesure->setPos(coord);

                        // Met a jour l'image
                        update();

                        // Mode : un ou plusieurs murs sont sélectionnés
                        setMode(VueHaut::MurSelectionne);

                        // On remet le premier point de la translation a la position du curseur
                        translation.setP1(mouseEvent->scenePos());

                    }
                    else if(nombreDElementsDans(objets) > 1) {

                        //                    setMode(VueHaut::ElementsSelectionnes);

                    }
                }
                break;

            case ElementsSelectionnesEnMouvement:

                translation.setP2(mouseEvent->scenePos());


                foreach (QGraphicsItem *item, listeDesElementsDans(objets)) {

                    if(item->type() == Mur::Type){
                        Mur *murSelect = qgraphicsitem_cast<Mur *>(item);
                        translation.setP2(mouseEvent->scenePos());
                        QLineF clone = murSelect->line();
                        QLineF base = murSelect->line();

                        clone.setP1(QPointF(base.x1()+(translation.x2()-translation.x1()),
                                            base.y1()+(translation.y2()-translation.y1())));
                        clone.setP2(QPointF(base.x2()+(translation.x2()-translation.x1()),
                                            base.y2()+(translation.y2()-translation.y1())));

                        murSelect->setLine(clone);
                    }
                    else if(item->type() == Courbe::Type){

                        Courbe *courbeSelect = qgraphicsitem_cast<Courbe *>(item);
                        translation.setP2(mouseEvent->scenePos());
                        update();
                        courbeSelect->bougerLesPoints(translation.dx(),translation.dy());

                        //delete cheminCourbe;
                        cheminCourbe = new QPainterPath(courbeSelect->getDebut());
                        cheminCourbe->cubicTo(courbeSelect->getPointUn(),courbeSelect->getPointDeux(),courbeSelect->getFin());
                        courbeSelect->setPath(*cheminCourbe);

                        if(items().contains(pointCourbeUn))
                            removeItem(pointCourbeUn);
                        if(items().contains(pointCourbeDeux))
                            removeItem(pointCourbeDeux);

                        pointCourbeUn->setRect(approxProches(courbeSelect->getPointUn()));
                        pointCourbeDeux->setRect(approxProches(courbeSelect->getPointDeux()));
                    }
                    else if(item->type() == QGraphicsSurelevationItem::Type){
                        QGraphicsSurelevationItem *surelev = qgraphicsitem_cast<QGraphicsSurelevationItem *>(item);
                        translation.setP2(mouseEvent->scenePos());
                        surelev->moveBy(translation.dx(), translation.dy());
                    }
                    update();
                    setMode(VueHaut::ElementsSelectionnesEnMouvement);
                }

                translation.setP1(mouseEvent->scenePos());

                break;

            case CourbeSelectionne:


                // Si la sélection n'est pas vide...
                if(!objets.isEmpty() && bouge){

                    // Si elle ne contient qu'une seule courbe
                    if(nombreDeCourbesDans(objets)==1 || superpose){
                        translation.setP2(mouseEvent->scenePos());
                        // On récupàre la courbe
                        Courbe *courbeSelect = listeDesCourbesDans(objets).first();
                        update();
                        // Dessine les petits rectangles sympathiques ornant l'extrémité d'une courbe selectionnée
                        if(partieSelectionneeC == DebutC){
                            selectPoint->setRect(cerclePoint(courbeSelect->getDebut()));
                            courbeSelect->setDebut(mouseEvent->scenePos());
                            partieSelectionnee=VueHaut::Debut;
                        }
                        else if(partieSelectionneeC == FinC){
                            selectPoint->setRect(cerclePoint(courbeSelect->getFin()));
                            courbeSelect->setFin(mouseEvent->scenePos());
                            partieSelectionnee=VueHaut::Fin;
                        }
                        else if(partieSelectionneeC == PointUn){
                            selectPoint->setRect(cerclePoint(courbeSelect->getPointUn()));
                            courbeSelect->setPointUn(mouseEvent->scenePos());
                        }
                        else if(partieSelectionneeC == PointDeux){
                            selectPoint->setRect(cerclePoint(courbeSelect->getPointDeux()));
                            courbeSelect->setPointDeux(mouseEvent->scenePos());
                        }
                        else if(partieSelectionneeC == BaseC){
                            courbeSelect->bougerLesPoints(translation.dx(), translation.dy());
                            partieSelectionnee=VueHaut::Base;
                        }
                        QPointF *liaison = new QPointF(0,0);
                        ligneDeMur->setPoints(courbeSelect->getDebut(),courbeSelect->getFin());
                        fantome->setLine(*ligneDeMur);

                        if(force<100){
                            foreach (QGraphicsItem *item, listeDesMurs()) {
                                if (item!=fantome)
                                {
                                    if(fantome->finEstProche(*qgraphicsitem_cast<Mur *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Fin)){
                                        force++;
                                        ligneDeMur->setP2(*liaison);
                                    }
                                    else if(fantome->debutEstProche(*qgraphicsitem_cast<Mur *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Debut)){
                                        ligneDeMur->setP1(*liaison);
                                        force++;
                                    }
                                }
                            }
                            foreach (QGraphicsItem *item, listeDesCourbes()) {
                                if (item!=courbeSelect)
                                {
                                    if(fantome->finEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Fin)){
                                        force++;
                                        ligneDeMur->setP2(*liaison);
                                    }
                                    else if(fantome->debutEstProche(*qgraphicsitem_cast<Courbe *>(item),liaison) &&
                                            (partieSelectionnee == Base || partieSelectionnee == Debut)){
                                        ligneDeMur->setP1(*liaison);
                                        force++;
                                    }
                                }
                            }

                        }
                        fantome->setLine(*ligneDeMur);
                        courbeSelect->setDebut(ligneDeMur->p1());
                        courbeSelect->setFin(ligneDeMur->p2());
                        update();
                        cheminCourbe = new QPainterPath(courbeSelect->getDebut());
                        update();
                        cheminCourbe->cubicTo(courbeSelect->getPointUn(),courbeSelect->getPointDeux(),courbeSelect->getFin());
                        update();
                        courbeSelect->setPath(*cheminCourbe);
                        update();

                        if(items().contains(pointCourbeUn))
                            removeItem(pointCourbeUn);
                        if(items().contains(pointCourbeDeux))
                            removeItem(pointCourbeDeux);

                        update();
                        pointCourbeUn->setRect(approxProches(courbeSelect->getPointUn()));
                        pointCourbeDeux->setRect(approxProches(courbeSelect->getPointDeux()));
                        this->addItem(pointCourbeUn);
                        this->addItem(pointCourbeDeux);

                        update();
                        translation.setP1(mouseEvent->scenePos());

                        // Mode : un ou plusieurs murs sont sélectionnés
                        setMode(VueHaut::CourbeSelectionne);

                    }
                    else if(nombreDElementsDans(objets) > 1) {

                        translation.setP2(mouseEvent->scenePos());
                        foreach (QGraphicsItem *item, listeDesCourbesDans(objets)) {

                            Courbe *courbeSelect = qgraphicsitem_cast<Courbe *>(item);
                            translation.setP2(mouseEvent->scenePos());
                            Courbe clone = *courbeSelect;
                            Courbe base = *courbeSelect;

                            clone.setDebut(QPointF(base.getDebut().x()+(translation.x2()-translation.x1()),
                                                   base.getDebut().y()+(translation.y2()-translation.y1())));
                            clone.setFin(QPointF(base.getFin().x()+(translation.x2()-translation.x1()),
                                                 base.getFin().y()+(translation.y2()-translation.y1())));
                            clone.setPointUn(QPointF(base.getPointUn().x()+(translation.x2()-translation.x1()),
                                                     base.getPointUn().y()+(translation.y2()-translation.y1())));
                            clone.setPointDeux(QPointF(base.getPointDeux().x()+(translation.x2()-translation.x1()),
                                                       base.getPointDeux().y()+(translation.y2()-translation.y1())));

                            *courbeSelect=clone;
                            update();
                            setMode(VueHaut::CourbeSelectionne);

                        }
                        translation.setP1(mouseEvent->scenePos());
                    }
                }
                break;

            case ObjetSelectionne:

                if(!objets.isEmpty()){

                    Objet3D *objetSelect = listeDesObjetsDans(objets).first();


                    if(listeDesObjetsDans(objets).count() == 1){

                        emit angleObjetSelectModifie(objetSelect->rotation());
                        translation.setP2(mouseEvent->scenePos());
                        objetSelect->moveBy(translation.dx(), translation.dy());
                        translation.setP1(mouseEvent->scenePos());

                        update();


                    }
                }

                break;

            case PointControleSelectionne:

                if(!objets.isEmpty()){

                    Courbe *courbeSelect = listeDesCourbesDans(objets).first();
                    //                    if(cheminCourbe != NULL)
                    //                    delete cheminCourbe;
                    cheminCourbe = new QPainterPath(courbeSelect->getDebut());

                    if(listeDesCourbesDans(objets).count() == 1){
                        if(unDeux) {
                            courbeSelect->setPointUn(mouseEvent->scenePos());
                        }
                        else {
                            courbeSelect->setPointDeux(mouseEvent->scenePos());
                        }

                        cheminCourbe->cubicTo(courbeSelect->getPointUn(),courbeSelect->getPointDeux(),courbeSelect->getFin());
                        courbeSelect->setPath(*cheminCourbe);

                        if(items().contains(pointCourbeUn))
                            removeItem(pointCourbeUn);
                        if(items().contains(pointCourbeDeux))
                            removeItem(pointCourbeDeux);

                        pointCourbeUn->setRect(approxProches(courbeSelect->getPointUn()));
                        pointCourbeDeux->setRect(approxProches(courbeSelect->getPointDeux()));
                        this->addItem(pointCourbeUn);
                        this->addItem(pointCourbeDeux);

                        update();


                    }
                }

                break;

                // Si on a cliqué sur une surelevation

            case SurelevationSelectionne:

                // Si la sélection n'est pas vide...
                if(!objets.isEmpty()){

                    // Si elle ne contient qu'une seule Surélévation
                    if((nombreDeSurelevationsDans(objets)==1) && nombreDElementsDans(objets) == nombreDeSurelevationsDans(objets)){


                        translation.setP2(mouseEvent->scenePos());
                        if(surelevEnCours != NULL) {
                            surelevEnCours->moveTo(translation);
                            surelevEnCours->getGraphicsSurelevation()->setPen(*penMurSelectionne);
                            surelevEnCours->majSurelevation();
                        }

                        // Met a jour l'image
                        update();
                        setMode(VueHaut::SurelevationSelectionne);
                        // On remet le premier point de la translation a la position du curseur
                        translation.setP1(mouseEvent->scenePos());

                    }
                }

                break;

            case PointSurelevationSelectionne:

                if(pointSurelev != NULL) {
                    pointSurelev->setPos(mouseEvent->scenePos());

                    if(selectPoint != NULL)
                        selectPoint->setRect(approxProches(pointSurelev->toQPoint()));
                    else
                        selectPoint = new QGraphicsRectItem(approxProches(pointSurelev->toQPoint()));
                    if(!items().contains(selectPoint))
                        addItem(selectPoint);

                    QPointF pointSup, pointInf;
                    int i=0;
                    foreach (QPoint3D *pt, *surelevEnCours->getListeDesPoints()) {
                        if(pt == pointSurelev){
                            //qDebug() << "On a trouvé le point cliqué ! pos = " << i ;
                            if(surelevEnCours->getListeDesPoints()->size()-1 == i){
                                pointSup = surelevEnCours->getListeDesPoints()->at(0)->toQPoint();
                            }
                            else {
                                pointSup = surelevEnCours->getListeDesPoints()->at(i+1)->toQPoint();
                            }

                            if(i == 0){
                                pointInf = surelevEnCours->getListeDesPoints()->last()->toQPoint();
                            }
                            else {
                                pointInf = surelevEnCours->getListeDesPoints()->at(i-1)->toQPoint();
                            }
                        }
                        i++;
                    }
                    mesure->setPlainText(QString(QString::number(QLineF(pointSurelev->toQPoint(),pointSup).length()/echelle,'g',3)+" m"));
                    QPointF coord((QLineF(pointSurelev->toQPoint(),pointSup).x1()+QLineF(pointSurelev->toQPoint(),pointSup).x2())/2,
                                  (QLineF(pointSurelev->toQPoint(),pointSup).y1()+QLineF(pointSurelev->toQPoint(),pointSup).y2())/2);
                    mesure->setPos(coord);

                    mesurebis->setPlainText(QString(QString::number(QLineF(pointSurelev->toQPoint(),pointInf).length()/echelle,'g',3)+" m"));
                    QPointF coordbis((QLineF(pointSurelev->toQPoint(),pointInf).x1()+QLineF(pointSurelev->toQPoint(),pointInf).x2())/2,
                                     (QLineF(pointSurelev->toQPoint(),pointInf).y1()+QLineF(pointSurelev->toQPoint(),pointInf).y2())/2);
                    mesurebis->setPos(coordbis);

                    if(!this->items().contains(mesure))
                        addItem(mesure);
                    if(!this->items().contains(mesurebis))
                        addItem(mesurebis);


                }

                surelevEnCours->majSurelevation();
                break;


                // Si on est en train de dessiner une zone de sélection
            case SelectionEnCours:


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
                this->appliquerTraits();
                if(!listeDesElementsDans(objets).isEmpty()){
                    this->peindre(*penMurSelectionne, objets);
                    setMode(VueHaut::SelectionEnCours);
                }



                break;

            case AjoutSurelevation:

                break;

            case CreationSurelevation:

                break;


            default:
                ;
            }
        }

        // Si on appuie sur CTRL (enelever le mouseevent dans la condition pour un resultat approximatif)
        if(monModificateur == this->CTRL && mouseEvent->button() == Qt::LeftButton){

            this->deplacement(mouseEvent->scenePos());
            translation.setP1(mouseEvent->scenePos());
        }
    }
    else {
        if(indicateurActif){
            // Si la salle est verouillee
            if(listeDesMursDans(items(approxProches(mouseEvent->scenePos()))).count() >0){
                if(murApercuIndic == 0 || murApercuIndic != listeDesMursDans(items(approxProches(mouseEvent->scenePos()))).first()){
                    int nb=0;
                    murApercuIndic = listeDesMursDans(items(approxProches(mouseEvent->scenePos()))).first();
                    QString msg="";
                    foreach (QGraphicsPixmapItem *px, apercusIndicateur) {
                        if(items().contains(px))
                            removeItem(px);
                        delete px;
                        update();
                    }
                    apercusIndicateur.clear();
                    update();
                    foreach (Mur *mur, listeDesMursDans(items(approxProches(mouseEvent->scenePos())))) {
                        nb=mur->getPremiereVueFace()->listeDesTableaux().count()+mur->getDeuxiemeVueFace()->listeDesTableaux().count();
                        if(nb > 1){
                            msg += QString("\nCe mur contient ") + QString::number(nb) + QString(" tableaux");

                            double offset=0;
                            foreach (Tableau *tabPre, mur->getPremiereVueFace()->listeDesTableaux()) {
                                QPixmap pix = tabPre->pixmap();
                                pix = pix.scaledToHeight(40,Qt::SmoothTransformation);
                                QGraphicsPixmapItem *pixm = new QGraphicsPixmapItem(pix);
                                pixm->setPos(mouseEvent->scenePos().x()+offset,mouseEvent->scenePos().y()-50);
                                offset+=pixm->pixmap().width()+1;
                                pixm->show();
                                addItem(pixm);
                                this->update();
                                apercusIndicateur.append(pixm);
                            }
                            foreach (Tableau *tabDeu, mur->getDeuxiemeVueFace()->listeDesTableaux()) {
                                QPixmap pix = tabDeu->pixmap();
                                pix = pix.scaledToHeight(40,Qt::SmoothTransformation);
                                QGraphicsPixmapItem *pixm = new QGraphicsPixmapItem(pix);
                                pixm->setPos(mouseEvent->scenePos().x()+offset,mouseEvent->scenePos().y()-50);
                                offset+=pixm->pixmap().width()+1;
                                pixm->show();
                                addItem(pixm);
                                this->update();
                                apercusIndicateur.append(pixm);
                            }
                        }
                        else if(nb == 1){
                            double offset=0;
                            msg += QString("\nCe mur contient ") + QString::number(nb) + QString(" tableau");
                            foreach (Tableau *tabPre, mur->getPremiereVueFace()->listeDesTableaux()) {
                                QPixmap pix = tabPre->pixmap();
                                pix = pix.scaledToHeight(40,Qt::SmoothTransformation);
                                QGraphicsPixmapItem *pixm = new QGraphicsPixmapItem(pix);
                                pixm->setPos(mouseEvent->scenePos().x()+offset,mouseEvent->scenePos().y()-50);
                                offset+=pixm->pixmap().width()+1;
                                pixm->show();
                                addItem(pixm);
                                this->update();
                                apercusIndicateur.append(pixm);
                            }
                            foreach (Tableau *tabDeu, mur->getDeuxiemeVueFace()->listeDesTableaux()) {
                                QPixmap pix = tabDeu->pixmap();
                                pix = pix.scaledToHeight(40,Qt::SmoothTransformation);
                                QGraphicsPixmapItem *pixm = new QGraphicsPixmapItem(pix);
                                pixm->setPos(mouseEvent->scenePos().x()+offset,mouseEvent->scenePos().y()-50);
                                offset+=pixm->pixmap().width()+1;
                                pixm->show();
                                addItem(pixm);
                                this->update();
                                apercusIndicateur.append(pixm);
                            }
                        }
                        else
                            msg += QString("\nCe mur ne contient aucun tableau");
                    }
                    indicateurMur.setPlainText(msg);
                    indicateurMur.show();
                    indicateurMur.setPos(mouseEvent->scenePos());
                    if(!items().contains(&indicateurMur))
                        addItem(&indicateurMur);
                }
                else {
                    double offset = 0;
                    int k=0;
                    qDebug() << "apercus = " << apercusIndicateur.count();

                    foreach (Mur *mur, listeDesMursDans(items(approxProches(mouseEvent->scenePos())))) {
                        foreach (Tableau *tabPre, mur->getPremiereVueFace()->listeDesTableaux()) {
                            apercusIndicateur.at(k)->setPixmap(tabPre->pixmap().scaledToHeight(40,Qt::SmoothTransformation));
                            apercusIndicateur.at(k)->setPos(mouseEvent->scenePos().x()+offset,mouseEvent->scenePos().y()-50);
                            offset+=apercusIndicateur.at(k)->pixmap().width()+1;
                            k++;
                        }
                        foreach (Tableau *tabDeu, mur->getDeuxiemeVueFace()->listeDesTableaux()) {
                            apercusIndicateur.at(k)->setPixmap(tabDeu->pixmap().scaledToHeight(40,Qt::SmoothTransformation));
                            apercusIndicateur.at(k)->setPos(mouseEvent->scenePos().x()+offset,mouseEvent->scenePos().y()-50);
                            offset+=apercusIndicateur.at(k)->pixmap().width()+1;
                            k++;
                        }
                    }

                    indicateurMur.setPos(mouseEvent->scenePos());
                    update();
                }
            }
            else {
                indicateurMur.hide();
                murApercuIndic = 0;
                if(items().contains(&indicateurMur))
                    removeItem(&indicateurMur);
                foreach (QGraphicsPixmapItem *px, apercusIndicateur) {
                    if(items().contains(px))
                        removeItem(px);
                    delete px;
                    update();
                }
                apercusIndicateur.clear();
            }
        }
    }

    // partie experimentale de comptage de tableaux




}

void VueHaut::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<murSelectionne();
    qDebug()<<monMode;
    this->appliquerTraits();
    if(!isVerouille()){

        // Si on appuie sur CTRL
        if(monModificateur == this->CTRL){
            translation.setPoints(mouseEvent->scenePos(), mouseEvent->scenePos());
        }
        else {
            Mur *monMur;
            force=0;
            if(this->items().contains(selectPoint))
                this->removeItem(selectPoint);
            if(this->items().contains(mesure))
                this->removeItem(mesure);
            if(this->items().contains(mesurebis))
                this->removeItem(mesurebis);
            switch (monMode) {


            case DessinMur:
                emit sceneModifiee();
                if(this->monModificateur == this->MAJ){
                    ligneDeMur->setAngle(this->getAngleBrique(ligneDeMur->angle()));
                    ligneDeMur->setLength(this->getLongueurBrique(ligneDeMur->length()));
                }
                if (!this->items().empty()) {
                    if(listeDesMursDans(items()).first()->type() == Mur::Type)
                    {
                        monMur =
                                qgraphicsitem_cast<Mur *>(listeDesMursDans(items()).first());
                        monMur->setLine(*ligneDeMur);
                        monMur->getPremiereVueFace()->setMurCourant(monMur);
                        monMur->getDeuxiemeVueFace()->setMurCourant(monMur);
                        QPointF *liaison = new QPointF(0,0);
                        foreach (QGraphicsItem *item, items()) {
                            if (item->type() == Mur::Type && item!=monMur){
                                if(monMur->finEstProche(*qgraphicsitem_cast<Mur *>(item),liaison)){
                                    ligneDeMur->setP2(*liaison);
                                    monMur->setLine(*ligneDeMur);

                                }
                            }
                        }
                        monMur->setPen(*penMurFini);
                        if(monMur->isMobile()){
                            monMur->setPen(*penMurMobile);
                        }
                        else if(!monMur->isAffichable()){
                            monMur->setPen(*penMurNonAffichable);
                        }

                        setMode(VueHaut::AjoutMur);

                    }
                }

                emit sceneChangee();
                break;

            case DessinCourbe:
                emit sceneModifiee();
                Courbe *courbeEnCour;
                courbeEnCour = new Courbe();
                courbeEnCour->setDebut(ligneDeMur->p1());
                courbeEnCour->setFin(ligneDeMur->p2());
                courbeEnCour->setPointUn(QPointF(((((fantome->line().x1()+fantome->line().x2())/2)+fantome->line().x1())/2),((((fantome->line().y1()+fantome->line().y2())/2)+fantome->line().y1())/2)));
                courbeEnCour->setPointDeux(QPointF(((((fantome->line().x1()+fantome->line().x2())/2)+fantome->line().x2())/2),((((fantome->line().y1()+fantome->line().y2())/2)+fantome->line().y2())/2)));

                pointCourbeUn->setRect(approxProches(courbeEnCour->getPointUn()));
                pointCourbeDeux->setRect(approxProches(courbeEnCour->getPointDeux()));
                this->addItem(pointCourbeUn);
                this->addItem(pointCourbeDeux);
                if(cheminCourbe!=NULL)
                    delete cheminCourbe;
                cheminCourbe=new QPainterPath(courbeEnCour->getDebut());
                cheminCourbe->cubicTo(courbeEnCour->getPointUn(),courbeEnCour->getPointDeux(),courbeEnCour->getFin());
                this->removeItem(fantome);
                courbeEnCour->setPath(*cheminCourbe);
                this->addItem(courbeEnCour);
                monMode = AjoutCourbe;


                emit sceneChangee();
                break;

            case MurSelectionne:
                setMode(VueHaut::Select);

                if(partieSelectionnee == Debut || partieSelectionnee == Fin){
                    this->removeItem(selectPoint);
                }


                if(this->items().contains(mesure))
                    this->removeItem(mesure);
                if(!objets.isEmpty()){
                    if((nombreDeMursDans(objets)==1 || superpose)){
                        emit sceneModifiee();
                        Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());
                        emit murAffichable(murSelect->isAffichable());
                        emit murMobile(murSelect->isMobile());
                        superpose=false;
                    }
                }
                break;

            case ObjetSelectionne:
                setMode(VueHaut::Select);

                break;

            case ElementsSelectionnesEnMouvement:
                setMode(VueHaut::Select);

                if(partieSelectionnee == Debut || partieSelectionnee == Fin){
                    this->removeItem(selectPoint);
                }


                if(this->items().contains(mesure))
                    this->removeItem(mesure);
                emit sceneModifiee();

                emit sceneChangee();
                break;

            case ElementsSelectionnes:
                setMode(VueHaut::Select);

                if(partieSelectionnee == Debut || partieSelectionnee == Fin){
                    if(this->items().contains(selectPoint))
                        this->removeItem(selectPoint);
                }


                if(this->items().contains(mesure))
                    this->removeItem(mesure);
                emit sceneModifiee();
                break;

            case CourbeSelectionne:
                bouge=false;

                if(partieSelectionneeC == DebutC || partieSelectionneeC == FinC || partieSelectionneeC == PointUn || partieSelectionneeC == PointDeux)
                    this->removeItem(selectPoint);

                if(!objets.isEmpty()){
                    if((nombreDeCourbesDans(objets)==1 || superpose)){
                        emit sceneModifiee();
                        superpose=false;
                    }
                }
                else
                    setMode(VueHaut::Select);

                break;

            case PointControleSelectionne:

                if(partieSelectionneeC == DebutC || partieSelectionneeC == FinC || partieSelectionneeC == PointUn || partieSelectionneeC == PointDeux){
                    this->removeItem(selectPoint);
                }
                setMode(VueHaut::CourbeSelectionne);
                break;

            case SelectionEnCours:

                // On nettoye un peu...
                if(this->items().contains(&graphiqueSelection))
                    removeItem(&graphiqueSelection);
                this->appliquerTraits();

                if(nombreDElementsDans(objets) == 0){
                    setMode(VueHaut::Select);
                    peindre(*penMurFini, this->items());
                    emit aucunMurEstSelectionne();
                }
                else if(nombreDeMursDans(objets) == 2){
                    setMode(VueHaut::MursSelectionnes);
                    emit deuxMursSontSelectionnes();

                    Mur *murSelectUn = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());
                    Mur *murSelectDeux = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).last());

                    QLineF cloneUn = murSelectUn->line();
                    QLineF cloneDeux = murSelectDeux->line();
                    int angle;
                    if(cloneDeux.angle() < cloneUn.angle())
                        angle = abs((360-int(murSelectUn->line().angle()-murSelectDeux->line().angle()))%360);
                    else angle = abs(int(murSelectUn->line().angle()-murSelectDeux->line().angle())%360);

                    if(cloneUn.p1()==cloneDeux.p2())
                        angle=(angle-180)%360;
                    if(cloneUn.p2()==cloneDeux.p1())
                        angle=(angle+180)%360;


                    setModifing(true);
                    emit angleSelectModifie(angle);
                    setModifing(false);
                }
                else if(nombreDeMursDans(objets)==1 && nombreDElementsDans(objets)==1) {
                    //qDebug() << "La sélection ne comporte qu'un seul mur : " << nombreDElementsDans(objets);
                    setMode(VueHaut::Select);

                    emit unMurEstSelectionne();

                }
                else if(nombreDeCourbesDans(objets)==1 && nombreDElementsDans(objets)==1) {
                    //qDebug() << "La sélection ne comporte qu'une seul courbe : " << nombreDElementsDans(objets);
                    setMode(VueHaut::CourbeSelectionne);

                    //                emit unMurEstSelectionne();

                }
                else if(nombreDElementsDans(objets)>2) {
                    //qDebug() << "Ouah ! on a pleins d'objets ! : " << nombreDElementsDans(objets);
                    setMode(VueHaut::ElementsSelectionnes);

                    emit desMursSontSelectionnes();

                }
                else {
                    //qDebug() << "[else] objets au relachement : " << nombreDElementsDans(objets);
                    setMode(VueHaut::ElementsSelectionnes);

                    emit desMursSontSelectionnes();

                }
                break;

            case AjoutSurelevation:

                break;

            case CreationSurelevation:

                break;

            case SurelevationSelectionne:
                setMode(VueHaut::Select);
                emit uneSurelevationEstSelectionnee();
                break;

            case PointSurelevationSelectionne:

                if(items().contains(selectPoint))
                    removeItem(selectPoint);
                pointSurelev = NULL;
                setMode(VueHaut::Select);

                if(this->items().contains(mesure))
                    removeItem(mesure);
                if(this->items().contains(mesurebis))
                    removeItem(mesurebis);

                break;

            default:
                ;
            }

        }
    }
    else {
        // Si la salle est verouillee
    }
}

void VueHaut::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){

}

void VueHaut::setMode(Mode mode) {
    monMode = mode;
    //qDebug() << "mode = " << mode;
}

void VueHaut::setLongueurMurSelect(double longueur){
    if(!objets.isEmpty()){
        if(nombreDeMursDans(objets)==1){
            Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());
            QLineF clone = murSelect->line();
            clone.setLength(qreal(longueur*echelle));
            murSelect->setLine(clone);
            emit sceneModifiee();
        }
    }
}

void VueHaut::setAngleMurSelect(int angle){
    if(!objets.isEmpty()){
        if(nombreDeMursDans(objets)==1){
            Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());
            QLineF clone = murSelect->line();
            clone.setAngle(angle);
            murSelect->setLine(clone);
            emit sceneModifiee();
            //qDebug() << "l'angle a été modifié !";
        }
    }
}

void VueHaut::setAngleObjetSelect(int angle){
    if(!objets.isEmpty()){
        if(nombreDObjetsDans(objets)==1){
            Objet3D *objetSelect = qgraphicsitem_cast<Objet3D *>(listeDesObjetsDans(objets).first());
            //            objetSelect->resetTransform();
            //            emit angleObjetSelectModifie(int(objetSelect->rotation()));
            qDebug() << "rotate de : " << angle;
            objetSelect->setRotation(objetSelect->rotation() + angle);
            emit sceneModifiee();
            //qDebug() << "l'angle a été modifié !";
        }
    }
}

void VueHaut::setAngleEntreDeuxMurs(int angle){
    if(!objets.isEmpty() && !getModifing()){
        if(nombreDeMursDans(objets)==2){
            Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).at(0));
            Mur *deuxiemeMurSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).at(1));
            QLineF cloneUn = murSelect->line();
            QLineF cloneDeux = deuxiemeMurSelect->line();
            if(cloneUn.p2()==cloneDeux.p2()||cloneUn.p2()==cloneDeux.p1())
            {
                QLineF change=cloneUn;
                cloneUn.setP2(change.p1());
                cloneUn.setP1(change.p2());
            }
            if(cloneDeux.p2()==cloneUn.p2()||cloneDeux.p2()==cloneUn.p1())
            {
                QLineF change=cloneDeux;
                cloneDeux.setP2(change.p1());
                cloneDeux.setP1(change.p2());
            }

            cloneDeux.setAngle(angle+cloneUn.angle());
            deuxiemeMurSelect->setLine(cloneDeux);
            emit sceneModifiee();
            //qDebug() << "l'angle a été modifié !";
        }
    }
}

void VueHaut::supprimerMurSelect(){
    if(!objets.isEmpty()){
        foreach (QGraphicsItem *item, listeDesElementsDans(objets)) {
            if(item->type() == QGraphicsSurelevationItem::Type){
                QGraphicsSurelevationItem *it = qgraphicsitem_cast<QGraphicsSurelevationItem *>(item);
                this->surelevations.removeOne(it->getSurelevation());
                delete it->getSurelevation();
            }
            this->removeItem(item);
        }
        this->removeItem(mesure);
    }
    emit aucunMurEstSelectionne();
    emit sceneModifiee();
    objets.clear();
}

void VueHaut::setMurSelectMobile(bool mobile){
    if(!objets.isEmpty()){
        foreach (QGraphicsItem *item, listeDesMursDans(objets)) {


            Mur *murSelect = qgraphicsitem_cast<Mur *>(item);
            murSelect->setMobile(mobile);
            if(mobile == true){
                murSelect->setPen(*penMurMobile);
            }
            else {
                murSelect->setPen(*penMurSelectionne);
            }
        }
        emit sceneModifiee();
    }
}

void VueHaut::setMurSelectAffichable(bool affichable){
    if(!objets.isEmpty()){
        foreach (QGraphicsItem *item, listeDesMursDans(objets)) {


            Mur *murSelect = qgraphicsitem_cast<Mur *>(item);
            murSelect->setAffichable(affichable);
            if(affichable == false){
                murSelect->setPen(*penMurNonAffichable);
            }
            else {
                murSelect->setPen(*penMurSelectionne);
            }
        }
        emit sceneModifiee();
    }
}

QList<Mur *> VueHaut::listeDesMurs(){
    QList<Mur *> liste;

    if(!items().isEmpty()){
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == Mur::Type){
                liste.append(qgraphicsitem_cast<Mur *>(item));
            }
        }
    }
    return liste;
}

QList<Courbe *> VueHaut::listeDesCourbes(){
    QList<Courbe *> liste;

    if(!items().isEmpty()){
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == Courbe::Type){
                liste.append(qgraphicsitem_cast<Courbe *>(item));
            }
        }

    }
    return liste;
}

void VueHaut::viderObjets(){
    objets.clear();
    foreach (QGraphicsItem *item, items()) {
        delete item;
    }
}

bool VueHaut::contientMurs(){
    QList<Mur *> lst = this->listeDesMurs();
    if(lst.count()>0)
        return true;
    else
        return false;
}

void VueHaut::copierContenu(){
    qDebug()<< "this :" << this;
    qDebug()<< "fentre vh :" << getFenetre()->getVueHaut();
    qDebug()<< "objet fenetre :"<< getFenetre()->getVueHaut()->getObjets();
    this->viderPressePapier();

    bool content = false;
    if(!items().isEmpty()){
        qDebug()<<"###################### Copier";
        qDebug()<<"mur::type :" << Mur::Type;
        if(!getFenetre()->getVueHaut()->getObjets().isEmpty())
            foreach (QGraphicsItem *item, getFenetre()->getVueHaut()->getObjets()) {
                if (item->type() == Mur::Type){
                    qDebug()<<"mur" << item->type() ;
                    Mur *murCopie=new Mur(*qgraphicsitem_cast<Mur *>(item));

                    pressePapier.append(murCopie);
                    content = true;
                }
            }
        qDebug()<<pressePapier;
    }
    if(content){
        emit elementAColler();
    }
}

void VueHaut::couperContenu(){
    this->viderPressePapier();
    bool content = false;
    if(!items().isEmpty()){
        qDebug()<<"###################### Couper";
        qDebug()<< Mur::Type;
        qDebug()<< getFenetre()->getVueHaut()->getObjets();
        if(!getFenetre()->getVueHaut()->getObjets().isEmpty())
            foreach (QGraphicsItem *item, getFenetre()->getVueHaut()->getObjets()) {
                //qDebug()<<item->type();
                if (item->type() == Mur::Type){
                    qDebug()<<"mur";
                    pressePapier.append(item);
                    this->removeItem(item);
                    content = true;
                }
            }
        qDebug()<<pressePapier;
    }
    if(content){
        emit elementAColler();
    }
    getFenetre()->getVueHaut()->getObjets().clear();
    emit sceneChangee();

}

void VueHaut::collerContenu(){
    if(!pressePapier.isEmpty()){
        qDebug()<<"###################### Coller";
        foreach (QGraphicsItem *item, pressePapier) {
            if (item->type() == Mur::Type){
                qDebug()<<"mur";
                Mur *contenu = new Mur(*qgraphicsitem_cast<Mur *>(item));
                getFenetre()->getVueHaut()->addItem(contenu);
                contenu->setPos(contenu->x()-decalageCopie, contenu->y()-decalageCopie);
            }
        }
        qDebug()<<pressePapier;
    }
    this->appliquerTraits();
    this->update();
}

void VueHaut::viderPressePapier(){
    if(!pressePapier.isEmpty()){
        foreach (QGraphicsItem *item, pressePapier) {
            pressePapier.removeOne(item);
            delete item;
        }
        pressePapier.clear();
    }
}

void VueHaut::appliquerTraits(){
    foreach (QGraphicsItem *item, items()) {
        if (item->type() == Mur::Type){
            Mur *mur = qgraphicsitem_cast<Mur *>(item);
            if(objets.contains(mur)){
                mur->setPen(*penMurSelectionne);
            }
            else {
                if(mur->isMobile())
                    mur->setPen(*penMurMobile);
                if(!mur->isAffichable())
                    mur->setPen(*penMurNonAffichable);
                if(!mur->isMobile() && mur->isAffichable())
                    mur->setPen(*penMurFini);
            }

        }
    }
}

int VueHaut::nombreDeMursDans(QList<QGraphicsItem *> lst){
    int nb=0;
    if(!lst.isEmpty())
        foreach (QGraphicsItem *item, lst) {
            if(item->type() == Mur::Type)
                nb++;
        }
    return nb;
}

int VueHaut::nombreDeCourbesDans(QList<QGraphicsItem *> lst){
    int nb=0;
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Courbe::Type)
            nb++;
    }
    return nb;
}


int VueHaut::nombreDeSurelevationsDans(QList<QGraphicsItem *> lst) {
    int nb=0;
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == QGraphicsSurelevationItem::Type)
            nb++;
    }
    return nb;
}

int VueHaut::nombreDObjetsDans(QList<QGraphicsItem *> lst){
    int nb=0;
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == typeObjet3D)
            nb++;
    }
    return nb;
}

QList<QGraphicsSurelevationItem *> VueHaut::listeDesSurelevationsDans(QList<QGraphicsItem *> lst){
    QList<QGraphicsSurelevationItem *> liste;
    liste.clear();
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == QGraphicsSurelevationItem::Type)
            liste.append(qgraphicsitem_cast<QGraphicsSurelevationItem *>(item));
    }
    return liste;
}

int VueHaut::nombreDElementsDans(QList<QGraphicsItem *> lst){
    int nb=0;
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Courbe::Type)
            nb++;
        else if(item->type() == Mur::Type)
            nb++;
        else if(item->type() == QGraphicsSurelevationItem::Type)
            nb++;
        else if(item->type() == typeObjet3D)
            nb++;
    }
    return nb;
}

QList<Mur *> VueHaut::listeDesMursDans(QList<QGraphicsItem *> lst){
    QList<Mur *> liste;
    liste.clear();
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Mur::Type)
            liste.append(qgraphicsitem_cast<Mur *>(item));
    }
    return liste;
}

QList<Courbe *> VueHaut::listeDesCourbesDans(QList<QGraphicsItem *> lst){
    QList<Courbe *> liste;
    liste.clear();
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Courbe::Type)
            liste.append(qgraphicsitem_cast<Courbe *>(item));
    }
    return liste;
}

QList<Objet3D *> VueHaut::listeDesObjetsDans(QList<QGraphicsItem *> lst){
    QList<Objet3D *> liste;
    liste.clear();
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == typeObjet3D)
            liste.append(qgraphicsitem_cast<Objet3D *>(item));
    }
    return liste;
}

QList<QGraphicsItem *> VueHaut::listeDesElementsDans(QList<QGraphicsItem *> lst) {
    QList<QGraphicsItem *> liste;
    liste.clear();
    foreach (QGraphicsItem *item, lst) {
        if(item->type() == Courbe::Type)
            liste.append(qgraphicsitem_cast<Courbe *>(item));
        else if(item->type() == Mur::Type)
            liste.append(qgraphicsitem_cast<Mur *>(item));
        else if(item->type() == QGraphicsSurelevationItem::Type)
            liste.append(qgraphicsitem_cast<QGraphicsSurelevationItem *>(item));
        else if(item->type() == typeObjet3D)
            liste.append(qgraphicsitem_cast<Objet3D *>(item));
    }
    return liste;
}

void VueHaut::keyPressEvent(QKeyEvent *event){

    switch(event->key()){
    case Qt::Key_Shift:
        monModificateur = this->MAJ;
        //qDebug() << "Touche Maj pressée";
        break;
    case Qt::Key_Control:
        monModificateur = this->CTRL;
        //qDebug() << "Touche Ctrl pressée";
        break;
    case Qt::Key_Delete:
        foreach (Mur *mur, listeDesMursDans(objets)) {
            removeItem(mur);
        }
        break;
    default:
        break;

    }
}

void VueHaut::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Shift:
        monModificateur = this->Aucun;
        //qDebug() << "Touche Maj relÃ¢chée";
        break;
    case Qt::Key_Control:
        monModificateur = this->Aucun;
        //qDebug() << "Touche Ctrl relÃ¢chée";
        break;
    default:
        break;

    }
}

VueHaut::Modificateur VueHaut::getModificateur(){
    return monModificateur;
}

void VueHaut::setModificateur(Modificateur mod){
    this->monModificateur = mod;
}

int VueHaut::getAngleBrique(const qreal angle) const {
    int angleRetour = 0;
    if(angle > 0.0 && angle <= 22.5)
        angleRetour = 0;
    else if(angle > 22.5 && angle <= 67.5)
        angleRetour = 45;
    else if(angle > 67.5 && angle <= 112.5)
        angleRetour = 90;
    else if(angle > 112.5 && angle <= 157.5)
        angleRetour = 135;
    else if(angle > 157.5 && angle <= 202.5)
        angleRetour = 180;
    else if(angle > 202.5 && angle <= 247.5)
        angleRetour = 225;
    else if(angle > 247.5 && angle <= 292.5)
        angleRetour = 270;
    else if(angle > 292.5 && angle <= 337.5)
        angleRetour = 315;
    else if(angle > 337.5 && angle <= 360)
        angleRetour = 360;

    return angleRetour;
}

int VueHaut::getLongueurBrique(const qreal longueur) const {
    return int((floor(longueur/echelle))*echelle);
}

void VueHaut::wheelEvent(QGraphicsSceneWheelEvent *event) {
    if(event->delta() > 0){
        emit rouletteAvant();
    }
    else if(event->delta() < 0){
        emit rouletteArriere();
    }
}

void VueHaut::deplacement(qreal dx, qreal dy) {
    if(!items().isEmpty()){
        foreach (QGraphicsItem *item, listeDesMursDans(items())) {
            item->moveBy(dx, dy);
        }
    }
}

void VueHaut::deplacement(QPointF point){
    if(!items().isEmpty()){
        QLineF depla;
        foreach (QGraphicsItem *item, listeDesMursDans(items())) {
            depla.setPoints(item->scenePos(),point);
            item->moveBy(depla.dx(), depla.dy());
        }
    }
}

void VueHaut::initialiserMenus() {

    // Préparation des menus

    menuUnMur = new QMenu;
    menuUnMurVerr = new QMenu;



    // Préparation des actions


    supprMurAct = new QAction(QIcon(":/res/supprimer.png"), tr("Supprimer"), this);
    supprMurAct->setStatusTip(tr("Supprimer"));
    connect(supprMurAct, SIGNAL(triggered()), this, SLOT(supprimerMurSelect()));

    menuUnMur->addAction(supprMurAct);

    changerCoteAct = new QAction(QIcon(":/res/Change.png"), tr("Changer le coté d'affichage"), this);
    changerCoteAct->setStatusTip(tr("Changer le coté d'affichage"));
    //    connect(changerCoteAct, SIGNAL(triggered()), this, SLOT(echangerMurSelect()));

    //    menuUnMur->addAction(changerCoteAct);

    passerEnVueDeFaceAct = new QAction(QIcon(":/res/passerVueFace.png"), tr("Passer en vue de face"), this);
    passerEnVueDeFaceAct->setStatusTip(tr("Passer en vue de face"));
    connect(passerEnVueDeFaceAct, SIGNAL(triggered()), maFenetre, SLOT(passerEnVueDeFace()));

    //    menuUnMurVerr->addAction(passerEnVueDeFaceAct);
}

void VueHaut::initialiser() {
    Objet3D *obj = new Objet3D(Objet3D::Colonne);
    typeObjet3D = obj->type();

    pointRotationObjet = new QGraphicsEllipseItem(QRectF(0,0,5,5));
    centreCamera.setRect(0,0,10,10);
    ligneDeMur = new QLineF;
    monMode = Select;
    mesure = new QGraphicsTextItem;
    mesurebis = new QGraphicsTextItem;
    pressePapier.clear();
    contenuCopie = false;
    superpose = false;
    decalageCopie = 50;
    force=0;
    modifing=false;
    unDeux=false;
    bouge=false;
    hauteurSalle=2;
    echelle=50;
    indicateurActif = true;


    penMurEnCours = new QPen(QColor(30,30,30,150), 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    penMurFini = new QPen(QColor(30,30,30), 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    penMurSelectionne = new QPen(QColor(200,80,0), 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    penMurMobile = new QPen(QColor(60,80,100), 2, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin);
    penSelection = new QPen(QColor(20,90,20,0), 10, Qt::DotLine, Qt::RoundCap, Qt::MiterJoin);
    penMurNonAffichable = new QPen(QColor(255,0,0), 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);

    pointCourbeUn = new QGraphicsRectItem;
    pointCourbeDeux = new QGraphicsRectItem;

    graphiqueSelection.setPen(*penSelection);

    /** BRUSH DE LA SELECTION */
    graphiqueSelection.setBrush(QBrush(QColor(80,80,20,40)));

    verouille = false;
    faceUn= new QRectF();
    rectUn=new QGraphicsRectItem();
    rectUn->setPen(*penSelection);
    rectUn->setBrush(QBrush(QColor(80,120,20,40)));
    faceDeux= new QRectF();
    rectDeux=new QGraphicsRectItem();
    rectDeux->setPen(*penSelection);
    rectDeux->setBrush(QBrush(QColor(120,80,20,40)));

    connect(maFenetre, SIGNAL(hauteurChangee(qreal)) , this , SLOT(modifierHauteurSalle(qreal)));
}

void VueHaut::peindre(const QPen &pen, QList<QGraphicsItem *> liste) {
    foreach (QGraphicsItem *item, this->listeDesElementsDans(liste)) {
        if(item->type() == Courbe::Type){
            Courbe *courbe = qgraphicsitem_cast<Courbe *>(item);
            courbe->setPen(pen);
        }
        else if(item->type() == Mur::Type){
            Mur *mur = qgraphicsitem_cast<Mur *>(item);
            mur->setPen(pen);
        }
        else if(item->type() == QGraphicsSurelevationItem::Type){
            QGraphicsSurelevationItem *sure = qgraphicsitem_cast<QGraphicsSurelevationItem *>(item);
            sure->setPen(pen);
        }
        else if(item->type() == typeObjet3D){
            Objet3D *obj = qgraphicsitem_cast<Objet3D *>(item);
            obj->setPen(pen);
        }
    }
}

void VueHaut::modifierHauteurSurelevSelect(double hauteur) {
    if(nombreDeSurelevationsDans(objets) == nombreDElementsDans(objets)) {
        //qDebug() << "NOMBRE DE SURELEVATIONS : " << nombreDeSurelevationsDans(objets);
        foreach (QGraphicsSurelevationItem *surelev, listeDesSurelevationsDans(objets)) {
            surelev->setHauteur(qreal(hauteur));
            //qDebug() << "hauteur surelev changée dans VueHaut : " << hauteur;
        }
    }
}

Mur* VueHaut::murSelectionne() {
    Mur *retour = NULL;
    if(nombreDeMursDans(objets) > 0){
        retour = listeDesMursDans(objets).first();
    }
    return retour;
}

int VueHaut::getEchelle(){
    return echelle;
}

double VueHaut::getHauteurSalle() {
    return hauteurSalle;
}


void VueHaut::modifierHauteurSalle(qreal h) {
    hauteurSalle = h;
}

Fenetre* VueHaut::getFenetre() {
    return maFenetre;
}

void VueHaut::verouillerSalle(){
    verouille = true;
    objets.clear();
    emit salleVerouillee();
    peindre(*penMurFini, listeDesElementsDans(items()));
    this->addItem(&centreCamera);
    centreCamera.setPos(QPointF(this->genererCentreVueHaut().x()-5,this->genererCentreVueHaut().y()-5));
}

void VueHaut::deverouillerSalle(){

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Attention !");
    msgBox.setText(tr("Cette action effacera tous les tableaux présents sur les murs existants. Voulez vous continuer ?"));
    msgBox.setStandardButtons(QMessageBox::NoButton);

    msgBox.addButton(tr("Continuer"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("Annuler"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole){
        verouille = false;
        objets.clear();
        if(this->items().contains(rectUn)){
            this->removeItem(rectUn);
        }
        if(this->items().contains(rectDeux)){
            this->removeItem(rectDeux);
        }
        emit salleDeverouillee();
        peindre(*penMurFini, items());
        if(items().contains(&centreCamera))
            this->removeItem(&centreCamera);
    }

}

QPointF VueHaut::getCentreCamera(){
 return QPointF(centreCamera.scenePos().x()-5,centreCamera.scenePos().y()-5);
}

bool VueHaut::isVerouille(){
    return verouille;
}


QList<Surelevation *> VueHaut::getSurelevations(){
    return surelevations;
}

void VueHaut::ajouterSurelevation(Surelevation *sur){
    if(sur != NULL)
        surelevations.append(sur);
}


void VueHaut::majTableaux(){
    //    foreach (QGraphicsLineItem *item, represTableaux) {
    //        represTableaux.removeOne(item);
    //        this->removeItem(item);
    //        delete item;
    //    }
    //    represTableaux.clear();
    //    foreach (Mur *murEnCours, listeDesMurs()) {
    //        represTableaux.append(murEnCours->calculerRepresentations());

    //    }
    //    foreach (QGraphicsLineItem *item, represTableaux) {
    //        if(item != NULL)
    //            this->addItem(item);
    //        else
    //            qDebug() << "ATT ! item NULL lors de la maj tableaux";
    //        qDebug() << "Représentation de tableau ajoutée ! pos = " << item->line();
    //        qDebug() << "Liste représentation  = " << represTableaux << "et tems : " << this->items();
    //    }
}

//QLineF VueHaut::rendreNormale(Mur *mur){
//    QLineF ligne = mur->line();
//    QLineF normale = ligne.normalVector();
//    return normale;
//}

//void VueHaut::afficherNormaleMurSelect(){
//    if(listeDesMursDans(objets).count()>0){
//        Mur *murReference = listeDesMursDans(objets).first();
//        QLineF normale = rendreNormale(murReference);
//        flecheNormale->setPos(murReference->line().x1()+(murReference->line().dx()/2),murReference->line().y1()+(murReference->line().dy()/2));
//        flecheNormale->resetTransform();
//        flecheNormale->rotate(-normale.angle());
//        flecheNormale->show();
//    }
//}

//void VueHaut::cacherNormale(){
//    flecheNormale->hide();
//}


//void VueHaut::echangerMurSelect(){
//    if(listeDesMursDans(objets).count()>0){
//        Mur *murReference = listeDesMursDans(objets).first();
//        QLineF ligne = murReference->line();
//        QPointF ech = ligne.p1();
//        ligne.setP1(ligne.p2());
//        ligne.setP2(ech);
//        murReference->setLine(ligne);
//        this->afficherNormaleMurSelect();
//    }
//}

void VueHaut::afficherRectFace(){
    qDebug()<<murSelectionne();
    qDebug()<<nombreDeMursDans(objets);
    if(!objets.isEmpty()){
        if(nombreDeMursDans(objets)==1)
        {
            Mur *murSelect = qgraphicsitem_cast<Mur *>(listeDesMursDans(objets).first());

            faceUn->setTopLeft(QPointF(0,0));
            faceUn->setBottomRight(QPointF(murSelect->line().length(),20));
            rectUn->setRect(*faceUn);
            rectUn->resetTransform();
            //rectUn->rotate(-murSelect->line().angle());
            rectUn->setRotation(rectUn->rotation() + (-murSelect->line().angle()));
            rectUn->setPos(murSelect->line().p1());
            this->addItem(rectUn);

            faceDeux->setTopLeft(QPointF(0,0));
            faceDeux->setBottomRight(QPointF(murSelect->line().length(),-20));
            rectDeux->setRect(*faceDeux);
            rectDeux->resetTransform();
            //rectDeux->rotate(-murSelect->line().angle());
            rectDeux->setRotation(rectDeux->rotation() + (-murSelect->line().angle()));
            rectDeux->setPos(murSelect->line().p1());
            this->addItem(rectDeux);
        }
    }
}

void VueHaut::cacherRectFace(){
    if(items().contains(rectUn))
        this->removeItem(rectUn);
    if(items().contains(rectDeux))
        this->removeItem(rectDeux);

}

QPointF VueHaut::genererCentreVueHaut(){
    QPointF centre;
    QPolygonF ensemble;

    foreach (Mur *m, listeDesMurs()) {
        ensemble.append(m->line().p1());
        ensemble.append(m->line().p2());
    }

    centre = ensemble.boundingRect().center();

    return centre;


}

QList<Objet3D *> VueHaut::listeDesObjets(){
    QList<Objet3D *> liste;

    if(!items().isEmpty()){
        foreach (QGraphicsItem *item, this->items()) {
            if (item->type() == typeObjet3D){
                liste.append(qgraphicsitem_cast<Objet3D *>(item));
            }
        }
    }
    return liste;
}


QList<QGraphicsItem *> VueHaut::getObjets(){
    return objets;

}

void VueHaut::setIndicateur(bool indic){
    indicateurActif = indic;
}

int VueHaut::getTypeObjets3D(){
    return typeObjet3D;
}
