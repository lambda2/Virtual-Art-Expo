#ifndef FENETRE_H
#define FENETRE_H

#include <QtGui>
#include "mur.h"
#include "vuehaut.h"
#include "vueface.h"
#include "grille.h"
#include "paramsalledial.h"
#include "daiconmachina.h"
#include "listeimages.h"
#include "echelle.h"
#include "projet.h"
#include "objet3d.h"

class VueFace;
class QPorte;
class VueHaut;
class Mur;
class Projet;
class ParamSalleDial;

class Fenetre : public QMainWindow
{
        Q_OBJECT

    protected:
        void closeEvent(QCloseEvent *event);

    public:
        explicit Fenetre(QWidget *parent = 0);
        Fenetre(QString fichier);
        Fenetre(Projet *proj);
        ~Fenetre();
        void initialiserPrincipale();
        void initialiserZoneSelect();
        void initialiserZoneGrille();
        void initialiserBarreLaterale();
        void initialiserBarreSuperieure();
        void initialiserBarreVueFace();
        void initialiserActions();
        void initialiserConnexions();
        void initialiserMenus();
        void initialiserStatusBar();
        void initialiserEchelle();

        // VueFace

        void initialiserVueDeFace();

        QList<VueHaut *> listeActions;
        void supprimerSuivants();
        bool suivant();
        bool precedant();
        double getHauteur();
        bool repertoirePrepare();

        // Spins mesures vue face

        QDoubleSpinBox *spinHTab;
        QDoubleSpinBox *spinLTab;
        QDoubleSpinBox *spinHDistTab;
        QDoubleSpinBox *spinLDistTab;

        VueHaut* getVueHaut();



    private:

        // grille

        Grille *grille;

        // scene graphique

        VueHaut *sceneVueHaut;

        QGridLayout *layout;
        QGraphicsView *vue;
        QWidget *widgetPrincipal;
        QVBoxLayout *laterale;
        QHBoxLayout *superieure;
        ParamSalleDial *dialParam;
        QTimer monTimer;
        int timeCount;

        // Mur de test

        Mur *test;

        // zone principale

//        QVBoxLayout *zoneBoutons;
//        QPushButton *boutonQuitter;
//        QPushButton *boutonSelectionner;
//        QPushButton *boutonAjouterMur;

        // zone un mur selectionne

        QWidget *widgetParametres;
        QHBoxLayout *layoutParametres;
        QGroupBox *groupeAttributs;
        QPushButton *supprimerMur;
        QPushButton *ajouterPorte;
        QGroupBox *groupeCoordonnees;
        QCheckBox *checkMobile;
        QCheckBox *checkAffichable;
        QHBoxLayout *layoutAttributs;
        QHBoxLayout *layoutCoordonnees;
        QDoubleSpinBox *spinLongueur;
        QLabel *labelSpinLongueur;
        QSpinBox *spinAngle;
        QLabel *labelSpinAngle;

        // zone deux murs selectionnes


        QHBoxLayout *layoutAttributsDeuxMurs;
        QSpinBox *spinAngleDeuxMurs;
        QLabel *labelSpinAngleDeuxMurs;

        // ou plus

        QWidget *widgetParametresDeuxMurs;
        QHBoxLayout *layoutParametresDeuxMurs;
        QGroupBox *groupeAttributsDeuxMurs;
        QPushButton *supprimerMurs;
        QCheckBox *checkMobiles;
        QCheckBox *checkAffichables;

        // ou une surélévation

        QWidget *widgetParametresSurelevation;
        QHBoxLayout *layoutAttributSurelevation;
        QDoubleSpinBox *spinSurelevation;
        QLabel *labelSpinSurelevation;

        // widget grille

        QWidget *widgetGrille;
        QGroupBox *groupeGrille;
        QGridLayout *layoutGrille;
        QDoubleSpinBox *spinGrille;
        QLabel *labelSpinGrille;
        QCheckBox *checkMagnetisme;
        QHBoxLayout *layoutWidgetGrille;

        // widget salle verouillee

        QWidget *widgetMurSelectVerouille;
        QHBoxLayout *layoutMurSelectVerouille;

        // widget Objet3D

        QWidget *widgetObjet;
        QSpinBox *spinAngleObjet;
        QLabel *labelSpinAngleObjet;
        QComboBox *comboChoixType;
        QLabel *labelComboChoixType;
        QHBoxLayout *layoutWidgetObjet;

        // Barre d'outils latérale

        QToolBar *barreLaterale;

        // Barre d'outils supérieure

        QToolBar *barreSuperieure;

        // Barre de la vue de face

        QToolBar *barreVueFace;

        // Explorateur d'images de la vue de face

        QWidget *widgetExplorateur;
        QVBoxLayout *layoutExplorateur;
        QPushButton *boutonImportation;
        ListeImages *vueExplorateur;
        QFileSystemModel *modeleExplorateur;
        DaIconMachina *maMachina;


        // Différentes actions

        // -- menu classique --

        QAction *nouvAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *saveAsAct;
        QAction *fermerAct;
        QAction *exitAct;
        QAction *couperAct;
        QAction *copierAct;
        QAction *collerAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *fullScreenAct;
        QAction *paramSalleAct;

        // -- Barre d'outils --

        QAction *selectionnerAct;
        QAction *dessinerMurAct;
        QAction *afficherGrilleAct;
        QAction *dessinerCourbeAct;
        QAction *supprimerAct;
        QAction *dessinerSurelevationAct;
        QAction *verouillerAct;

        // Menus

        QMenu *menuFichier;
        QMenu *menuEdition;
        QMenu *menuAide;

        // Relatifs à la sauvegarde

        void chargerSalle(const QString &fileName);
        bool enregistrerSalle(const QString &fileName);
        bool devraitEtreSauvegarde();
        bool sansTitre;
        bool modifie;
        QString nomFichier;

        // Annuler / Retablir
        int iterateur;

        // Vue de face

        VueFace *vueDeFace;
        QAction *passerEnVueFaceAct;
        QAction *passerEnVueHautAct;
        QAction *passerEnVue3DAct;
        QAction *ajouterObjet3DAct;
        QAction *placerPointDepartAct;
        double hauteur;
//        QDir *repertoireUtilisateur;

        QWidget *widgetMesureTab;
        QHBoxLayout *layoutMesureTab;

        // Zone echelle

        Echelle *echelle;

        // Zone Gestion de projet

        Projet *projetCourant;

        // Vue 3D


    public slots:
        void ajouterMur();
        void ajouterCourbe();
        void ajouterSurelevation();
        void selectionner();
        void afficherZoneMurSelect();
        void afficherZoneDeuxMursSelect();
        void afficherZoneMurSelectVerouille();
        void afficherZoneSurelevation();
        void afficherZoneObjetSelect();
        void afficherExplorateur();
        void afficherWidgetTableauSelect();
        void cacherZoneMurSelect();
        void cacherZoneDeuxMursSelect();
        void cacherZoneMurSelectVerouille();
        void cacherZoneSurelevation();
        void cacherExplorateur();
        void cacherZoneObjetSelect();
        void cacherWidgetTableauSelect();
        void setPasGrille(double pas);
        void reactionSelection();
        void reactionDoubleSelection();
        void reactionSelectionMultiple();
        void reactionAucuneSelection();
        void reactionSelectionSurelevation();
        void reactionVerrouillage();
        void reactionDeverrouillage();
        void reactionSelectionObjet();
        void cacherDoubleSpin();
        void afficherDoubleSpin();
        void changerValeurSpinBox(int valeur);
        void changerValeurSpinBoxObjet(int valeur);
        void changerValeurDoubleSpinBox(int valeur);
        void zoomer();
        void dezoomer();
        void deplacementDe(qreal dx, qreal dy);
        void annuler();
        void retablir();
        void pleinEcran();
        void fenetre();

        void preparerRepertoire();
        Projet *getProjetCourant();
        void nouveauProjet(Projet *proj);
        void nouveauProjet();
        void nouveauProjet(QString fichier);
        void setProjet(Projet *pro);
        void setSolProjet(Sol sol);
        void setUrlTextureProjet(QString texture);
        void setTailleTextureProjet(double taille);



        // Verouillage de la salle

        void verouiller();
        void deverouiller();

        // Vue Face
        void passerEnVueDeFace();
        void passerEnVueDeHaut();
        void passerEnVue3D();
        void paramSalle();
        void changerHauteur(qreal h);

        // Objets 3D

        void ajouterObjet3D();

        // Importation des images

        void chargerImages();
        void actualiserLesMiniatures();
        void incrementerImages();
        void placerPtDepart();

    signals:
        void hauteurChangee(qreal h);
        void copieEnCours();
        void finCopie();


    private slots:
        void nouvelleSalle();
        void open();
        bool save();
        bool saveAs();
        void about();
        void documentEstModifie();
        void addToList();




};


#endif // FENETRE_H
