


#ifndef PROJET_H
#define PROJET_H


enum Sol {
    Aucun,
    Moquette,
    Carreaux
};


#include <QtGui>
#include "sauvegarde.h"
#include "vuehaut.h"

class VueHaut;



class Projet

{
public:
    Projet();
    Projet(QString _nom, QDir rep, QString desc = "", QDate _date = QDate::currentDate(), Sol sol=Aucun);
    QString getNom();
    void setNom(QString _nom);
    QString getDescription();
    void setDescription(QString _desc);
    QDate getDate();
    void setDate(QDate _date);
    QDir getRepertoire();
    void setRepertoire(QDir _dir);
    bool initialiser();
    bool creerRepertoiresUtilisateur();
    bool isValide();
    Sol getSol();
    void setSol(Sol _sol);
    QString getCheminSave();
    QString getChemin();
    QString getRepertoireImages();
    QString url_sol;
    double size_sol;

public slots:
    bool enregistrer(VueHaut *vue);
    bool sauvegarderSalle(VueHaut *vue);

private:
    QString nom;
    QString description;
    QDate date;
    QDir repertoire;
    Sol monSol;


};

#endif // PROJET_H
