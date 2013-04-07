#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QtGui>
#include "fenetre.h"
#include "nouveauprojet.h"

namespace Ui {
class Accueil;
}

class Accueil : public QWidget
{
    Q_OBJECT
    
public:
    explicit Accueil(QWidget *parent = 0);
    ~Accueil();

public slots:
    void on_boutonCharger_clicked();
    void on_boutonNouveau_clicked();

    
private:
    Ui::Accueil *ui;
};

#endif // ACCUEIL_H
