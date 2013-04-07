#ifndef VUEFACE_H
#define VUEFACE_H

#include <QtGui>
#include "vuehaut.h"
#include "mur.h"
#include "tableau.h"
#include "qnotification.h"

class VueHaut;
class Mur;

class VueFace : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {
        Select,//0
        TableauSelectionne,//1
        TableauxSelectionnes,//2
        SelectionEnCours,//3
        TableauEnMouvement,//4
        TableauxEnMouvement,//5
        redimensionnement//6
    };

    enum CoinTab {
        HG,
        HD,
        BG,
        BD,
        Base
    };


    explicit VueFace(QObject *parent = 0);
    VueFace(VueHaut *maVueDeHaut = 0);
    VueFace(Mur *monMur);

    QList<Tableau *> listeDesTableaux();
    bool contientTableaux();
    void tuerLaVariable();

private:
    void initialiser();

    VueHaut *vueDeHaut;
    QBrush *brush;
    Mur *monMur;
    Mode monMode;
    CoinTab coin;
    //QNotification *maNot;
    QGraphicsRectItem graphiqueMur;
    QGraphicsTextItem *mesure;
    QGraphicsTextItem *mesureHauteur;
    QGraphicsTextItem *mesureLargeurTab;
    QGraphicsTextItem *mesureHauteurTab;
    QList<QGraphicsItem *> objets;
    QLineF *translation;
    bool haut;
    bool bas;
    bool gauche;
    bool droite;
    QGraphicsRectItem *coinHG;
    QGraphicsRectItem *coinHD;
    QGraphicsRectItem *coinBG;
    QGraphicsRectItem *coinBD;
    unsigned int coef;
    int decalage;
    QPointF pointSelection;
    QRectF zoneSelection;
    QGraphicsRectItem graphiqueSelection;
    QPen *penSelection;
    QPen *penRedimentionnement;
    double widthRedimentionnement;
    double ratio;
    int wa;
    int ha;
    QRectF zoneRedimentionnement;
    QGraphicsRectItem *graphiqueRedimentionnement;
    double heightTab;
    Tableau *tableauSelectionne;



    int nombreDeTableauxDans(QList<QGraphicsItem *> lst);
    void ajouterTableau(QString fichier, QPointF pos);
    void ajouterMesure(Tableau *item);
    void supprimerMesure();
    QRectF approxProches(const QPointF &point);
    void peindre();
    void ajouterCoins(Tableau *tableauSelect);
    void supprimerCoins();
    void majSpin();




// Andre
        QGraphicsSimpleTextItem *texteTitre;
    void initialiserEffets();

    QList<Tableau *> listeDesTableauxDans(QList<QGraphicsItem *> lst);

    QMenu *menuTab;
    QAction *supprTab;

    
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);

signals:
    void rouletteAvant();
    void rouletteArriere();
    void emitheight(Tableau*,double);
    void tableauModifie();

public slots:
    void setMurCourant(Mur *mur = 0);
    void enleverMurCourant();
    void setMode(Mode mode);
    void setCoin(CoinTab mode);
    void supprimerTableauxSelect();


private slots:
    void setHauteur(double hauteur);
    void setLargeur(double largeur);
    void setHeight(double height);
    void setWidth(double width);
    void unTableauEstSelectionne();
    void aucunTableauSelectionne();
};

#endif // VUEFACE_H
