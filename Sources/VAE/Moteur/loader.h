#ifndef LOADER_H
#define LOADER_H

#include <OGRE/Ogre.h>



#include <QtXml>
#include <QtGui>
#include "gestionnaireentree.h"

using namespace Ogre;

struct PatchVertex {
        float x, y, z;
        float nx, ny, nz;
        float u, v;
    };


class Loader
{
public:
    Loader();
    Loader(QString fichier);
    ~Loader();
    void reconfigure();
    void createScene();
    bool chargerRessources();
    void createFrameListener();
    void recupererDonnees();
    void preparerMedias();
    QString genererMaterial(QString nom, QString TU, double scale = 1.0);
    ManualObject* genererSol(QList<QPointF> lst);
    void genererAxes();

    Ogre::Entity * creerCourbe(Ogre::String nom, Ogre::String nomMat, QPointF p1, QPointF p2, QPointF p3, QPointF p4, Real hauteur, int maxlevel=4, float subdiv=0.99);
    Ogre::Entity* creerMur(Ogre::String nom, Ogre::String nomMat, QPointF p1, QPointF p2, Real hauteur=50, int maxlevel=4, float subdiv=0.99);
    ManualObject* creerSurelevation(Ogre::String nom, Ogre::String nomMat, QList<QPointF> liste, Real hauteur=1);
    ManualObject* creerTableau(Ogre::String nom, Ogre::String nomMat, Real longueur, Real hauteur, bool ext);
    bool start();
private:
    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::SceneNode *node;
    Ogre::Vector2 pointDepart;
    QString nomFichier;
    QString cheminTextSol;
    double scaleTextSol;
    bool valide;
    int nbMur;
    int nbCourbe;
    int nbSurelev;
    int nbObjets;
    double hauteurMur;
    int typeSol;
};


#endif // LOADER_H
