#include <cstring>
#include "gestionnaireentree.h"

/*
          1-------2
         /|      /|
        / |     / |
       5-------4  |
       |  0----|--3
       | /     | /
       |/      |/
       6-------7
*/

GestionnaireEntree::GestionnaireEntree(
        Ogre::RenderWindow *wnd,
        Ogre::Camera *camera, Ogre::SceneNode *node,
        int nbMur,
        int nbCourbe,
        int hauteur,
        Ogre::SceneManager* SceneMgr)
{
    mWindow = wnd;
    mCamera = camera;
    mNode = node;
    mNbMur = nbMur;
    mNbCourbe = nbCourbe;
    mHauteur=hauteur;
    mSceneMgr=SceneMgr;
    //mCamera->setPolygonMode(Ogre::PM_WIREFRAME);

    mVitesse = 100;
    mVitesseRotation = 0.3;
    mToucheAppuyee = false;
    startOIS();
}

GestionnaireEntree::~GestionnaireEntree()
{
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
}

bool GestionnaireEntree::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    mKeyboard->capture();
    mMouse->capture();

    Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
    mMouvement = mVitesse * evt.timeSinceLastFrame;

    unsigned int touche=0;
    bool dep=true;
    int res=200;
    int distance=200;
    MyRayCasting collision=MyRayCasting();
    //recupere la position de la camera
    Ogre::Vector3 camPos = mCamera->getPosition();//Ogre::Vector3(mCamera->getPosition().x,5,mCamera->getPosition().z);


    //recupere la Direction de la camera
    Ogre::Vector3 camDir = mCamera->getDirection();

    Ogre::Ray cameraRay(camPos, camDir);
    //un vecteur pour stocker la position de l'impact
    Ogre::Vector3 impactPos;

    Ogre::SceneNode* bukake;
    Ogre::Entity* target;
    for(int h=0;h<mNbCourbe;h++)
    {
        bukake=(Ogre::SceneNode*)mSceneMgr->getRootSceneNode()->getChild("nodeCourbe"+Ogre::String(QString::number(h).toStdString()));
        target=(Ogre::Entity*)bukake->getAttachedObject(0);
        touche += collision.RaycastFromRay(cameraRay,target,impactPos,distance);
        if(distance<res)
            res=distance;
    }

    for(int h=0;h<mNbMur;h++)
    {
        bukake=(Ogre::SceneNode*)mSceneMgr->getRootSceneNode()->getChild("batard")->getChild("nodeMur"+Ogre::String(QString::number(h).toStdString()));
        target=(Ogre::Entity*)bukake->getAttachedObject(0);
        touche += collision.RaycastFromRay(cameraRay,target,impactPos,distance);
        if(distance<res)
            res=distance;
    }


    if(res>50)
        dep=true;
    else
        dep=false;

    if(mCamera->getPosition().y+mMouvement<=5 || mCamera->getPosition().y-mMouvement<=5 ){
        dep=false;
        mCamera->setPosition(mCamera->getPosition().x,6,mCamera->getPosition().z);
    }

    if(mCamera->getPosition().y+mMouvement>=mHauteur-5 || mCamera->getPosition().y-mMouvement>=mHauteur-5 ){
        dep=false;
        mCamera->setPosition(mCamera->getPosition().x,mHauteur-6,mCamera->getPosition().z);
    }



    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;
    if(dep){
        if(mKeyboard->isKeyDown(OIS::KC_LEFT) || mKeyboard->isKeyDown(OIS::KC_Q)) // La touche A d'un clavier QWERTY correspond au Q sur un AZERTY
            deplacement.x -= mMouvement;
        if(mKeyboard->isKeyDown(OIS::KC_RIGHT) || mKeyboard->isKeyDown(OIS::KC_D))
            deplacement.x += mMouvement;
        if(mKeyboard->isKeyDown(OIS::KC_UP) || mKeyboard->isKeyDown(OIS::KC_Z)) // W correspond au Z du AZERTY
            deplacement.z -= mMouvement;
        if(mKeyboard->isKeyDown(OIS::KC_DOWN) || mKeyboard->isKeyDown(OIS::KC_S))
            deplacement.z += mMouvement;

    }
    if(mKeyboard->isKeyDown(OIS::KC_W))
        deplacement.z -= mMouvement;
    const OIS::MouseState &mouseState = mMouse->getMouseState();

    mRotationX = Ogre::Degree(-mouseState.Y.rel * mVitesseRotation);
    mRotationY = Ogre::Degree(-mouseState.X.rel * mVitesseRotation);

    mCamera->yaw(mRotationY);
    mCamera->pitch(mRotationX);
    mCamera->moveRelative(deplacement);


    return true;
}

void GestionnaireEntree::startOIS(){
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));

    windowResized(mWindow);
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

}

void GestionnaireEntree::windowResized(Ogre::RenderWindow *rw){
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void GestionnaireEntree::windowClosed(Ogre::RenderWindow* wnd)
{
    if( wnd == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

