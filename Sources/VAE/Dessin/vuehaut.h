#ifndef VUEHAUT_H
#define VUEHAUT_H

#include <QtGui>
#include <QtSvg>
#include "mur.h"
#include "sauvegarde.h"
#include "courbe.h"
#include "fenetre.h"
#include <surelevation.h>
#include <objet3d.h>

class Fenetre;
class Courbe;

class VueHaut : public QGraphicsScene
{
        Q_OBJECT
    public:
        enum Mode {
            AjoutMur,//0 On commence a tracer un mur
            AjoutCourbe,//1 On commence a tracer une courbe
            DessinMur,//2 On a placé le premier point du mur
            DessinCourbe,//3 On a placé le premier point de la courbe
            SupprSel,//4 Ne sert a rien
            MurSelectionne,//5 Quand un mur est déja sélectionné et qu'il va etre déplacé
            PointControleSelectionne,//6
            CourbeSelectionne,//7
            MursSelectionnes,//8
            SelectionEnCours,//9
            AjoutObjet,//10
            Select,//11
            AjoutSurelevation,//12
            CreationSurelevation,//13
            SurelevationSelectionne,//14
            PointSurelevationSelectionne, // 15
            ElementsSelectionnes, //16 Elements sélectionnées mais ne bougent pas !
            ElementsSelectionnesEnMouvement, //17 Elements selectionnes En Mouvement
            ObjetSelectionne, // Un objet est selectionne
            PlacementDepart
        };

        enum PartieMur {
            Debut,
            Fin,
            Base
        };

        enum PartieCourbe {
            DebutC,
            FinC,
            PointUn,
            PointDeux,
            BaseC
        };

        enum Modificateur {
            Aucun,
            MAJ,
            CTRL,
            ALT
        };

        explicit VueHaut(Fenetre *fentre,QObject *parent = 0);
        VueHaut(VueHaut &other);
//      VueHaut& operator =(const VueHaut& autreCourbe);
        Mode getMode();
        int getEchelle();
        double getHauteurSalle();
        QRectF approxProches(const QPointF &point);
        QRectF cerclePoint(const QPointF &point);
        QList<Mur *> listeDesMurs();
        QList<Courbe *> listeDesCourbes();
        QList<Objet3D *> listeDesObjets();
        int getTypeObjets3D();
        bool contientMurs();
        void viderObjets();

        QList<Surelevation *> getSurelevations();
        Fenetre* getFenetre();
        void ajouterSurelevation(Surelevation *sur);

        Mur *murSelectionne();
        void initialiser();
        bool isVerouille();

        QList<QGraphicsItem *> objets;
        QList<Mur *> listeDesMursDans(QList<QGraphicsItem *> lst);
        QList<QGraphicsItem *> getObjets();

    private:


        Mur *fantome;
        Mode monMode;
        Modificateur monModificateur;
        int echelle;
        PartieMur partieSelectionnee;
        PartieCourbe partieSelectionneeC;
        bool bouge;
        bool indicateurActif;
        double hauteurSalle;
        Fenetre *maFenetre;
        Mur *murApercuIndic;
        int typeObjet3D;

        QLineF *ligneDeMur;
        QLineF translation;
        Surelevation *surelevEnCours;
        QPainterPath *cheminCourbe;
        QGraphicsRectItem *selectPoint;
        QGraphicsTextItem *mesure;
        QGraphicsTextItem *mesurebis;
        QGraphicsTextItem indicateurMur;
        QList<QGraphicsPixmapItem *> apercusIndicateur;
        QList<QGraphicsItem *> pressePapier;
        QList<Surelevation *> surelevations;
        QList<QGraphicsEllipseItem *> pointsSurelevation;
        QList<QGraphicsLineItem *> represTableaux;
        QObject *main;
        QPoint3D *pointSurelev;
        QPointF pointSelection;
        QRectF zoneSelection;

        QGraphicsRectItem *pointCourbeUn;
        QGraphicsRectItem *pointCourbeDeux;
        QGraphicsEllipseItem *pointRotationObjet;
        QGraphicsEllipseItem centreCamera;
//        QGraphicsSvgItem *flecheNormale;

        QGraphicsRectItem graphiqueSelection;
        int force;
        int decalageCopie;
        bool contenuCopie;


        int nombreDeMursDans(QList<QGraphicsItem *> lst);
        int nombreDeCourbesDans(QList<QGraphicsItem *> lst);
        int nombreDElementsDans(QList<QGraphicsItem *> lst);
        int nombreDeSurelevationsDans(QList<QGraphicsItem *> lst);
        int nombreDObjetsDans(QList<QGraphicsItem *> lst);
        QList<Courbe *> listeDesCourbesDans(QList<QGraphicsItem *> lst);
        QList<QGraphicsSurelevationItem *> listeDesSurelevationsDans(QList<QGraphicsItem *> lst);
        QList<QGraphicsItem *> listeDesElementsDans(QList<QGraphicsItem *> lst);
        QList<Objet3D *> listeDesObjetsDans(QList<QGraphicsItem *> lst);

        void peindre(const QPen &pen, QList<QGraphicsItem *> liste);

        bool superpose;
        bool modifing;
        bool unDeux;

        bool getModifing();
        void setModifing(bool modif);

        int getAngleBrique(const qreal angle) const;
        int getLongueurBrique(const qreal longueur) const;

        Modificateur getModificateur();

        void viderPressePapier();

        QPen *penMurEnCours;
        QPen *penMurFini;
        QPen *penMurSelectionne;
        QPen *penMurMobile;
        QPen *penMurNonAffichable;
        QPen *penSelection;

        // Menus

        void initialiserMenus();

        QMenu *menuUnMur;
        QMenu *menuUnMurVerr;

        // Elements des menus

        QAction *supprMurAct;
        QAction *passerEnVueDeFaceAct;
        QAction *changerCoteAct;

        // Booléen de verouillage

        bool verouille;

        QRectF *faceUn;
        QRectF *faceDeux;
        QGraphicsRectItem *rectUn;
        QGraphicsRectItem *rectDeux;

    signals:
        void unMurEstSelectionne();
        void desMursSontSelectionnes();
        void aucunMurEstSelectionne();
        void deuxMursSontSelectionnes();

        void uneCourbeEstSelectionnee();
        void uneSurelevationEstSelectionnee();

        void unObjetEstSelectionne();

        void longueurSelectModifiee(double d);
        void angleSelectModifie(int angle);
        void angleObjetSelectModifie(int angle);
        void murAffichable(bool aff);
        void murMobile(bool mob);
        void sceneModifiee(); // Définit si le document a besoin d'Ãªtre sauvegardé
        void elementAColler();
        void rouletteAvant();
        void rouletteArriere();
        void translationDemandee(qreal dx, qreal dy);
        void sceneChangee(); // Enregistrer une nouvelle capture pour le Ctrl-Z
        void salleVerouillee();
        void salleDeverouillee();


    public slots:
        void setIndicateur(bool indic);
        void setMode(Mode mode);
        void setModificateur(Modificateur mod);
        void setLongueurMurSelect(double longueur);
        void setAngleMurSelect(int angle);
        void setAngleObjetSelect(int angle);
        void changerTypeObjetSelect(int index);
        void setAngleEntreDeuxMurs(int angle);
        void supprimerMurSelect();
        void setMurSelectMobile(bool mobile);
        void setMurSelectAffichable(bool affichable);
        void copierContenu();
        void collerContenu();
        void couperContenu();
        void appliquerTraits();
        void deplacement(qreal dx, qreal dy);
        void deplacement(QPointF point);
        void modifierHauteurSurelevSelect(double hauteur);
        void modifierHauteurSalle(qreal h);
        void verouillerSalle();
        void deverouillerSalle();
        void majTableaux();
//        QLineF rendreNormale(Mur *mur);
//        void afficherNormaleMurSelect();
//        void echangerMurSelect();
//        void cacherNormale();
        void afficherRectFace();
        void cacherRectFace();
        QPointF genererCentreVueHaut();

        QPointF getCentreCamera();


    protected:
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        void wheelEvent(QGraphicsSceneWheelEvent *event);


};

#endif // VUEHAUT_H
