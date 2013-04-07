#include "sauvegarde.h"

Sauvegarde::Sauvegarde(VueHaut *s)
{
    maSalle = s;
    doc = new QDomDocument;
}

bool Sauvegarde::Sauvegarder(QString fichier){



    // Création de l'en-tête du fichier XML : <?xml version="1.0" encoding="UTF-8"?>
    QDomNode xmlNode = doc->createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    // On insère cet en-tête avant le premier enfant
    doc->insertBefore(xmlNode, doc->firstChild());

    QDomElement racine = doc->createElement("racine");

    // On ajoute l'élément <racine> en tant que premier enfant de notre document
    doc->appendChild(racine);

    // On definit les attributs de la salle

    QDomElement infos = doc->createElement("infos");
    racine.appendChild(infos);
    infos.setAttribute("nom", maSalle->getFenetre()->getProjetCourant()->getNom());
    infos.setAttribute("rep", maSalle->getFenetre()->getProjetCourant()->getChemin());
    infos.setAttribute("desc", maSalle->getFenetre()->getProjetCourant()->getDescription());
    infos.setAttribute("y", maSalle->getFenetre()->getProjetCourant()->getDate().year());
    infos.setAttribute("m", maSalle->getFenetre()->getProjetCourant()->getDate().month());
    infos.setAttribute("d", maSalle->getFenetre()->getProjetCourant()->getDate().day());


    // Création de l'élément <salle>
    QDomElement salle = doc->createElement("salle");

    // On ajoute l'élément <salle> en tant que premier enfant de l'élément <racine>
    racine.appendChild(salle);
    salle.setAttribute("hauteur", maSalle->getHauteurSalle());
    salle.setAttribute("start_x",maSalle->getCentreCamera().x());
    salle.setAttribute("start_y",maSalle->getCentreCamera().y());
    salle.setAttribute("type_sol",maSalle->getFenetre()->getProjetCourant()->getSol());
    salle.setAttribute("url_sol",maSalle->getFenetre()->getProjetCourant()->url_sol);
    salle.setAttribute("scale_sol",maSalle->getFenetre()->getProjetCourant()->size_sol);



    //On récupère la liste des murs de la salle

    QList<Mur *> liste = maSalle->listeDesMurs();

    // Et pour chaque mur, on crée un ensemble de balises

    foreach (Mur *monMur, liste) {

        // Création de l'élément <mur>
        QDomElement mur = doc->createElement("mur");

        // On ajoute l'élément <mur> en tant que premier enfant de l'element <salle>
        salle.appendChild(mur);

        QDomElement pointDebut = doc->createElement("pointDebut");
        mur.appendChild(pointDebut);

        QDomElement pointFin = doc->createElement("pointFin");
        mur.appendChild(pointFin);

        pointDebut.setAttribute("x",monMur->line().x1());
        pointDebut.setAttribute("y",monMur->line().y1());

        pointFin.setAttribute("x",monMur->line().x2());
        pointFin.setAttribute("y",monMur->line().y2());

        mur.setAttribute("mobile",monMur->isMobile());
        mur.setAttribute("affichable",monMur->isAffichable());

        foreach (Tableau *tab, monMur->listeDesTableaux()) {
            QDomElement domTab = doc->createElement("tableau");
            mur.appendChild(domTab);
            domTab.setAttribute("nom",tab->getFichier());
            domTab.setAttribute("face",0);

            QDomElement geometry = doc->createElement("geometry");
            domTab.appendChild(geometry);
            geometry.setAttribute("width",tab->pixmap().width());
            geometry.setAttribute("height",tab->pixmap().height());

            QDomElement position = doc->createElement("position");
            domTab.appendChild(position);
            position.setAttribute("marge_x",tab->pos().x());
            position.setAttribute("marge_y",tab->pos().y());
            QPointF debugPos = tab->pos();
            qDebug() << "Position du tableau lors de la sauvegarde : " << debugPos;
        }

        foreach (Tableau *tab, monMur->listeDesTableauxDeux()) {
            QDomElement domTab = doc->createElement("tableau");
            mur.appendChild(domTab);
            domTab.setAttribute("nom",tab->getFichier());
            domTab.setAttribute("face",1);

            QDomElement geometry = doc->createElement("geometry");
            domTab.appendChild(geometry);
            geometry.setAttribute("width",tab->pixmap().width());
            geometry.setAttribute("height",tab->pixmap().height());

            QDomElement position = doc->createElement("position");
            domTab.appendChild(position);
            position.setAttribute("marge_x",tab->pos().x());
            position.setAttribute("marge_y",tab->pos().y());
            QPointF debugPos = tab->pos();
            qDebug() << "Position du tableau lors de la sauvegarde : " << debugPos;
        }


    }

    QList<Courbe *> listec = maSalle->listeDesCourbes();

    // Et pour chaque courbe, on crée un ensemble de balises

    foreach (Courbe *maCourbe, listec) {

        // Création de l'élément <courbe>
        QDomElement courbe = doc->createElement("courbe");

        // On ajoute l'élément <courbe> en tant qu'enfant de l'element <salle>
        salle.appendChild(courbe);

        QDomElement pointDebut = doc->createElement("pointDebut");
        courbe.appendChild(pointDebut);

        QDomElement pointFin = doc->createElement("pointFin");
        courbe.appendChild(pointFin);

        QDomElement pointUn = doc->createElement("pointUn");
        courbe.appendChild(pointUn);

        QDomElement pointDeux = doc->createElement("pointDeux");
        courbe.appendChild(pointDeux);

        pointDebut.setAttribute("x",maCourbe->getDebut().x());
        pointDebut.setAttribute("y",maCourbe->getDebut().y());

        pointFin.setAttribute("x",maCourbe->getFin().x());
        pointFin.setAttribute("y",maCourbe->getFin().y());

        pointUn.setAttribute("x",maCourbe->getPointUn().x());
        pointUn.setAttribute("y",maCourbe->getPointUn().y());

        pointDeux.setAttribute("x",maCourbe->getPointDeux().x());
        pointDeux.setAttribute("y",maCourbe->getPointDeux().y());

    }

    // Et pour chaque Surelevation, on crée un ensemble de balises

    foreach (Surelevation *maSurelev, maSalle->getSurelevations()) {

        // Création de l'élément <surelevation>
        QDomElement surelevation = doc->createElement("surelevation");

        // On ajoute l'élément <surelevation> en tant qu'enfant de l'element <salle>
        salle.appendChild(surelevation);

        // Pour chaque point de la surelevation courante
        foreach (QPoint3D *pt, *maSurelev->getListeDesPoints()) {
            QDomElement point = doc->createElement("point");
            surelevation.appendChild(point);
            point.setAttribute("x",pt->getx());
            point.setAttribute("y",pt->gety());
            point.setAttribute("z",pt->getz());
        }

    }

    foreach (Objet3D *monObjet, maSalle->listeDesObjets()) {

        // Création de l'élément <surelevation>
        QDomElement domObj = doc->createElement("objet");

        // On ajoute l'élément <surelevation> en tant qu'enfant de l'element <salle>
        salle.appendChild(domObj);

        domObj.setAttribute("x",monObjet->pos().x());
        domObj.setAttribute("y",monObjet->pos().y());
        domObj.setAttribute("rot",monObjet->rotation());
        domObj.setAttribute("type",int(monObjet->getType()));

    }

    // Création du fichier XML de sortie
    QFile file( fichier );

    // Ouverture de ce fichier en lecture seule
    file.open(QIODevice::WriteOnly);

    // On crée une QTextStream a partir de ce fichier
    QTextStream ts(&file);

    // Valeur servant au nombre de caractères pour l'indentation du fichier XML
    int indent = 2;

    // On sauvegarde le fichier XML en precisant l'indentation desirée
    doc->save(ts, indent);

    return 0;
}

bool Sauvegarde::Charger(QString fichier){
    qDebug() << "   > On crée le fichier...";
    QFile file(fichier);


    qDebug() << "   > Ouverture du fichier en lecture seule et en mode texte...";
    // Ouverture du fichier en lecture seule et en mode texte
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    qDebug() << "   > On vide la salle...";
    maSalle->viderObjets();
    maSalle->clear();
    maSalle->initialiser();

    qDebug() << "   > Ajoute le contenu du fichier XML dans un QDomDocument...";
    // Ajoute le contenu du fichier XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
    doc->setContent(&file, false);

    qDebug() << "   > Ici, racine pointe sur l'élément <racine> de notre document...";
    // Ici, racine pointe sur l'élément <racine> de notre document
    QDomElement racine = doc->documentElement();

    qDebug() << "   > Ici, racine pointe sur un fils de <racine>...";
    // Ici, racine pointe sur un fils de <racine>



    bool valide = false;
    racine = racine.firstChildElement();

    while(!racine.isNull()){

        if(racine.tagName() == "infos"){
            valide = true;
            QString nom = racine.attribute("nom");
            QString desc = racine.attribute("desc");
            QString rep = racine.attribute("rep");
            QDir monRep(rep);
            monRep.cdUp();
            QDate date(racine.attribute("y").toInt(),racine.attribute("m").toInt(),racine.attribute("d").toInt());
            Projet *proj = new Projet(nom, QDir(monRep),desc,date);
            maSalle->getFenetre()->nouveauProjet(proj);
        }
        else if(racine.tagName() == "salle"){
            valide = true;
            double hauteur = racine.attribute("hauteur").toDouble();
            int type_sol = racine.attribute("type_sol").toInt();
            maSalle->getFenetre()->getProjetCourant()->setSol(Sol(type_sol));
            maSalle->modifierHauteurSalle(hauteur);
        }


    QDomElement ele = racine.firstChildElement();



    qDebug() << "   > On parcourt tous les enfants de l'élément <mur>...";
    // On parcourt tous les enfants de l'élément <mur>
    while(!ele.isNull())
    {
        if(ele.tagName() == "mur")
        {
            // On crée un nouveau mur
            bool mobile, affichable;
            QPointF p1;
            QPointF p2;

            QList<Tableau *> listeFaceUne;
            QList<Tableau *> listeFaceDeux;

            QDomElement point = ele.firstChildElement();
            qDebug() << "nom elem mur : " << ele.tagName();
            mobile = ele.attribute("mobile").toInt();
            affichable = ele.attribute("affichable").toInt();


            while(!point.isNull()){

                if(point.tagName() == "pointDebut")
                {
                    p1.setX(point.attribute("x").toDouble());
                    p1.setY(point.attribute("y").toDouble());
                }
                else if(point.tagName() == "pointFin")
                {
                    p2.setX(point.attribute("x").toDouble());
                    p2.setY(point.attribute("y").toDouble());
                }
                else if(point.tagName() == "tableau"){

                    Tableau *monTab = new Tableau(point.attribute("nom"));

                    bool face = point.attribute("face").toInt();

                    QDomElement tab = point.firstChildElement();

                    while(!tab.isNull()){
                        qDebug() << "On a ajouté un tableau ! Yeah ! (face is " << face <<")";
                        if(tab.tagName() == "geometry"){
                            monTab->setPixmap(QPixmap(monTab->getFichier()).scaledToWidth(tab.attribute("width").toInt()));
                        }
                        else if(tab.tagName() == "position"){
                            monTab->setPos(tab.attribute("marge_x").toDouble(),tab.attribute("marge_y").toDouble());
                        }




                    tab = tab.nextSiblingElement();
                    }

                    if(face){
                        listeFaceDeux.append(monTab);
                    }
                    else {
                        listeFaceUne.append(monTab);
                    }

                }

                qDebug() << "point ajoute";
                point = point.nextSiblingElement();
            }

            Mur *murCourant = new Mur(QLineF(p1,p2),maSalle);
            murCourant->setMobile(mobile);
            murCourant->setAffichable(affichable);
            maSalle->addItem(murCourant);
            foreach (Tableau *tba, listeFaceUne) {
                qDebug() << "On a ajouté un tableau au mur un";
                murCourant->getPremiereVueFace()->addItem(tba);
            }
            foreach (Tableau *tbb, listeFaceDeux) {
                qDebug() << "On a ajouté un tableau au mur deux";
                murCourant->getDeuxiemeVueFace()->addItem(tbb);
            }




        }
        else if(ele.tagName() == "courbe")
        {
            // On crée un nouveau mur
            QPointF p1;
            QPointF p2;
            QPointF pdeb;
            QPointF pfin;

            QDomElement point = ele.firstChildElement();
            qDebug() << "nom elem courbe : " << ele.tagName();

            while(!point.isNull()){

                if(point.tagName() == "pointDebut")
                {
                    pdeb.setX(point.attribute("x").toDouble());
                    pdeb.setY(point.attribute("y").toDouble());
                }
                else if(point.tagName() == "pointFin")
                {
                    pfin.setX(point.attribute("x").toDouble());
                    pfin.setY(point.attribute("y").toDouble());
                }
                else if(point.tagName() == "pointUn")
                {
                    p1.setX(point.attribute("x").toDouble());
                    p1.setY(point.attribute("y").toDouble());
                }
                else if(point.tagName() == "pointDeux")
                {
                    p2.setX(point.attribute("x").toDouble());
                    p2.setY(point.attribute("y").toDouble());
                }


                qDebug() << "point ajoute";
                point = point.nextSiblingElement();
            }
            QPainterPath *chemin = new QPainterPath(pdeb);
            chemin->cubicTo(p1,p2,pfin);
            Courbe *courbeEnCour = new Courbe(*chemin);
            courbeEnCour->setDebut(pdeb);
            courbeEnCour->setPointUn(p1);
            courbeEnCour->setPointDeux(p2);
            courbeEnCour->setFin(pfin);
            maSalle->addItem(courbeEnCour);
        }
        else if(ele.tagName() == "objet")
        {
            QPointF p1(ele.attribute("x").toDouble(),ele.attribute("y").toDouble());
            int rot = ele.attribute("rot").toInt();
            int type = ele.attribute("type").toInt();


            Objet3D *obj = new Objet3D(Objet3D::TypeObjet(type));
            obj->setPos(p1);
            //obj->rotate(rot);
            obj->setRotation(obj->rotation() + rot);
            maSalle->addItem(obj);
        }
        else if(ele.tagName() == "surelevation")
        {
            QDomElement point = ele.firstChildElement();

            QList<QPoint3D *> maListe;
            while(!point.isNull()){

                if(point.tagName() == "point")
                {
                    QPoint3D *p = new QPoint3D(0,0,0);
                    p->setX(point.attribute("x").toDouble());
                    p->setY(point.attribute("y").toDouble());
                    p->setZ(point.attribute("z").toDouble());
                    maListe.append(p);
                }

                qDebug() << "point ajoute";
                point = point.nextSiblingElement();
            }
            Surelevation *maSurelev = new Surelevation(maListe);
            maSalle->ajouterSurelevation(maSurelev);
            maSalle->addItem(maSurelev->getGraphicsSurelevation());
        }

        ele = ele.nextSiblingElement();

    }

    racine = racine.nextSiblingElement();

}


    if(!valide){
        return false;
    }
    qDebug() << maSalle->items();
    return true;
}
