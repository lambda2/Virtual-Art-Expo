#ifndef MYRAYCASTING_H
#define MYRAYCASTING_H

#include <Ogre.h>

class MyRayCasting
{
public:
    MyRayCasting(); //Constructeur

    //Définit le point résultat du ray casting : (point de départ du rayon, direction, point d'impact)
    static unsigned int RaycastFromRay(Ogre::Ray &camRay,Ogre::Entity *pentity, Ogre::Vector3 &result, int &distance);

private:
    //Obtient des informations sur un mesh
    static void getMeshInformation(Ogre::MeshPtr mesh,
                                   size_t &vertex_count,
                                   Ogre::Vector3* &vertices,
                                   size_t &index_count,
                                   unsigned long* &indices,
                                   const Ogre::Vector3 &position,
                                   const Ogre::Quaternion &orient,
                                   const Ogre::Vector3 &scale);
};

#endif


/*
        //recupere la position de la camera
        Ogre::Vector3 camPos = mCameraMan->getCamera()->getPosition();
        //recupere la Direction de la camera
        Ogre::Vector3 camDir = mCameraMan->getCamera()->getDirection();
        //construit le rayon
        Ogre::Ray cameraRay(camPos, camDir);
        //un vecteur pour stocker la position de l'impact
        Ogre::Vector3 impactPos;
        //methode de marksman modifiee pour recevoir en entree le rayon de la camera
        int i=marksmanRay->RaycastFromRay(cameraRay,ogreHead,impactPos);
        //ecriture dans le log pour debug
        Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(i));
        if(i==2)//la methode renvoie 2 quand le rayon traverse le mesh
*/
