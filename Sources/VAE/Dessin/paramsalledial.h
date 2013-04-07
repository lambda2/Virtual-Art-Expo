#ifndef PARAMSALLEDIAL_H
#define PARAMSALLEDIAL_H

#include <QDialog>
#include "projet.h"
#include "listeimages.h"



namespace Ui {
class ParamSalleDial;
}

class ParamSalleDial : public QDialog
{
    Q_OBJECT
    
public:
    explicit ParamSalleDial(QWidget *parent = 0);
    ~ParamSalleDial();
    
private:
    Ui::ParamSalleDial *ui;

signals:
    void hauteurChangee(qreal hauteur);
    void sigListeChangee(Sol ind);
    void sigActualiserMiniatures();
    void sigCheckAffImgChange(bool check);
    void cheminTextureImageChangee(QString chemin);
    void tailleTextureImageChangee(double taille);



public slots:
    void spinboxChangee(double val);
    void listeChangee(int index);
    void reconfigurer();
    void afficherBarre(bool aff=true);
    void setValeurBarre(int valeur);
    void actualiserMiniatures();
    void checkAffichageTabChange(bool check);
    void boutonParcourirPresse();
    void tailleTextureChangee(double taille);


};

#endif // PARAMSALLEDIAL_H
