#include "loader.h"

Loader::Loader() : mRoot(0)
{

    throw "Aucun fichier n'a été donné en argument.";
}

Loader::Loader(QString fichier){
    QFile file(fichier);
    if(file.exists()){
        //qDebug() << "le fichier existe !";
        this->valide = true;
        nomFichier = fichier;
    }
    else {
        //qDebug() << "le fichier est introuvable :" << fichier;
        this->valide = false;
    }
}

void Loader::reconfigure(){
    mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
    mRoot->showConfigDialog();
}


void Loader::preparerMedias(){
    if(valide){

        QDir dir("./media/");
        if(dir.exists("temp")){
            dir.cd("temp");
            foreach (QString fileName, dir.entryList()) {
                dir.remove(fileName);
            }
        }
        else {
            dir.mkdir("temp");
        }

        QFile fileMat("./media/temp/tableaux.material");

        if (!fileMat.open(QFile::WriteOnly)) {
            throw "impossible d'ouvrir le fichier material des tableaux";

        }
        QTextStream fluxMat(&fileMat);
        QFile file(nomFichier);
        QDomDocument doc;
        if(!file.open(QFile::ReadOnly | QFile::Text))
            throw "exeption : erreur de lecture du fichier";
        doc.setContent(&file, false);
        QDomElement racine = doc.documentElement();
        while(!racine.isNull()){
            QDomElement ele = racine.firstChildElement();

            if(racine.tagName() == "salle")
            {
                hauteurMur = 50*(racine.attribute("hauteur").toDouble());
                pointDepart.x = racine.attribute("start_x").toDouble();
                pointDepart.y = racine.attribute("start_y").toDouble();
                typeSol = racine.attribute("type_sol").toInt();
                cheminTextSol = racine.attribute("url_sol");
                scaleTextSol = (racine.attribute("scale_sol").toDouble()/10000)*50;
                if(typeSol == 3){
                    QFile file(cheminTextSol);
                    file.copy("./media/temp/"+QFileInfo(cheminTextSol).fileName());
                    fluxMat << this->genererMaterial(QFileInfo(cheminTextSol).baseName(),QFileInfo(cheminTextSol).fileName(),scaleTextSol);

                }
            }

            racine = racine.firstChildElement();
            while(!ele.isNull())
            {
                if(ele.tagName() == "mur")
                {
                    QDomElement point = ele.firstChildElement();
                    while(!point.isNull()){
                        if(point.tagName() == "tableau")
                        {
                            QString nomFichier = point.attribute("nom");
                            QFile file(nomFichier);
                            file.copy("./media/temp/"+QFileInfo(nomFichier).fileName());
                            fluxMat << this->genererMaterial(QFileInfo(nomFichier).baseName(),QFileInfo(nomFichier).fileName());
                        }
                        point = point.nextSiblingElement();
                    }
                }
                ele = ele.nextSiblingElement();
            }
            racine = racine.nextSiblingElement();
        }
    }
}

void Loader::recupererDonnees(){
    if(valide){
        int largeurMur = 0.1;
        double hauteur;

        cheminTextSol = "";
        scaleTextSol = 0.05;
        QFile file(nomFichier);
        QDomDocument doc;
        // Ouverture du fichier en lecture seule et en mode texte
        if(!file.open(QFile::ReadOnly | QFile::Text))
            throw "exeption : erreur de lecture du fichier";
        // Ajoute le contenu du fichier XML dans un QDomDocument et dit au QDomDocument de ne pas tenir compte des namespaces
        doc.setContent(&file, false);
        // Ici, racine pointe sur l'élément <racine> de notre document
        QDomElement racine = doc.documentElement();
        // Ici, racine pointe sur un fils de <racine>
        while(!racine.isNull()){
            QDomElement ele = racine.firstChildElement();
            int i=0;

            if(racine.tagName() == "salle")
            {
                hauteurMur = 50*(racine.attribute("hauteur").toDouble());
                pointDepart.x = racine.attribute("start_x").toDouble();
                pointDepart.y = racine.attribute("start_y").toDouble();
                typeSol = racine.attribute("type_sol").toInt();
                cheminTextSol = racine.attribute("url_sol");
            }

            racine = racine.firstChildElement();
            int k=0;
            int nbTab=0;
            while(!ele.isNull())
            {
                if(ele.tagName() == "mur")
                {

                    qDebug()<< "Creation de mur !! ";
                    // On crée un nouveau mur
                    bool mobile, affichable;
                    QPointF p1;
                    QPointF p2;


                    QDomElement point = ele.firstChildElement();
                    mobile = ele.attribute("mobile").toInt();
                    affichable = ele.attribute("affichable").toInt();

                    Ogre::SceneNode *nodeMur = node->createChildSceneNode("nodeMur"+Ogre::String(QString::number(nbMur).toStdString()), Ogre::Vector3::ZERO, Quaternion::IDENTITY);
                    Ogre::SceneNode *nobeTableau = node->createChildSceneNode("nodeTableau"+Ogre::String(QString::number(nbTab).toStdString()), Ogre::Vector3::ZERO, Quaternion::IDENTITY);
                    k++;
                    nbTab++;

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
                        else if(point.tagName() == "tableau")
                        {

                            int tab_h = 0;
                            int tab_w = 0;
                            QPointF tab_pos;
                            QString nomFichier = point.attribute("nom");
                            bool cote = point.attribute("face").toInt();

                            QDomElement tab = point.firstChildElement();
                            while(!tab.isNull()){
                                if(tab.tagName() == "geometry")
                                {
                                    tab_h = tab.attribute("height").toDouble()/7;
                                    tab_w = tab.attribute("width").toDouble()/7;
                                }
                                else if(tab.tagName() == "position")
                                {
                                    tab_pos.setX(tab.attribute("marge_x").toDouble()/7);
                                    tab_pos.setY(tab.attribute("marge_y").toDouble()/7);
                                }
                                tab = tab.nextSiblingElement();
                            }
                            Ogre::SceneNode *tabNode = nobeTableau->createChildSceneNode("tab_node"+Ogre::String(QString::number(i).toStdString()), Ogre::Vector3::ZERO, Quaternion::IDENTITY);
                            tabNode->attachObject(creerTableau("Tableau"+Ogre::String(QString::number(i).toStdString()), QFileInfo(nomFichier).baseName().toStdString(),tab_w, tab_h, cote));
                            tabNode->rotate(Ogre::Vector3::UNIT_Z, Ogre::Degree(180));
                            QLineF popo = QLineF(p1,p2);
                            if(cote){
                                tabNode->translate(popo.length()-tab_pos.x()+2.8,-tab_pos.y()+hauteurMur+2.8,-0.1);

                            }
                            else{

                                tabNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(180));
                                tabNode->translate(tab_pos.x()-2.8,-tab_pos.y()+hauteurMur+2.8,0.2);
                            }

                            i++;

                        }

                        point = point.nextSiblingElement();
                    }
                    QLineF ligne = QLineF(p1,p2);


                    /** # Modifs */
                    nodeMur->attachObject(creerMur("Cube"+Ogre::String(QString::number(nbMur).toStdString()), "patch",p1,p2,hauteurMur));
                    nbMur++;
                    nobeTableau->translate(ligne.x1(),0.0,ligne.y1());
                    nobeTableau->rotate(Ogre::Vector3::UNIT_Y,Ogre::Degree(ligne.angle()));
                    i++;

                }
                else if(ele.tagName() == "surelevation")
                {
                    qDebug()<< "Creation de surelevation !! ";
                    QDomElement point = ele.firstChildElement();
                    QList<QPointF> maListe;
                    while(!point.isNull()){

                        if(point.tagName() == "point")
                        {
                            QPointF p;
                            p.setX(point.attribute("x").toDouble());
                            p.setY(point.attribute("y").toDouble());
                            hauteur = point.attribute("z").toDouble()*50;
                            maListe.append(p);
                        }

                        point = point.nextSiblingElement();
                    }
                    Ogre::SceneNode *nodeSurelev = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeSurelev"+Ogre::String(QString::number(nbSurelev).toStdString()), Ogre::Vector3::ZERO, Quaternion::IDENTITY);
                    nodeSurelev->attachObject(creerSurelevation("surelev"+Ogre::String(QString::number(i).toStdString()),"surelevation",maListe,hauteur));
                    i++;
                    nbSurelev++;
                }
                else if(ele.tagName() == "objet")
                {
                    qDebug()<< "Creation de objet !! ";
                    QPointF centre;

                    Ogre::Entity *entObj;
                    Ogre::AxisAlignedBox op;
                    Ogre::Vector3 taille=Ogre::Vector3::ZERO;
                    Ogre::SceneNode *nodeObjet = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeObjet"+Ogre::String(QString::number(nbObjets).toStdString()), Ogre::Vector3::ZERO, Quaternion::IDENTITY);
                    centre.setX(ele.attribute("x").toDouble());
                    centre.setY(ele.attribute("y").toDouble());

                    int type = ele.attribute("type").toInt();
                    if(type != 0){
                        qDebug() << "Type d'objet invalide ! (" << type << ")";
                    }
                    else {
                        switch(type){

//                        case 0:
//                            entObj = mSceneMgr->createEntity("Banc"+Ogre::String(QString::number(nbObjets).toStdString()),"banc.obj");
//                            entObj->setCastShadows(false);
//                            nodeObjet->attachObject(entObj);
//                            op=entObj->getBoundingBox();
//                            taille =op.getMaximum();

//                            break;
//                        case 1:
//                            entObj = mSceneMgr->createEntity("Chaise"+Ogre::String(QString::number(nbObjets).toStdString()),"chaise.obj");
//                            entObj->setCastShadows(false);
//                            nodeObjet->attachObject(entObj);
//                            op=entObj->getBoundingBox();
//                            taille =op.getMaximum();
//                            break;

//                        case 2:
//                            entObj = mSceneMgr->createEntity("Table"+Ogre::String(QString::number(nbObjets).toStdString()),"table.obj");
//                            entObj->setCastShadows(false);
//                            nodeObjet->attachObject(entObj);
//                            op=entObj->getBoundingBox();
//                            taille =op.getMaximum();
//                            break;

                        case 0:
                            entObj = mSceneMgr->createEntity("Colonne"+Ogre::String(QString::number(nbObjets).toStdString()),"column.mesh");
                            entObj->setCastShadows(false);
                            entObj->setMaterialName("patch");
                            nodeObjet->attachObject(entObj);

                            op=entObj->getBoundingBox();
                            taille =op.getMaximum();
                            nodeObjet->scale(0.4,hauteurMur/(taille.y-2.8),0.4);
                            nodeObjet->translate(centre.x()+2.8,0,centre.y()+50*0.2-2.8);


                            break;
                        }

                    }
                    i++;

                    nbObjets++;
                }
                else if(ele.tagName() == "courbe")
                {
                    qDebug()<< "Creation de courbe !! ";
                    QDomElement point = ele.firstChildElement();
                    QPointF p1;
                    QPointF p2;
                    QPointF p3;
                    QPointF p4;

                    while(!point.isNull()){

                        if(point.tagName() == "pointDebut")
                        {
                            p1.setX(point.attribute("x").toDouble());
                            p1.setY(point.attribute("y").toDouble());
                        }
                        else if(point.tagName() == "pointUn")
                        {
                            p2.setX(point.attribute("x").toDouble());
                            p2.setY(point.attribute("y").toDouble());
                        }
                        else if(point.tagName() == "pointDeux")
                        {
                            p3.setX(point.attribute("x").toDouble());
                            p3.setY(point.attribute("y").toDouble());
                        }
                        else if(point.tagName() == "pointFin")
                        {
                            p4.setX(point.attribute("x").toDouble());
                            p4.setY(point.attribute("y").toDouble());
                        }

                        point = point.nextSiblingElement();
                    }

                    Ogre::SceneNode *nodeCourbe =  mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeCourbe"+Ogre::String(QString::number(nbCourbe).toStdString()), Ogre::Vector3::ZERO, Quaternion::IDENTITY);
                    nodeCourbe->attachObject(creerCourbe("maCourbe"+nbCourbe,"patch",p1,p2,p3,p4,hauteurMur));

                    i++;
                    nbCourbe++;

                }
                ele = ele.nextSiblingElement();
                k++;

            }
            racine = racine.nextSiblingElement();
        }

    }

}

Loader::~Loader()
{
    delete mRoot;
}

bool Loader::chargerRessources(){
    Ogre::ConfigFile configFile;
    configFile.load("resources.cfg");
    Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                        archName, typeName, secName);
        }
    }
    if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    {
        return false;
    }

}

void Loader::genererAxes() {
    /*
    Ogre::SceneNode *nodeBaseAxes = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeAxes", Ogre::Vector3::ZERO, Quaternion::IDENTITY);
    Ogre::SceneNode *nodeAxeO = nodeBaseAxes->createChildSceneNode("nodeAxeO", Ogre::Vector3::ZERO, Quaternion::IDENTITY);
    Ogre::SceneNode *nodeAxeX = nodeBaseAxes->createChildSceneNode("nodeAxeX", Ogre::Vector3::ZERO, Quaternion::IDENTITY);
    Ogre::SceneNode *nodeAxeY = nodeBaseAxes->createChildSceneNode("nodeAxeY", Ogre::Vector3::ZERO, Quaternion::IDENTITY);
    Ogre::SceneNode *nodeAxeZ = nodeBaseAxes->createChildSceneNode("nodeAxeZ", Ogre::Vector3::ZERO, Quaternion::IDENTITY);

    int taille = 1;
    nodeAxeO->attachObject(creerMur("cubeO","cube_o",taille,taille,taille));
    nodeAxeX->attachObject(creerMur("cubeX","cube_x",taille,taille,taille));
    nodeAxeY->attachObject(creerMur("cubeY","cube_y",taille,taille,taille));
    nodeAxeZ->attachObject(creerMur("cubeZ","cube_z",taille,taille,taille));

    nodeAxeX->translate(50,0,0);
    nodeAxeY->translate(0,50,0);
    nodeAxeZ->translate(0,0,50);
    */

}

Ogre::Entity *Loader::creerCourbe(String nom, String nomMat, QPointF p1, QPointF p2, QPointF p3, QPointF p4, Real hauteur, int maxlevel, float subdiv){


    Ogre::Vector3 n1 = Ogre::Math::calculateBasicFaceNormal(
                Ogre::Vector3(p1.x(),5,p1.y()),
                Ogre::Vector3(p2.x()-p1.x(),0,p2.y()-p1.y()),
                Ogre::Vector3((p2.x()+p1.x())/2,1,(p2.y()+p1.y())/2));

    Ogre::Vector3 n2 = Ogre::Math::calculateBasicFaceNormal(
                Ogre::Vector3(p2.x(),5,p2.y()),
                Ogre::Vector3(p3.x()-p2.x(),0,p3.y()-p2.y()),
                Ogre::Vector3((p3.x()+p2.x())/2,1,(p3.y()+p2.y())/2));

    Ogre::Vector3 n3 = Ogre::Math::calculateBasicFaceNormal(
                Ogre::Vector3(p3.x(),5,p3.y()),
                Ogre::Vector3(p4.x()-p3.x(),0,p4.y()-p3.y()),
                Ogre::Vector3((p4.x()+p3.x())/2,1,(p4.y()+p3.y())/2));


    PatchVertex verts[81] =
    {

        {p1.x(), hauteur*(0/8), p1.y(), n1.x, n1.y, n1.z, 0, 0.0},
        {p1.x(), hauteur*(1/8), p1.y(),  n1.x, n1.y, n1.z, 1/8, 0.0},
        {p1.x(), hauteur*(2/8), p1.y(),  n1.x, n1.y, n1.z, 2/8, 0.0},
        {p1.x(), hauteur*(3/8), p1.y(),  n1.x, n1.y, n1.z, 3/8, 0.0},
        {p1.x(), hauteur*(4/8), p1.y(),  n1.x, n1.y, n1.z, 4/8, 0.0},
        {p1.x(), hauteur*(5/8), p1.y(),  n1.x, n1.y, n1.z, 5/8, 0.0},
        {p1.x(), hauteur*(6/8), p1.y(),  n1.x, n1.y, n1.z, 6/8, 0.0},
        {p1.x(), hauteur*(7/8), p1.y(),  n1.x, n1.y, n1.z, 7/8, 0.0},
        {p1.x(), hauteur*(8/8), p1.y(),  n1.x, n1.y, n1.z, 1.0, 0.0},

        {p1.x(), hauteur*(0/8), p1.y(), n1.x, n1.y, n1.z, 0, 0.0},
        {p1.x(), hauteur*(1/8), p1.y(),  n1.x, n1.y, n1.z, 1/8, 0.0},
        {p1.x(), hauteur*(2/8), p1.y(),  n1.x, n1.y, n1.z, 2/8, 0.0},
        {p1.x(), hauteur*(3/8), p1.y(),  n1.x, n1.y, n1.z, 3/8, 0.0},
        {p1.x(), hauteur*(4/8), p1.y(),  n1.x, n1.y, n1.z, 4/8, 0.0},
        {p1.x(), hauteur*(5/8), p1.y(),  n1.x, n1.y, n1.z, 5/8, 0.0},
        {p1.x(), hauteur*(6/8), p1.y(),  n1.x, n1.y, n1.z, 6/8, 0.0},
        {p1.x(), hauteur*(7/8), p1.y(),  n1.x, n1.y, n1.z, 7/8, 0.0},
        {p1.x(), hauteur*(8/8), p1.y(),  n1.x, n1.y, n1.z, 1.0, 0.0},

        {p1.x(), hauteur*(0/8), p1.y(), n1.x, n1.y, n1.z, 0, 0.0},
        {p1.x(), hauteur*(1/8), p1.y(),  n1.x, n1.y, n1.z, 1/8, 0.0},
        {p1.x(), hauteur*(2/8), p1.y(),  n1.x, n1.y, n1.z, 2/8, 0.0},
        {p1.x(), hauteur*(3/8), p1.y(),  n1.x, n1.y, n1.z, 3/8, 0.0},
        {p1.x(), hauteur*(4/8), p1.y(),  n1.x, n1.y, n1.z, 4/8, 0.0},
        {p1.x(), hauteur*(5/8), p1.y(),  n1.x, n1.y, n1.z, 5/8, 0.0},
        {p1.x(), hauteur*(6/8), p1.y(),  n1.x, n1.y, n1.z, 6/8, 0.0},
        {p1.x(), hauteur*(7/8), p1.y(),  n1.x, n1.y, n1.z, 7/8, 0.0},
        {p1.x(), hauteur*(8/8), p1.y(),  n1.x, n1.y, n1.z, 1.0, 0.0},


        {p2.x(), hauteur*(0/8), p2.y(), n2.x, n2.y, n2.z, 0, 0.0},
        {p2.x(), hauteur*(1/8), p2.y(),  n2.x, n2.y, n2.z, 1/8, 0.0},
        {p2.x(), hauteur*(2/8), p2.y(),  n2.x, n2.y, n2.z, 2/8, 0.0},
        {p2.x(), hauteur*(3/8), p2.y(),  n2.x, n2.y, n2.z, 3/8, 0.0},
        {p2.x(), hauteur*(4/8), p2.y(),  n2.x, n2.y, n2.z, 4/8, 0.0},
        {p2.x(), hauteur*(5/8), p2.y(),  n2.x, n2.y, n2.z, 5/8, 0.0},
        {p2.x(), hauteur*(6/8), p2.y(),  n2.x, n2.y, n2.z, 6/8, 0.0},
        {p2.x(), hauteur*(7/8), p2.y(),  n2.x, n2.y, n2.z, 7/8, 0.0},
        {p2.x(), hauteur*(8/8), p2.y(),  n2.x, n2.y, n2.z, 1.0, 0.0},





        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(0/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2, n2.x, n2.y, n2.z, 0, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(1/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 1/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(2/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 2/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(3/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 3/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(4/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 4/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(5/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 5/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(6/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 6/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(7/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 7/8, 0.0},
        {(((((p2.x()+p3.x())/2)+p4.x())/2)+((((p2.x()+p3.x())/2)+p1.x())/2))/2, hauteur*(8/8), (((((p2.y()+p3.y())/2)+p4.y())/2)+((((p2.y()+p3.y())/2)+p1.y())/2))/2,  n2.x, n2.y, n2.z, 1.0, 0.0},


        {p3.x(), hauteur*(0/8), p3.y(), n2.x, n2.y, n2.z, 0, 0.0},
        {p3.x(), hauteur*(1/8), p3.y(),  n2.x, n2.y, n2.z, 1/8, 0.0},
        {p3.x(), hauteur*(2/8), p3.y(),  n2.x, n2.y, n2.z, 2/8, 0.0},
        {p3.x(), hauteur*(3/8), p3.y(),  n2.x, n2.y, n2.z, 3/8, 0.0},
        {p3.x(), hauteur*(4/8), p3.y(),  n2.x, n2.y, n2.z, 4/8, 0.0},
        {p3.x(), hauteur*(5/8), p3.y(),  n2.x, n2.y, n2.z, 5/8, 0.0},
        {p3.x(), hauteur*(6/8), p3.y(),  n2.x, n2.y, n2.z, 6/8, 0.0},
        {p3.x(), hauteur*(7/8), p3.y(),  n2.x, n2.y, n2.z, 7/8, 0.0},
        {p3.x(), hauteur*(8/8), p3.y(),  n2.x, n2.y, n2.z, 1.0, 0.0},


        {p4.x(), hauteur*(0/8), p4.y(),  n3.x, n3.y, n3.z, 0, 0.0},
        {p4.x(), hauteur*(1/8), p4.y(),  n3.x, n3.y, n3.z, 1/8, 0.0},
        {p4.x(), hauteur*(2/8), p4.y(),  n3.x, n3.y, n3.z, 2/8, 0.0},
        {p4.x(), hauteur*(3/8), p4.y(),  n3.x, n3.y, n3.z, 3/8, 0.0},
        {p4.x(), hauteur*(4/8), p4.y(),  n3.x, n3.y, n3.z, 4/8, 0.0},
        {p4.x(), hauteur*(5/8), p4.y(),  n3.x, n3.y, n3.z, 5/8, 0.0},
        {p4.x(), hauteur*(6/8), p4.y(),  n3.x, n3.y, n3.z, 6/8, 0.0},
        {p4.x(), hauteur*(7/8), p4.y(),  n3.x, n3.y, n3.z, 7/8, 0.0},
        {p4.x(), hauteur*(8/8), p4.y(),  n3.x, n3.y, n3.z, 1.0, 0.0},


        {p4.x(), hauteur*(0/8), p4.y(),  n3.x, n3.y, n3.z, 0, 0.0},
        {p4.x(), hauteur*(1/8), p4.y(),  n3.x, n3.y, n3.z, 1/8, 0.0},
        {p4.x(), hauteur*(2/8), p4.y(),  n3.x, n3.y, n3.z, 2/8, 0.0},
        {p4.x(), hauteur*(3/8), p4.y(),  n3.x, n3.y, n3.z, 3/8, 0.0},
        {p4.x(), hauteur*(4/8), p4.y(),  n3.x, n3.y, n3.z, 4/8, 0.0},
        {p4.x(), hauteur*(5/8), p4.y(),  n3.x, n3.y, n3.z, 5/8, 0.0},
        {p4.x(), hauteur*(6/8), p4.y(),  n3.x, n3.y, n3.z, 6/8, 0.0},
        {p4.x(), hauteur*(7/8), p4.y(),  n3.x, n3.y, n3.z, 7/8, 0.0},
        {p4.x(), hauteur*(8/8), p4.y(),  n3.x, n3.y, n3.z, 1.0, 0.0},


        {p4.x(), hauteur*(0/8), p4.y(),  n3.x, n3.y, n3.z, 0, 0.0},
        {p4.x(), hauteur*(1/8), p4.y(),  n3.x, n3.y, n3.z, 1/8, 0.0},
        {p4.x(), hauteur*(2/8), p4.y(),  n3.x, n3.y, n3.z, 2/8, 0.0},
        {p4.x(), hauteur*(3/8), p4.y(),  n3.x, n3.y, n3.z, 3/8, 0.0},
        {p4.x(), hauteur*(4/8), p4.y(),  n3.x, n3.y, n3.z, 4/8, 0.0},
        {p4.x(), hauteur*(5/8), p4.y(),  n3.x, n3.y, n3.z, 5/8, 0.0},
        {p4.x(), hauteur*(6/8), p4.y(),  n3.x, n3.y, n3.z, 6/8, 0.0},
        {p4.x(), hauteur*(7/8), p4.y(),  n3.x, n3.y, n3.z, 7/8, 0.0},
        {p4.x(), hauteur*(8/8), p4.y(),  n3.x, n3.y, n3.z, 1.0, 0.0},
    };



    Ogre::VertexDeclaration * decl = Ogre::HardwareBufferManager::getSingleton().createVertexDeclaration();
    decl->addElement(0,0,VET_FLOAT3,VES_POSITION);
    decl->addElement(0,sizeof(float)*3,VET_FLOAT3,VES_NORMAL);
    decl->addElement(0,sizeof(float)*6,VET_FLOAT2,VES_TEXTURE_COORDINATES,0);

    Ogre::PatchMeshPtr mPatch;
    mPatch = Ogre::MeshManager::getSingleton().createBezierPatch(nom,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,(float *)verts,decl,9,9,maxlevel,maxlevel,Ogre::PatchSurface::VS_BOTH);

    mPatch->setSubdivision(subdiv);

    Ogre::Entity * entPatch = mSceneMgr->createEntity("Patch"+nom,nom);
    entPatch->setMaterialName(nomMat);
    entPatch->setCastShadows(false);

    return entPatch;

}

void Loader::createScene(){


    mWindow = mRoot->initialise(true, "Rendu de salle VAE");
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // Scene manager
    mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "VAE Scene Manager");

    mCamera = mSceneMgr->createCamera("Camera");
    /** # Modifs */
    mCamera->setPosition(Ogre::Vector3(pointDepart.x,180,pointDepart.y));
    /** # */
    mCamera->lookAt(Ogre::Vector3(500,0,500));
    mCamera->setNearClipDistance(5);

    //    mSceneMgr->setSkyBox(true, "skybox");

    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0.1,0.1,0.1));

    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1,1,1));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    node= mSceneMgr->getRootSceneNode();
    nbMur=0;
    nbCourbe=0;
    nbSurelev=0;



    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_TRILINEAR);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);

    this->genererAxes();


    Ogre::Plane plan(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
                "sol", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                plan, 10000, 10000, 100, 100, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);

    //    mCamera->setPolygonMode(PM_WIREFRAME);

    Ogre::Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");


    ent->setCastShadows(true);
    node->attachObject(ent);

    node = node->createChildSceneNode("batard", Ogre::Vector3::ZERO, Quaternion::IDENTITY);


    this->recupererDonnees();

    qDebug() << "TYPESOL=" << typeSol;
    if(typeSol == 1)
        ent->setMaterialName("sol_moquette");
    else if(typeSol == 2)
        ent->setMaterialName("sol_parquet");
    else if(typeSol == 3){
        ent->setMaterialName(QFileInfo(cheminTextSol).baseName().toStdString());
    }
    else {
        ent->setMaterialName("sol_blank");
    }

    mCamera->setPosition(Ogre::Vector3(pointDepart.x,80,pointDepart.y));
    //    ent->setMaterialName("cube");
    //    node->scale(2,2,2);
    //    nodeSurelev->scale(2,2,2);

    //    /** Lumières */

    //    Ogre::Light* light = mSceneMgr->createLight("light1");
    //    light->setDiffuseColour(1.0, 1.0, 1.0);
    //    light->setSpecularColour(1.0, 1.0, 1.0);
    //    light->setPosition(0, 300, 0);
    //    light->setType(Light::LT_DIRECTIONAL);
    //    light->setDire    Ogre::SceneNode* bukake;

    //    }ction(10.0, 10.0, 10);
    //    light->setAttenuation(1000, 1.0, 0.045, 0.0075);
    //    light->setVisible(true);

    //    light->setCastShadows(true);

    //    /** Lignes de projos */

//    Ogre::Light* projo = mSceneMgr->createLight("projo");
//    projo->setDiffuseColour(1.0, 1.0, 1.0);
//    projo->setSpecularColour(1.0, 1.0, 1.0);
//    projo->setType(Light::LT_SPOTLIGHT);
//    projo->setPosition(400,400,400);
//    projo->setDirection(500,0,500);
//    projo->setSpotlightRange(Degree(30), Degree(60), 1.0);
//    projo->setVisible(true);


//    projo->setCastShadows(true);

    Ogre::Light* pt = mSceneMgr->createLight("pt");
    pt->setDiffuseColour(1.0, 1.0, 1.0);
    pt->setSpecularColour(1.0, 1.0, 1.0);
    pt->setType(Light::LT_POINT);
    pt->setPosition(pointDepart.x, 2000, pointDepart.y);
    pt->setVisible(true);


    pt->setCastShadows(true);


}

void Loader::createFrameListener(){
    GestionnaireEntree *mInputListener;
    //    QPolygonF poly;
    //    foreach (QPointF pt, polygone) {
    //        poly.append(pt);
    //    }

    //    Ogre::SceneNode *collade = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeCollision", Ogre::Vector3::ZERO, Quaternion::IDENTITY);
    //    collade->attachObject(creerSurelevation("surelevCollision","cube_x",polygone,10));


    mInputListener = new GestionnaireEntree(mWindow, mCamera, node,nbMur,nbCourbe,hauteurMur,mSceneMgr);
    mRoot->addFrameListener(mInputListener);
}

bool Loader::start()
{
    mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
    /** # Modifs */
    pointDepart.x = 0;
    pointDepart.y = 0;
    typeSol=0;
    /** # */
    this->preparerMedias();
    this->chargerRessources();
    this->createScene();
    this->createFrameListener();

    while(true)
    {
        Ogre::WindowEventUtilities::messagePump();

        if(mWindow->isClosed())
            return false;

        if(!mRoot->renderOneFrame())
            return false;
    }

    return true;
}

Entity* Loader::creerMur(String nom, String nomMat, QPointF p1, QPointF p2, Real hauteur, int maxlevel, float subdiv){

    Ogre::Vector3 n1 = Ogre::Math::calculateBasicFaceNormal(
                Ogre::Vector3(p1.x(),5,p1.y()),
                Ogre::Vector3(p2.x()-p1.x(),0,p2.y()-p1.y()),
                Ogre::Vector3((p2.x()+p1.x())/2,1,(p2.y()+p1.y())/2));


    PatchVertex verts[9] =
    {

        {p1.x(), hauteur*(0/2), p1.y(), n1.x, n1.y, n1.z, 0, 0.0},
        {p1.x(), hauteur*(1/2), p1.y(),  n1.x, n1.y, n1.z, 1/2, 0.0},
        {p1.x(), hauteur*(2/2), p1.y(),  n1.x, n1.y, n1.z, 2/2, 0.0},

        {(p1.x()+p2.x())/2, hauteur*(0/2), (p1.y()+p2.y())/2, n1.x, n1.y, n1.z, 0, 0.5},
        {(p1.x()+p2.x())/2, hauteur*(1/2), (p1.y()+p2.y())/2,  n1.x, n1.y, n1.z, 1/2, 0.5},
        {(p1.x()+p2.x())/2, hauteur*(2/2), (p1.y()+p2.y())/2,  n1.x, n1.y, n1.z, 2/2, 0.5},

        {p2.x(), hauteur*(0/2), p2.y(), n1.x, n1.y, n1.z, 0, 1.0},
        {p2.x(), hauteur*(1/2), p2.y(),  n1.x, n1.y, n1.z, 1/2, 1.0},
        {p2.x(), hauteur*(2/2), p2.y(),  n1.x, n1.y, n1.z, 2/2, 1.0},

    };



    Ogre::VertexDeclaration * decl = Ogre::HardwareBufferManager::getSingleton().createVertexDeclaration();
    decl->addElement(0,0,VET_FLOAT3,VES_POSITION);
    decl->addElement(0,sizeof(float)*3,VET_FLOAT3,VES_NORMAL);
    decl->addElement(0,sizeof(float)*6,VET_FLOAT2,VES_TEXTURE_COORDINATES,0);

    Ogre::PatchMeshPtr mPatch;
    mPatch = Ogre::MeshManager::getSingleton().createBezierPatch(nom,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,(float *)verts,decl,3,3,maxlevel,maxlevel,Ogre::PatchSurface::VS_BOTH);

    mPatch->setSubdivision(subdiv);

    Ogre::Entity * entPatch = mSceneMgr->createEntity("Mur"+nom,nom);
    entPatch->setMaterialName(nomMat);
    entPatch->setCastShadows(false);

    return entPatch;

}

ManualObject* Loader::creerSurelevation(String nom, String nomMat, QList<QPointF> liste, Real hauteur){

    //qDebug() << "Debut du dessin...";
    ManualObject* maSurelev = new ManualObject(nom);
    maSurelev->begin(nomMat,Ogre::RenderOperation::OT_TRIANGLE_STRIP);


    int i=0;
    QVector3D n;

    QList<QPointF>::Iterator it;
    //qDebug() << "Première boucle...";
    for( int j =0; j < liste.size(); j++ )
    {
        if(j <= liste.size()-2){

            QLineF l1 = QLineF(liste.at(j),liste.at(j+1)).unitVector();
            QVector3D f1 = QVector3D(l1.x2(),l1.y2(),0);

            QVector3D f2 = QVector3D(0.0,0.0,hauteur);
            n = QVector3D::normal(f1, f2);

            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,1);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;
            j++;
            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,1);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;

            //maSurelev->normal(n.x(), n.y(), n.z());

        }
    }

    QLineF l1 = QLineF(liste.last(),liste.first()).unitVector();
    QVector3D f1 = QVector3D(l1.x2(),l1.y2(),0);

    QVector3D f2 = QVector3D(0.0,0.0,hauteur);
    n = QVector3D::normal(f1, f2);


    maSurelev->position(liste.last().x(), hauteur, liste.last().y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,1);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.last().x(), 0.0, liste.last().y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;
    maSurelev->position(liste.first().x(), hauteur, liste.first().y());
    maSurelev->index(i);
    maSurelev->textureCoord(1,1);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.first().x(), 0.0, liste.first().y());
    maSurelev->index(i);
    maSurelev->textureCoord(1,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.at(1).x(), hauteur, liste.at(1).y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,1);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.at(1).x(), 0.0, liste.at(1).y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    for( int j =1; j < liste.size(); j++ )
    {
        if(j < liste.size()-1){

            l1 = QLineF(liste.at(j),liste.at(j-1)).unitVector();
            f1 = QVector3D(l1.x2(),l1.y2(),0);

            f2 = QVector3D(0.0,0.0,hauteur);
            n = QVector3D::normal(f1, f2);

            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,1);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;
            j++;
            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,1);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,0);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;

            //maSurelev->normal(n.x(), n.y(), n.z());

        }
    }

    maSurelev->end();
    for(int i=0; i< liste.size()-1; i++){
        if(i < liste.size()-2){
            int k = 0;

            maSurelev->begin(nomMat);
            QLineF l1 = QLineF(liste.at(i),liste.at(i+1)).unitVector();
            QVector3D f1 = QVector3D(l1.x2(),0,l1.y2());
            QVector3D f2 = QVector3D(l1.x2(),0,0);
            QVector3D n = QVector3D::normal(f1, f2);


            maSurelev->position(liste.at(i).x(), hauteur, liste.at(i).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;

            maSurelev->position(liste.at(i+1).x(), hauteur, liste.at(i+1).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;

            maSurelev->position(liste.at(i+1).x(), 0.0, liste.at(i+1).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;

            maSurelev->position(liste.at(i).x(), 0.0, liste.at(i).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;
            maSurelev->triangle(0,2,3);
            maSurelev->triangle(0,1,2);
            maSurelev->end();
        }
    }

    int k = 0;

    l1 = QLineF(liste.last(),liste.first()).unitVector();
    f1 = QVector3D(l1.x2(),0,l1.y2());
    f2 = QVector3D(l1.x2(),0,0);
    n = QVector3D::normal(f1, f2);

    maSurelev->begin(nomMat);
    maSurelev->position(liste.at(liste.size()-2).x(), hauteur, liste.at(liste.size()-2).y());
    maSurelev->index(0);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.at(liste.size()-1).x(), hauteur, liste.at(liste.size()-1).y());
    maSurelev->index(1);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.at(liste.size()-1).x(), 0.0, liste.at(liste.size()-1).y());
    maSurelev->index(2);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.at(liste.size()-2).x(), 0.0, liste.at(liste.size()-2).y());
    maSurelev->index(3);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->triangle(0,2,3);
    maSurelev->triangle(0,1,2);


    maSurelev->end();

    maSurelev->begin(nomMat);
    maSurelev->position(liste.last().x(), hauteur, liste.last().y());
    maSurelev->index(0);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.first().x(), hauteur, liste.first().y());
    maSurelev->index(1);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.first().x(), 0.0, liste.first().y());
    maSurelev->index(2);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.last().x(), 0.0, liste.last().y());
    maSurelev->index(3);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->triangle(0,2,3);
    maSurelev->triangle(0,1,2);


    maSurelev->end();

    // Petit capuchon
    maSurelev->begin(nomMat,Ogre::RenderOperation::OT_TRIANGLE_FAN);

    l1 = QLineF(liste.first(),liste.last()).unitVector();
    f1 = QVector3D(l1.x2(),l1.y2(),0);

    QLineF l2 = QLineF(liste.first(),liste.at(1)).unitVector();
    f2 = QVector3D(l2.x2(),l2.y2(),0);
    n = QVector3D::normal(f1, f2);

    QPolygonF poly;
    foreach (QPointF p, liste) {
        poly.append(p);
    }
    QPointF centre;
    if(poly.containsPoint(poly.boundingRect().center(),Qt::OddEvenFill)){
        centre = poly.boundingRect().center();
    }
    else {
        foreach (QPointF p, liste) {
            if(poly.containsPoint(p,Qt::OddEvenFill)){
                centre = p;
            }
        }
    }

    maSurelev->position(centre.x(), hauteur, centre.y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;

    foreach (QPointF p, liste) {
        maSurelev->position(p.x(), hauteur, p.y());
        maSurelev->index(k);
        maSurelev->textureCoord(1,0);
        maSurelev->normal(-n.x(), -n.y(),-n.z());
        k++;
    }

    for(int l= liste.size()-1; l>=0; l--){
        maSurelev->position(liste.at(l).x(), hauteur, liste.at(l).y());
        maSurelev->index(k);
        maSurelev->textureCoord(1,0);
        maSurelev->normal(1,1,1);
        k++;
    }

    maSurelev->position(liste.last().x(), hauteur, liste.last().y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;

    maSurelev->position(liste.first().x(), hauteur, liste.first().y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;


    maSurelev->end();
    maSurelev->setCastShadows(true);



    return maSurelev;
}



/*

ManualObject* Loader::creerSurelevation_old(String nom, String nomMat, QList<QPointF> liste, Real hauteur){

    //qDebug() << "Debut du dessin...";
    ManualObject* maSurelev = new ManualObject(nom);
    maSurelev->begin(nomMat,Ogre::RenderOperation::OT_TRIANGLE_STRIP);


    int i=0;
    QVector3D n;

    QList<QPointF>::Iterator it;
    //qDebug() << "Première boucle...";
    for( int j =0; j < liste.size(); j++ )
    {
        if(j <= liste.size()-2){

            QLineF l1 = QLineF(liste.at(j),liste.at(j+1)).unitVector();
            QVector3D f1 = QVector3D(l1.x2(),l1.y2(),0);

            QVector3D f2 = QVector3D(0.0,0.0,hauteur);
            n = QVector3D::normal(f1, f2);

            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,1);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;
            j++;
            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,1);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            i++;

            //maSurelev->normal(n.x(), n.y(), n.z());

        }
    }

    //qDebug() << "Liaison des derniers points...";
    //qDebug() << "ok";

    QLineF l1 = QLineF(liste.last(),liste.first()).unitVector();
    QVector3D f1 = QVector3D(l1.x2(),l1.y2(),0);

    QVector3D f2 = QVector3D(0.0,0.0,hauteur);
    n = QVector3D::normal(f1, f2);


    maSurelev->position(liste.last().x(), hauteur, liste.last().y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,1);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.last().x(), 0.0, liste.last().y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;
    maSurelev->position(liste.first().x(), hauteur, liste.first().y());
    maSurelev->index(i);
    maSurelev->textureCoord(1,1);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.first().x(), 0.0, liste.first().y());
    maSurelev->index(i);
    maSurelev->textureCoord(1,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.at(1).x(), hauteur, liste.at(1).y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,1);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;

    maSurelev->position(liste.at(1).x(), 0.0, liste.at(1).y());
    maSurelev->index(i);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    i++;


    //qDebug() << "Deuxième boucle...";
    for( int j =1; j < liste.size(); j++ )
    {
        if(j < liste.size()-1){

            l1 = QLineF(liste.at(j),liste.at(j-1)).unitVector();
            f1 = QVector3D(l1.x2(),l1.y2(),0);

            f2 = QVector3D(0.0,0.0,hauteur);
            n = QVector3D::normal(f1, f2);

            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,1);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;
            j++;
            maSurelev->position(liste.at(j).x(), hauteur, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,1);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;

            maSurelev->position(liste.at(j).x(), 0.0, liste.at(j).y());
            maSurelev->index(i);
            maSurelev->textureCoord(1,0);
            maSurelev->normal(n.x(), n.y(),n.z());
            i++;

            //maSurelev->normal(n.x(), n.y(), n.z());

        }
    }

    maSurelev->end();

    //qDebug() << "Troisieme boucle...";
    for(int i=0; i< liste.size()-1; i++){
        if(i < liste.size()-2){
            int k = 0;

            maSurelev->begin(nomMat);
            QLineF l1 = QLineF(liste.at(i),liste.at(i+1)).unitVector();
            QVector3D f1 = QVector3D(l1.x2(),0,l1.y2());
            QVector3D f2 = QVector3D(l1.x2(),0,0);
            QVector3D n = QVector3D::normal(f1, f2);


            maSurelev->position(liste.at(i).x(), hauteur, liste.at(i).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;

            maSurelev->position(liste.at(i+1).x(), hauteur, liste.at(i+1).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;

            maSurelev->position(liste.at(i+1).x(), 0.0, liste.at(i+1).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;

            maSurelev->position(liste.at(i).x(), 0.0, liste.at(i).y());
            maSurelev->index(k);
            maSurelev->textureCoord(0,0);
            maSurelev->normal(-n.x(), -n.y(),-n.z());
            k++;
            maSurelev->triangle(0,2,3);
            maSurelev->triangle(0,1,2);
            maSurelev->end();
        }
    }

    int k = 0;

    l1 = QLineF(liste.last(),liste.first()).unitVector();
    f1 = QVector3D(l1.x2(),0,l1.y2());
    f2 = QVector3D(l1.x2(),0,0);
    n = QVector3D::normal(f1, f2);



    //qDebug() << "Liaison des derniers points (2)...";
    maSurelev->begin(nomMat);
    maSurelev->position(liste.at(liste.size()-2).x(), hauteur, liste.at(liste.size()-2).y());
    maSurelev->index(0);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.at(liste.size()-1).x(), hauteur, liste.at(liste.size()-1).y());
    maSurelev->index(1);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.at(liste.size()-1).x(), 0.0, liste.at(liste.size()-1).y());
    maSurelev->index(2);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.at(liste.size()-2).x(), 0.0, liste.at(liste.size()-2).y());
    maSurelev->index(3);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->triangle(0,2,3);
    maSurelev->triangle(0,1,2);


    maSurelev->end();


    //qDebug() << "Liason des derniers et avant derniers (3)...";
    maSurelev->begin(nomMat);
    maSurelev->position(liste.last().x(), hauteur, liste.last().y());
    maSurelev->index(0);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.first().x(), hauteur, liste.first().y());
    maSurelev->index(1);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.first().x(), 0.0, liste.first().y());
    maSurelev->index(2);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->position(liste.last().x(), 0.0, liste.last().y());
    maSurelev->index(3);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());

    maSurelev->triangle(0,2,3);
    maSurelev->triangle(0,1,2);


    maSurelev->end();

    // Petit capuchon
    //qDebug() << "boucle du capuchon...";
    maSurelev->begin(nomMat,Ogre::RenderOperation::OT_TRIANGLE_FAN);

    l1 = QLineF(liste.first(),liste.last()).unitVector();
    f1 = QVector3D(l1.x2(),l1.y2(),0);

    QLineF l2 = QLineF(liste.first(),liste.at(1)).unitVector();
    f2 = QVector3D(l2.x2(),l2.y2(),0);
    n = QVector3D::normal(f1, f2);

    QPolygonF poly;
    foreach (QPointF p, liste) {
        poly.append(p);
        //qDebug() << "POINT :" << p;
    }


    //qDebug() << "NORMALE :" << n;
    QPointF centre;
    if(poly.containsPoint(poly.boundingRect().center(),Qt::OddEvenFill)){
        centre = poly.boundingRect().center();
    }
    else {
        foreach (QPointF p, liste) {
            if(poly.containsPoint(p,Qt::OddEvenFill)){
                centre = p;
            }
        }
    }



    //qDebug() << "boucle du capuchon(2)...";
    maSurelev->position(centre.x(), hauteur, centre.y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;

    foreach (QPointF p, liste) {
        maSurelev->position(p.x(), hauteur, p.y());
        maSurelev->index(k);
        maSurelev->textureCoord(1,0);
        maSurelev->normal(-n.x(), -n.y(),-n.z());
        k++;
    }

    //qDebug() << "boucle du capuchon(3)...";
    for(int l= liste.size()-1; l>=0; l--){
        maSurelev->position(liste.at(l).x(), hauteur, liste.at(l).y());
        maSurelev->index(k);
        maSurelev->textureCoord(1,0);
        maSurelev->normal(1,1,1);
        k++;
    }

    //qDebug() << "boucle du capuchon(4)...";
    maSurelev->position(liste.last().x(), hauteur, liste.last().y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;

    maSurelev->position(liste.first().x(), hauteur, liste.first().y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;



    //qDebug() << "boucle du capuchon(2)...";
    maSurelev->position(centre.x(), 0, centre.y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;

    foreach (QPointF p, liste) {
        maSurelev->position(p.x(), 0, p.y());
        maSurelev->index(k);
        maSurelev->textureCoord(1,0);
        maSurelev->normal(-n.x(), -n.y(),-n.z());
        k++;
    }

    //qDebug() << "boucle du capuchon(3)...";
    for(int l= liste.size()-1; l>=0; l--){
        maSurelev->position(liste.at(l).x(), 0, liste.at(l).y());
        maSurelev->index(k);
        maSurelev->textureCoord(1,0);
        maSurelev->normal(1,1,1);
        k++;
    }

    //qDebug() << "boucle du capuchon(4)...";
    maSurelev->position(liste.last().x(), 0, liste.last().y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;

    maSurelev->position(liste.first().x(), 0, liste.first().y());
    maSurelev->index(k);
    maSurelev->textureCoord(0,0);
    maSurelev->normal(-n.x(), -n.y(),-n.z());
    k++;


    maSurelev->end();
    maSurelev->setCastShadows(true);



    return maSurelev;
}



*/



ManualObject* Loader::creerTableau(String nom, String nomMat, Real longueur, Real hauteur, bool ext){

    ManualObject* monTab = new ManualObject(nom);
    monTab->begin(nomMat);


    //    if(!ext){
    // face 1
    monTab->position(0.0,0.0,0.0); //1
    monTab->normal(0,0,1);
    monTab->textureCoord(0,0,0);

    monTab->position(longueur,0.0,0.0); //2
    monTab->normal(0,0,1);
    monTab->textureCoord(1,0,0);

    monTab->position(longueur,hauteur,0.0); //3
    monTab->normal(0,0,1);
    monTab->textureCoord(1,1,0);

    monTab->position(0.0,hauteur,0.0); //4
    monTab->normal(0,0,1);
    monTab->textureCoord(0,1,0);


    monTab->quad(3,2,1,0);

    //    }
    //    else {
    //        monTab->position(0.0,0.0,7); //1
    //        monTab->normal(0,0,-1);
    //        monTab->textureCoord(0,0,0);

    //        monTab->position(longueur,0.0,7); //2
    //        monTab->normal(0,0,-1);
    //        monTab->textureCoord(1,0,0);

    //        monTab->position(longueur,hauteur,7); //3
    //        monTab->normal(0,0,-1);
    //        monTab->textureCoord(1,1,0);

    //        monTab->position(0.0,hauteur,7); //4
    //        monTab->normal(0,0,-1);
    //        monTab->textureCoord(0,1,0);


    //        monTab->quad(0,1,2,3);

    //    }


    monTab->end();
    monTab->setCastShadows(false);

    return monTab;
}


QString Loader::genererMaterial(QString nom, QString TU, double scale){
    QString mat;
    mat = QString("material "+nom+"\n");
    mat += QString("{\ntechnique\n\t{\n\tpass\n\t\t{\n\t\t\tambient 1.0 1.0 1.0\n\t\t\tdiffuse 1.0 0.5 0.0\n\t\t\ttexture_unit\n\t\t\t{\n\t\t\t\ttexture "+TU+"\n");
    mat += QString("\t\t\t\tscale ") + QString::number(scale) + QString(" ") + QString::number(scale) + QString("\n\t\t\t}\n\t\t}\n\t}\n}\n\n");
    return mat;
}










