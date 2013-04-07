#! /bin/bash

echo "------------------------------------------------------------"
echo "Programme d'installation de Virtual Art Expo - 2011 / 2012"
echo "------------------------------------------------------------"
echo "Installation de la bibliothèque OGRE"
sudo add-apt-repository ppa:ogre-team/ogre
sudo apt-get update
sudo apt-get install libogre-dev
wait ${!}
echo "Compilation des sources..."
cd ./VAE
qmake
make -s -w verbose=no
make clean
echo "Installation des dépendances de OGRE..."
cp -R ../Fichiers\ OGRE\ Additionnels/* ./Dessin/
cp -R ../Fichiers\ OGRE\ Additionnels/* ./Moteur/
echo "Configuration de OGRE..."
wait ${!}
cd ./Moteur
./Moteur configure

