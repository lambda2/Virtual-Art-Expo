#ifndef GESTIONNAIREENTREE_H
#define GESTIONNAIREENTREE_H

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <QtGui>
#include "CollisionTools.h"
#include "myraycasting.h"


class GestionnaireEntree : public Ogre::FrameListener, public Ogre::WindowEventListener
{
public:

    GestionnaireEntree(Ogre::RenderWindow *wnd,
                       Ogre::Camera *camera,Ogre::SceneNode *node,
                       int nbMur,
                       int nbCourbe,
                       int hauteur,
                       Ogre::SceneManager *SceneMgr);
    ~GestionnaireEntree();
    void startOIS();
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual void windowResized(Ogre::RenderWindow* rw);
    virtual void windowClosed(Ogre::RenderWindow* rw);

private:
    Ogre::RenderWindow* mWindow;
    Ogre::Camera*       mCamera;
    Ogre::SceneNode*    mNode;
    int                 mNbMur;
    int                 mNbCourbe;
    int                 mHauteur;

    OIS::InputManager*  mInputManager;
    OIS::Mouse*         mMouse;
    OIS::Keyboard*      mKeyboard;


    bool mToucheAppuyee;

    Ogre::Real mMouvement;
    Ogre::Real mVitesse;
    Ogre::Real mVitesseRotation;

    Ogre::Radian mRotationX;
    Ogre::Radian mRotationY;

    Ogre::SceneManager* mSceneMgr;
    Ogre::Ray rayon;

//    QPolygonF polygone;
};


#endif // GESTIONNAIREENTREE_H
