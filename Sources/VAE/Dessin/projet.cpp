#include "projet.h"

Projet::Projet()
{
    this->initialiser();
    nom = "Projet sans titre";
    date = QDate::currentDate();
    description = "Aucune description";
    monSol = Aucun;
    repertoire = QDir::homePath() + "/Virtual Art Expo";
    this->creerRepertoiresUtilisateur();
}

Projet::Projet(QString _nom, QDir rep, QString desc, QDate _date, Sol sol) {
    nom = _nom;
    date = _date;
    description = desc;
    repertoire = rep;
    repertoire.setPath(repertoire.path() + "/" + nom);
    monSol = sol;
    this->creerRepertoiresUtilisateur();
}

bool Projet::isValide(){
    qDebug() << "valide [entre]";
    bool valide = false;
    if(this->getDate().isValid()
            && !this->getNom().isEmpty()){
        qDebug() << "   -> date & nom & rep valide";
        if(this->repertoire.exists()){
            qDebug() << "   -> repertoire existe";
            if(QDir(repertoire.path() + "/bibliotheque").exists()){
                qDebug() << "   -> blibliotheque existe";
                valide = true;
            }
        }

    }
    else{
        qDebug() << "Salle invalide : " << this->getDate() << "," << this->getNom();
    }
    return valide;
}

QString Projet::getNom() {
    return nom;
}

void Projet::setNom(QString _nom){
    nom = _nom;
}

QString Projet::getDescription(){
    return description;
}

void Projet::setDescription(QString _desc){
    description = _desc;
}

QDate Projet::getDate(){
    return date;
}

void Projet::setDate(QDate _date){
    date = _date;
}

QDir Projet::getRepertoire(){
    return repertoire;
}

void Projet::setRepertoire(QDir _dir){
    repertoire = _dir;
}

QString Projet::getCheminSave(){
    qDebug() << repertoire.path() + "/" + nom + ".ensp";
    return QString(repertoire.path() + "/" + nom + ".ensp");
}

QString Projet::getChemin(){
    return QString(repertoire.path());
}

QString Projet::getRepertoireImages(){
    return QString(getChemin() + "/bibliotheque");
}

bool Projet::initialiser(){

    if(!repertoire.mkdir(QDir::homePath() + "/Virtual Art Expo")){
//        QMessageBox msg;
//        msg.setText("Virtual Art Expo n'est pas parvenu a créer les répertoires du projet par défaut");
//        msg.setWindowTitle("Erreur");
//        msg.exec();
        return false;
    }
    return true;

}

bool Projet::creerRepertoiresUtilisateur(){
    if(!repertoire.exists()){
        if(!repertoire.mkpath(repertoire.path())){

            return false;
        }
    }
    qDebug() << "D> repertoire crée (101) : " << repertoire.path();
    if(!QDir(repertoire.path() + "/bibliotheque").exists()){
        if(!repertoire.mkdir(repertoire.path() + "/bibliotheque")){
//            QMessageBox msg;
//            msg.setText("Virtual Art Expo n'est pas parvenu a créer la bibliothàque du projet");
//            msg.setWindowTitle("Erreur");
//            msg.exec();
            return false;
        }
    }
    return true;


}

bool Projet::sauvegarderSalle(VueHaut *vue){
    Sauvegarde save(vue);
    if(!save.Sauvegarder(this->getCheminSave())){
        if(!QFile(this->getCheminSave()).exists()){
        QMessageBox msg;
        msg.setText("Virtual Art Expo n'est pas parvenu a sauvegarder le projet");
//        msg.setText("Url = " + this->getCheminSave());
        msg.setWindowTitle("Erreur");
        msg.exec();
        }
        return false;
    }
    else
        return true;
}

bool Projet::enregistrer(VueHaut *vue){

}

void Projet::setSol(Sol _sol){
    qDebug() << "le sol a changé, il est maintenant en " << _sol;
    this->monSol = _sol;
}

Sol Projet::getSol(){
    return monSol;
}
