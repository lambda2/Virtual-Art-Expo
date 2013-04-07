#include "fenetre.h"

Fenetre::Fenetre(QWidget *parent) :
    QMainWindow(parent)
{
    this->preparerRepertoire();
    this->initialiserPrincipale();
    this->initialiserZoneGrille();
    this->initialiserZoneSelect();
    this->initialiserConnexions();
    this->initialiserActions();
    this->nouveauProjet();
    this->initialiserVueDeFace();
    this->initialiserBarreLaterale();
    this->initialiserBarreSuperieure();
    this->initialiserBarreVueFace();
    this->initialiserMenus();


    vue->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    widgetPrincipal = new QWidget;
    widgetPrincipal->setLayout(layout);

    setCentralWidget(widgetPrincipal);
    setWindowTitle(tr("Virtual Art Expo"));
    setUnifiedTitleAndToolBarOnMac(true);
    sceneVueHaut->update();
    this->reactionDeverrouillage();
}

Fenetre::Fenetre(QString fichier){
    this->preparerRepertoire();
    this->initialiserPrincipale();
    this->initialiserZoneGrille();
    this->initialiserZoneSelect();
    this->initialiserConnexions();
    this->initialiserActions();
    this->nouveauProjet(fichier);
    this->initialiserVueDeFace();
    this->initialiserBarreLaterale();
    this->initialiserBarreSuperieure();
    this->initialiserBarreVueFace();
    this->initialiserMenus();


    vue->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    widgetPrincipal = new QWidget;
    widgetPrincipal->setLayout(layout);

    setCentralWidget(widgetPrincipal);
    setWindowTitle(tr("Virtual Art Expo"));
    setUnifiedTitleAndToolBarOnMac(true);
    sceneVueHaut->update();
    this->reactionDeverrouillage();
    //    QFile file(fichier);
    //    if(file.exists()){
    //        this->chargerSalle(fichier);
    //    }
    sansTitre = false;
}

Fenetre::Fenetre(Projet *proj){


    //    this->preparerRepertoire();
    this->initialiserPrincipale();
    this->initialiserZoneGrille();
    this->initialiserZoneSelect();
    this->initialiserConnexions();
    this->nouveauProjet(proj);
    this->initialiserVueDeFace();
    this->initialiserActions();
    this->initialiserBarreLaterale();
    this->initialiserBarreSuperieure();
    this->initialiserBarreVueFace();
    this->initialiserMenus();


    vue->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    widgetPrincipal = new QWidget;
    widgetPrincipal->setLayout(layout);

    setCentralWidget(widgetPrincipal);
    setWindowTitle(tr("Virtual Art Expo"));
    setUnifiedTitleAndToolBarOnMac(true);
    sceneVueHaut->update();
    this->reactionDeverrouillage();
    sansTitre = false;

}

Fenetre::~Fenetre()
{
}

void Fenetre::selectionner(){
    selectionnerAct->setChecked(true);
    dessinerMurAct->setChecked(false);
    dessinerSurelevationAct->setChecked(false);
    dessinerCourbeAct->setChecked(false);
    ajouterObjet3DAct->setChecked(false);
    sceneVueHaut->setMode(VueHaut::Select);
}

void Fenetre::ajouterMur(){
    if(sceneVueHaut->getMode() != VueHaut::AjoutMur){
        dessinerSurelevationAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        selectionnerAct->setChecked(false);
        ajouterObjet3DAct->setChecked(false);
        dessinerMurAct->setChecked(true);
        sceneVueHaut->setMode(VueHaut::AjoutMur);
    }
    else {
        dessinerSurelevationAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        dessinerMurAct->setChecked(false);
        selectionnerAct->setChecked(true);
        ajouterObjet3DAct->setChecked(false);
        sceneVueHaut->setMode(VueHaut::Select);
    }
}

void Fenetre::ajouterCourbe(){
    if(sceneVueHaut->getMode() != VueHaut::AjoutCourbe){
        selectionnerAct->setChecked(false);
        dessinerMurAct->setChecked(false);
        dessinerSurelevationAct->setChecked(false);
        ajouterObjet3DAct->setChecked(false);
        dessinerCourbeAct->setChecked(true);
        sceneVueHaut->setMode(VueHaut::AjoutCourbe);
    }
    else {
        selectionnerAct->setChecked(true);
        dessinerMurAct->setChecked(false);
        dessinerSurelevationAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        ajouterObjet3DAct->setChecked(false);
        sceneVueHaut->setMode(VueHaut::Select);
    }
}

void Fenetre::ajouterSurelevation() {
    if(sceneVueHaut->getMode() != VueHaut::CreationSurelevation){
        dessinerSurelevationAct->setChecked(true);
        selectionnerAct->setChecked(false);
        dessinerMurAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        ajouterObjet3DAct->setChecked(false);
        sceneVueHaut->setMode(VueHaut::CreationSurelevation);
    }
    else {
        dessinerSurelevationAct->setChecked(false);
        dessinerMurAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        ajouterObjet3DAct->setChecked(false);
        selectionnerAct->setChecked(true);
        sceneVueHaut->setMode(VueHaut::Select);
    }
}



void Fenetre::afficherZoneMurSelect(){
    if(sceneVueHaut->contientMurs())
        widgetParametres->show();
}

void Fenetre::cacherZoneMurSelect(){
    widgetParametres->hide();

}

void Fenetre::afficherZoneDeuxMursSelect(){
    if(sceneVueHaut->contientMurs())
        widgetParametresDeuxMurs->show();
}

void Fenetre::cacherZoneDeuxMursSelect(){
    widgetParametresDeuxMurs->hide();
}

void Fenetre::afficherZoneMurSelectVerouille(){
    widgetMurSelectVerouille->show();
}

void Fenetre::cacherZoneMurSelectVerouille() {
    widgetMurSelectVerouille->hide();
}

void Fenetre::afficherZoneSurelevation() {
    widgetParametresSurelevation->show();
}

void Fenetre::cacherZoneSurelevation() {
    widgetParametresSurelevation->hide();
}

void Fenetre::afficherWidgetTableauSelect(){
    widgetMesureTab->show();
}

void Fenetre::cacherWidgetTableauSelect() {
    widgetMesureTab->hide();
}

void Fenetre::afficherZoneObjetSelect(){
    widgetObjet->show();
}

void Fenetre::cacherZoneObjetSelect() {
    widgetObjet->hide();
}

void Fenetre::setPasGrille(double pas){
    grille->setPas(pas);
    sceneVueHaut->update();
}

void Fenetre::initialiserPrincipale(){


    projetCourant = NULL;
    sansTitre = true;
    nomFichier = "Sans titre";
    modifie=false;


    spinHTab = new QDoubleSpinBox;
    spinLTab = new QDoubleSpinBox;
    spinLDistTab = new QDoubleSpinBox;
    spinHDistTab = new QDoubleSpinBox;

    sceneVueHaut = new VueHaut(this,this);
    sceneVueHaut->setSceneRect(QRectF(0, 0, 1000, 1000));
    layout = new QGridLayout;
    laterale = new QVBoxLayout;
    laterale->addStrut(1);

    superieure = new QHBoxLayout;
    layout->addLayout(superieure,0,0,1,0);

    vue = new QGraphicsView(sceneVueHaut);
    vue->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Affichage de l'échelle

    echelle = new Echelle(this);


    grille = new Grille;
    sceneVueHaut->addItem(grille);

    layout->addWidget(vue);
    layout->addWidget(echelle);
    iterateur=0;

    hauteur=1;
    dialParam = new ParamSalleDial(this);

    statusBar()->showMessage("Virtual Art Expo - Bienvenue !",2000);

    //    zoneBoutons = new QVBoxLayout;
    //    boutonQuitter = new QPushButton(tr("Quitter"));
    //    boutonAjouterMur = new QPushButton(tr("Ajouter un mur"));
    //    boutonSelectionner = new QPushButton(tr("Selectionner un mur"));
    //    zoneBoutons->addWidget(boutonQuitter);
    //    zoneBoutons->addWidget(boutonAjouterMur);
    //    zoneBoutons->addWidget(boutonSelectionner);
    //    boutonAjouterMur->setCheckable(true);
    //    zoneBoutons->addStretch(1);
    //    laterale->addLayout(zoneBoutons);
    layout->addLayout(laterale,1,1);
}

void Fenetre::initialiserZoneSelect(){

    // par defaut : pour un Mur

    widgetParametres = new QWidget;
    layoutParametres = new QHBoxLayout(widgetParametres);
    widgetParametres->setLayout(layoutParametres);
    supprimerMur = new QPushButton(tr("Supprimer le mur"));
    supprimerMur->setIcon(QIcon(":/res/supprimer.png"));
    superieure->addWidget(widgetParametres);

    checkMobile = new QCheckBox(tr("Mobile"));
    checkMobile->setChecked(false);
    checkAffichable = new QCheckBox(tr("Affichable"));
    checkAffichable->setChecked(true);
    layoutAttributs = new QHBoxLayout;
    layoutAttributs->addWidget(checkMobile);
    layoutAttributs->addWidget(checkAffichable);
    layoutAttributs->addStretch(1);
    layoutParametres->addLayout(layoutAttributs);

    layoutCoordonnees = new QHBoxLayout;
    spinLongueur = new QDoubleSpinBox;
    spinLongueur->setSuffix(" m");
    spinLongueur->setMinimum(0.01);
    labelSpinLongueur = new QLabel(tr("Longueur :"));
    spinAngle = new QSpinBox;
    spinAngle->setSuffix(tr(" °"));
    spinAngle->setMaximum(361);
    spinAngle->setMinimum(-1);
    labelSpinAngle = new QLabel(tr("Angle :"));
    layoutCoordonnees->addWidget(labelSpinLongueur);
    layoutCoordonnees->addWidget(spinLongueur);
    layoutCoordonnees->addWidget(labelSpinAngle);
    layoutCoordonnees->addWidget(spinAngle);
    layoutParametres->addLayout(layoutCoordonnees);

    widgetParametres->hide();

    // pour deux murs ou plus :

    widgetParametresDeuxMurs = new QWidget;
    layoutParametresDeuxMurs = new QHBoxLayout(widgetParametresDeuxMurs);
    widgetParametresDeuxMurs->setLayout(layoutParametresDeuxMurs);
    supprimerMurs = new QPushButton(tr("Supprimer les murs"));
    supprimerMurs->setIcon(QIcon(":/res/supprimer.png"));
    layoutParametresDeuxMurs->addWidget(supprimerMurs);
    superieure->addWidget(widgetParametresDeuxMurs);

    checkMobiles = new QCheckBox(tr("Les murs sont mobiles"));
    checkMobiles->setChecked(false);
    checkAffichables = new QCheckBox(tr("Les murs sont affichables"));
    checkAffichables->setChecked(true);
    layoutParametresDeuxMurs->addWidget(checkMobiles);
    layoutParametresDeuxMurs->addWidget(checkAffichables);
    layoutParametresDeuxMurs->addStretch(1);

    layoutAttributsDeuxMurs = new QHBoxLayout;
    spinAngleDeuxMurs = new QSpinBox;
    spinAngleDeuxMurs->setSuffix(tr(" °"));
    spinAngleDeuxMurs->setMaximum(361);
    spinAngleDeuxMurs->setMinimum(-1);
    labelSpinAngleDeuxMurs = new QLabel(tr("Angle entre les murs :"));
    layoutAttributsDeuxMurs->addWidget(labelSpinAngleDeuxMurs);
    layoutAttributsDeuxMurs->addWidget(spinAngleDeuxMurs);
    layoutParametresDeuxMurs->addLayout(layoutAttributsDeuxMurs);

    widgetParametresDeuxMurs->hide();

    // pour une surelevation :

    widgetParametresSurelevation = new QWidget;
    layoutAttributSurelevation = new QHBoxLayout(widgetParametresSurelevation);
    widgetParametresSurelevation->setLayout(layoutAttributSurelevation);
    superieure->addWidget(widgetParametresSurelevation);
    spinSurelevation = new QDoubleSpinBox;
    spinSurelevation->setSuffix(tr(" m"));
    spinSurelevation->setMaximum(20.0);
    spinSurelevation->setMinimum(0.1);
    spinSurelevation->setValue(1.0);
    spinSurelevation->setSingleStep(0.1);
    labelSpinSurelevation = new QLabel(tr("Hauteur de la surélévation"));
    layoutAttributSurelevation->addWidget(labelSpinSurelevation);
    layoutAttributSurelevation->addWidget(spinSurelevation);

    widgetParametresSurelevation->hide();

    // pour la salle verouillee

    widgetMurSelectVerouille = new QWidget;
    layoutMurSelectVerouille = new QHBoxLayout(widgetMurSelectVerouille);
    widgetMurSelectVerouille->setLayout(layoutMurSelectVerouille);
    superieure->addWidget(widgetMurSelectVerouille);
    widgetMurSelectVerouille->hide();

    // pour un objet select

    widgetObjet = new QWidget;
    layoutWidgetObjet = new QHBoxLayout(widgetObjet);
    widgetObjet->setLayout(layoutWidgetObjet);

    superieure->addWidget(widgetObjet);
    widgetObjet->hide();
    labelSpinAngleObjet = new QLabel("Orientation");
    spinAngleObjet = new QSpinBox;

    spinAngleObjet->setSuffix(tr(" °"));
    spinAngleObjet->setMaximum(361);
    spinAngleObjet->setMinimum(-1);

    labelComboChoixType = new QLabel("Type d'objet");
    comboChoixType = new QComboBox;
    comboChoixType->addItem("Colonne");

    layoutWidgetObjet->addWidget(labelSpinAngleObjet);
    layoutWidgetObjet->addWidget(spinAngleObjet);
    layoutWidgetObjet->addWidget(labelComboChoixType);
    layoutWidgetObjet->addWidget(comboChoixType);



    // pour la vue de face, tableau select

    widgetMesureTab = new QWidget;
    layoutMesureTab = new QHBoxLayout(widgetMesureTab);
    widgetMesureTab->setLayout(layoutMesureTab);



    spinHTab->setPrefix(tr("Hauteur : "));
    spinHTab->setSuffix(tr(" m"));
    spinHTab->setSingleStep(0.1);
    layoutMesureTab->addWidget(spinHTab);


    spinLTab->setPrefix(tr("Largeur : "));
    spinLTab->setSuffix(tr(" m"));
    spinLTab->setSingleStep(0.1);
    layoutMesureTab->addWidget(spinLTab);


    spinHDistTab->setPrefix(tr("Distance du sol : "));
    spinHDistTab->setSuffix(tr(" m"));
    spinHDistTab->setSingleStep(0.1);
    layoutMesureTab->addWidget(spinHDistTab);

    spinLDistTab->setPrefix(tr("Distance du bord : "));
    spinLDistTab->setSuffix(tr(" m"));
    spinLDistTab->setSingleStep(0.1);
    layoutMesureTab->addWidget(spinLDistTab);

    superieure->addWidget(widgetMesureTab);
    widgetMesureTab->hide();

}

void Fenetre::initialiserConnexions(){


    // Connexion des proriétés d'un mur

    connect(spinLongueur, SIGNAL(valueChanged(double)), sceneVueHaut, SLOT(setLongueurMurSelect(double)));

    connect(sceneVueHaut, SIGNAL(longueurSelectModifiee(double)), spinLongueur, SLOT(setValue(double)));
    //connect(spinAngle, SIGNAL(valueChanged(int)), sceneVueHaut, SLOT(setAngleMurSelect(int)));
    connect(spinAngle, SIGNAL(valueChanged(int)), this, SLOT(changerValeurSpinBox(int)));
    connect(sceneVueHaut, SIGNAL(angleSelectModifie(int)), spinAngle, SLOT(setValue(int)));
    connect(supprimerMur, SIGNAL(clicked()), sceneVueHaut, SLOT(supprimerMurSelect()));

    // Connexion des propriétées de deux murs

    connect(supprimerMurs, SIGNAL(clicked()), sceneVueHaut, SLOT(supprimerMurSelect()));
    //connect(spinAngleDeuxMurs, SIGNAL(valueChanged(int)), sceneVueHaut, SLOT(setAngleEntreDeuxMurs(int)));
    connect(spinAngleDeuxMurs, SIGNAL(valueChanged(int)), this, SLOT(changerValeurDoubleSpinBox(int)));
    connect(sceneVueHaut, SIGNAL(angleSelectModifie(int)), spinAngleDeuxMurs, SLOT(setValue(int)));

    // Connexions de la grille

    connect(spinGrille, SIGNAL(valueChanged(double)), this, SLOT(setPasGrille(double)));

    // Connexions des attributs d'un mur

    connect(checkMobile,SIGNAL(toggled(bool)),sceneVueHaut,SLOT(setMurSelectMobile(bool)));
    connect(checkAffichable,SIGNAL(toggled(bool)),sceneVueHaut,SLOT(setMurSelectAffichable(bool)));
    connect(checkMobiles,SIGNAL(toggled(bool)),sceneVueHaut,SLOT(setMurSelectMobile(bool)));
    connect(checkAffichables,SIGNAL(toggled(bool)),sceneVueHaut,SLOT(setMurSelectAffichable(bool)));
    connect(sceneVueHaut, SIGNAL(murAffichable(bool)), checkAffichable, SLOT(setChecked(bool)));
    connect(sceneVueHaut, SIGNAL(murMobile(bool)), checkMobile, SLOT(setChecked(bool)));
    connect(sceneVueHaut, SIGNAL(aucunMurEstSelectionne()), this, SLOT(reactionAucuneSelection()));
    connect(sceneVueHaut, SIGNAL(unMurEstSelectionne()),this,SLOT(reactionSelection()));
    connect(sceneVueHaut, SIGNAL(deuxMursSontSelectionnes()),this,SLOT(reactionDoubleSelection()));
    connect(sceneVueHaut, SIGNAL(desMursSontSelectionnes()),this,SLOT(reactionSelectionMultiple()));

    // Connexions liées à  la sauvegarde et au chargement

    connect(sceneVueHaut, SIGNAL(sceneModifiee()), this, SLOT(documentEstModifie()));

    // connexions liées à la connexion du zoom et de la roulette souris

    connect(sceneVueHaut, SIGNAL(rouletteAvant()), this, SLOT(zoomer()));
    connect(sceneVueHaut, SIGNAL(rouletteArriere()), this, SLOT(dezoomer()));

    connect(sceneVueHaut, SIGNAL(sceneChangee()), this, SLOT(addToList()));

    // Connexions liées à la translation

    connect(sceneVueHaut, SIGNAL(translationDemandee(qreal,qreal)), this, SLOT(deplacementDe(qreal,qreal)));
    connect(dialParam, SIGNAL(hauteurChangee(qreal)), this , SLOT(changerHauteur(qreal)));

    // Connexion liées au verouillage

    connect(sceneVueHaut, SIGNAL(salleDeverouillee()), this, SLOT(reactionDeverrouillage()));
    connect(sceneVueHaut, SIGNAL(salleVerouillee()), this, SLOT(reactionVerrouillage()));

    // Connexion liées à la sélection d'une surélévation
    //    * CRASH (13/02)
    // Edit : Résolu

    connect(sceneVueHaut, SIGNAL(uneSurelevationEstSelectionnee()), this, SLOT(reactionSelectionSurelevation()));
    connect(spinSurelevation, SIGNAL(valueChanged(double)), sceneVueHaut, SLOT(modifierHauteurSurelevSelect(double)));

    // Connexion lié au changement de sol (la moquette, tout ça tout ça...)

    connect(dialParam, SIGNAL(sigListeChangee(Sol)), this, SLOT(setSolProjet(Sol)));
    connect(dialParam,SIGNAL(sigActualiserMiniatures()),this,SLOT(actualiserLesMiniatures()));

    connect(dialParam, SIGNAL(sigCheckAffImgChange(bool)), sceneVueHaut, SLOT(setIndicateur(bool)));

    // Connexions liées aux évenements d'objets 3D

    connect(sceneVueHaut, SIGNAL(unObjetEstSelectionne()), this, SLOT(reactionSelectionObjet()));
    connect(spinAngleObjet, SIGNAL(valueChanged(int)), this, SLOT(changerValeurSpinBoxObjet(int)));
    connect(sceneVueHaut, SIGNAL(angleObjetSelectModifie(int)), spinAngleObjet, SLOT(setValue(int)));
    connect(comboChoixType, SIGNAL(currentIndexChanged(int)),sceneVueHaut, SLOT(changerTypeObjetSelect(int)));

    connect(dialParam, SIGNAL(cheminTextureImageChangee(QString)), this, SLOT(setUrlTextureProjet(QString)));
    connect(dialParam, SIGNAL(tailleTextureImageChangee(double)), this, SLOT(setTailleTextureProjet(double)));

}




void Fenetre::initialiserZoneGrille(){
    widgetGrille = new QWidget;
    groupeGrille = new QGroupBox(tr("Grille"));
    layoutGrille = new QGridLayout;
    spinGrille = new QDoubleSpinBox;
    spinGrille->setValue(1.00);
    spinGrille->setMinimum(0.10);
    spinGrille->setSingleStep(0.1);
    labelSpinGrille = new QLabel(tr("Pas de la grille : "));
    layoutGrille->addWidget(labelSpinGrille);
    layoutGrille->addWidget(spinGrille);
    checkMagnetisme = new QCheckBox(tr("Magnetisme"));
    layoutGrille->addWidget(checkMagnetisme);
    groupeGrille->setLayout(layoutGrille);
    layoutWidgetGrille = new QHBoxLayout;
    layoutWidgetGrille->addWidget(groupeGrille);
    widgetGrille->setLayout(layoutWidgetGrille);
    //    laterale->addWidget(widgetGrille);
    //    superieure->addWidget(widgetGrille);
}

void Fenetre::initialiserActions() {
    nouvAct = new QAction(QIcon(":/res/new.png"), tr("&Nouvelle salle"), this);
    nouvAct->setShortcuts(QKeySequence::New);
    nouvAct->setStatusTip(tr("Crée une nouvelle exposition vierge"));
    //    connect(nouvAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/res/open.png"), tr("&Ouvrir..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Ouvrir une exposition existante"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/res/save.png"), tr("&Enregistrer"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Sauvegarde l'exposition courante"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(QIcon(":/res/saveas.png"),tr("Enregistrer &Sous..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Sauvegarde l'exposition sous un nouveau nom"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    fermerAct = new QAction(tr("&Fermer"), this);
    fermerAct->setShortcut(tr("Ctrl+W"));
    fermerAct->setStatusTip(tr("Ferme cette fenÃªtre"));
    connect(fermerAct, SIGNAL(triggered()), this, SLOT(close()));

    exitAct = new QAction(tr("&Quitter"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Quitte l'application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    couperAct = new QAction(QIcon::fromTheme("edit-cut", QIcon(":/res/cut.png")), tr("Couper"), this);
    couperAct->setShortcuts(QKeySequence::Cut);
    couperAct->setStatusTip(tr("Coupe la sélection courante dans le presse papiers"));
    connect(couperAct, SIGNAL(triggered()), sceneVueHaut, SLOT(couperContenu()));

    copierAct = new QAction(QIcon::fromTheme("edit-copy", QIcon(":/res/copy.png")), tr("&Copier"), this);
    copierAct->setShortcuts(QKeySequence::Copy);
    copierAct->setStatusTip(tr("Copie la sélection courante dans le presse papiers"));
    connect(copierAct, SIGNAL(triggered()), sceneVueHaut, SLOT(copierContenu()));

    collerAct = new QAction(QIcon::fromTheme("edit-paste", QIcon(":/res/paste.png")), tr("&Coller"), this);
    collerAct->setShortcuts(QKeySequence::Paste);
    collerAct->setStatusTip(tr("Colle le contenu du presse papier"));
    connect(collerAct, SIGNAL(triggered()), sceneVueHaut, SLOT(collerContenu()));

    aboutAct = new QAction(tr("&A propos"), this);
    aboutAct->setStatusTip(tr("A propos de Virtual Art Expo"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("A propos de &Qt"), this);
    aboutQtAct->setStatusTip(tr("A propos de la librairie Qt"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    dessinerMurAct = new QAction(QIcon(":/res/dessinerMur.png"), tr("Dessiner"), this);
    dessinerMurAct->setStatusTip(tr("Dessiner des murs"));
    connect(dessinerMurAct, SIGNAL(triggered()), this, SLOT(ajouterMur()));

    afficherGrilleAct = new QAction(QIcon(":/res/iconeGrille.png"), tr("Grille"), this);
    afficherGrilleAct->setStatusTip(tr("Afficher la grille"));
    connect(afficherGrilleAct, SIGNAL(triggered()), this, SLOT(about()));

    selectionnerAct = new QAction(QIcon(":/res/selectionner.png"), tr("Selectionner"), this);
    selectionnerAct->setStatusTip(tr("Sélectionner un ou plusieurs éléments"));
    connect(selectionnerAct, SIGNAL(triggered()), this, SLOT(selectionner()));

    supprimerAct = new QAction(QIcon(":/res/supprimer.png"), tr("Supprimer"), this);
    supprimerAct->setStatusTip(tr("Supprimer un ou plusieurs éléments"));
    connect(supprimerAct, SIGNAL(triggered()), sceneVueHaut, SLOT(supprimerMurSelect()));

    undoAct = new QAction(QIcon(":/res/undo.png"), tr("Annuler"), this);
    undoAct->setStatusTip(tr("Annuler"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(annuler()));

    redoAct = new QAction(QIcon(":/res/redo.png"), tr("Rétablir"), this);
    redoAct->setStatusTip(tr("Rétablir"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(retablir()));

    fullScreenAct = new QAction(QIcon(":/res/fullscreen.png"), tr("Plein écran"), this);
    fullScreenAct->setStatusTip(tr("Passer en plein écran"));
    connect(fullScreenAct, SIGNAL(triggered()), this, SLOT(pleinEcran()));

    dessinerSurelevationAct = new QAction(QIcon(":/res/surelevation.png"), tr("Dessiner une surélévation"), this);
    dessinerSurelevationAct->setStatusTip(tr("Dessiner une surélévation"));
    connect(dessinerSurelevationAct, SIGNAL(triggered()), this, SLOT(ajouterSurelevation()));

    dessinerCourbeAct = new QAction(QIcon(":/res/courbe.png"), tr("Courbe"), this);
    dessinerCourbeAct->setStatusTip(tr("Dessiner une courbe"));
    connect(dessinerCourbeAct, SIGNAL(triggered()), this, SLOT(ajouterCourbe()));

    paramSalleAct = new QAction(QIcon(":/res/param.png"), tr("Parametres"), this);
    paramSalleAct->setStatusTip(tr("Paramètres de la salle"));
    connect(paramSalleAct, SIGNAL(triggered()), this, SLOT(paramSalle()));

    verouillerAct = new QAction(QIcon(":/res/cadenas.png"), tr("Verouiller"), this);
    verouillerAct->setStatusTip(tr("Verouiller la salle"));
    connect(verouillerAct, SIGNAL(triggered()), this, SLOT(verouiller()));

    passerEnVue3DAct = new QAction(QIcon(":/res/vue3D.png"), tr("Passer en vue 3D"), this);
    passerEnVue3DAct->setStatusTip(tr("Passer en vue 3D"));
    connect(passerEnVue3DAct, SIGNAL(triggered()), this, SLOT(passerEnVue3D()));

    ajouterObjet3DAct = new QAction(QIcon(":/res/chaise.png"), tr("Ajouter un objet 3D"), this);
    ajouterObjet3DAct->setStatusTip(tr("Ajouter un objet 3D"));
    connect(ajouterObjet3DAct, SIGNAL(triggered()), this, SLOT(ajouterObjet3D()));

    placerPointDepartAct = new QAction(QIcon(":/res/pointDepart.png"), tr("Placer le point de depart"), this);
    placerPointDepartAct->setStatusTip(tr("Placer le point de depart"));
    connect(placerPointDepartAct, SIGNAL(triggered()), this, SLOT(placerPtDepart()));



}

void Fenetre::placerPtDepart(){
    sceneVueHaut->setMode(VueHaut::PlacementDepart);
}

void Fenetre::initialiserBarreLaterale() {
    barreLaterale = new QToolBar(tr("Outils"));
    addToolBar(Qt::LeftToolBarArea,barreLaterale);
    dessinerMurAct->setCheckable(true);
    barreLaterale->addAction(selectionnerAct);
    selectionnerAct->setCheckable(true);
    selectionnerAct->setChecked(true);
    barreLaterale->addAction(dessinerMurAct);
    barreLaterale->addAction(dessinerCourbeAct);
    dessinerCourbeAct->setCheckable(true);
    barreLaterale->addAction(dessinerSurelevationAct);
    ajouterObjet3DAct->setCheckable(true);
    barreLaterale->addAction(ajouterObjet3DAct);
    dessinerSurelevationAct->setCheckable(true);

    //    barreLaterale->setAllowedAreas(Qt::LeftToolBarArea);

}

void Fenetre::initialiserBarreSuperieure() {
    barreSuperieure = new QToolBar(tr("Menu"));
    addToolBar(Qt::TopToolBarArea,barreSuperieure);
    //    barreSuperieure->setIconSize(QSize(10,10));

    barreSuperieure->addAction(nouvAct);
    barreSuperieure->addAction(saveAct);
    barreSuperieure->addAction(saveAsAct);
    barreSuperieure->addAction(couperAct);
    barreSuperieure->addAction(copierAct);
    barreSuperieure->addAction(collerAct);
    barreSuperieure->addSeparator();
    barreSuperieure->addAction(undoAct);
    barreSuperieure->addAction(redoAct);
    barreSuperieure->addSeparator();
    barreSuperieure->addAction(fullScreenAct);
//    barreSuperieure->addAction(passerEnVueFaceAct);
    barreSuperieure->addAction(paramSalleAct);
    barreSuperieure->addAction(verouillerAct);
    barreSuperieure->addAction(passerEnVue3DAct);
    barreSuperieure->addAction(placerPointDepartAct);
    passerEnVue3DAct->setEnabled(false);
}

void Fenetre::initialiserBarreVueFace() {
    barreVueFace = new QToolBar(tr("Outils"));
    barreVueFace->addAction(nouvAct);
    barreVueFace->addAction(saveAct);
    barreVueFace->addAction(saveAsAct);
    barreVueFace->addSeparator();
    barreVueFace->addAction(fullScreenAct);
    barreVueFace->addAction(passerEnVueHautAct);
}

void Fenetre::initialiserMenus(){
    menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(nouvAct);
    menuFichier->addAction(openAct);
    menuFichier->addAction(saveAct);
    menuFichier->addAction(saveAsAct);
    menuFichier->addSeparator();
    menuFichier->addAction(fermerAct);
    menuFichier->addAction(exitAct);

    menuEdition = menuBar()->addMenu(tr("&Edition"));
    menuEdition->addAction(couperAct);
    menuEdition->addAction(copierAct);
    menuEdition->addAction(collerAct);

    menuBar()->addSeparator();

    menuAide = menuBar()->addMenu(tr("&Aide"));
    menuAide->addAction(aboutAct);
    menuAide->addAction(aboutQtAct);
}

void Fenetre::initialiserStatusBar(){
    statusBar()->showMessage(tr("Prêt"));

}

void Fenetre::reactionSelection(){
    if(sceneVueHaut->contientMurs()){
        if(sceneVueHaut->isVerouille()){
            this->cacherZoneMurSelect();
            this->cacherZoneDeuxMursSelect();
            this->cacherZoneSurelevation();
            this->cacherZoneObjetSelect();
            this->afficherZoneMurSelectVerouille();
        }
        else {
            barreLaterale->addAction(supprimerAct);
            this->afficherZoneMurSelect();
            this->cacherZoneDeuxMursSelect();
            this->cacherZoneObjetSelect();
            this->cacherZoneMurSelectVerouille();
            this->cacherZoneSurelevation();
        }
    }
}

void Fenetre::reactionSelectionObjet(){
        if(!sceneVueHaut->isVerouille()){
            this->cacherZoneMurSelect();
            this->cacherZoneDeuxMursSelect();
            this->cacherZoneSurelevation();
            this->afficherZoneObjetSelect();
        }

}

void Fenetre::reactionDoubleSelection(){
    if(sceneVueHaut->contientMurs()){
        if(!sceneVueHaut->isVerouille()){
            this->afficherZoneDeuxMursSelect();
            this->cacherZoneMurSelect();
            this->cacherZoneObjetSelect();
            barreLaterale->addAction(supprimerAct);
            this->afficherDoubleSpin();
            this->cacherZoneMurSelectVerouille();
            this->cacherZoneSurelevation();
        }
    }
}

void Fenetre::reactionSelectionMultiple(){
    if(sceneVueHaut->contientMurs()){
        if(!sceneVueHaut->isVerouille()){
            this->afficherZoneDeuxMursSelect();
            this->cacherZoneMurSelect();
            this->cacherZoneObjetSelect();
            barreLaterale->addAction(supprimerAct);
            this->cacherDoubleSpin();
            this->cacherZoneMurSelectVerouille();
            this->cacherZoneSurelevation();
        }
    }
}

void Fenetre::reactionAucuneSelection(){
    barreLaterale->removeAction(supprimerAct);
    this->cacherZoneMurSelect();
    this->cacherZoneDeuxMursSelect();
    this->cacherZoneObjetSelect();
    this->cacherZoneMurSelectVerouille();
    this->cacherZoneSurelevation();
}

void Fenetre::reactionSelectionSurelevation() {
    this->reactionAucuneSelection();
    this->afficherZoneSurelevation();
}

void Fenetre::cacherDoubleSpin(){
    this->spinAngleDeuxMurs->hide();
    this->labelSpinAngleDeuxMurs->hide();
}

void Fenetre::afficherDoubleSpin(){
    this->spinAngleDeuxMurs->show();
    this->labelSpinAngleDeuxMurs->show();
}

void Fenetre::changerValeurSpinBox(int valeur){
    if(valeur == -1)
        valeur = 359;
    else if(valeur == 361)
        valeur = 1;
    sceneVueHaut->setAngleMurSelect(valeur);
    this->spinAngle->setValue(valeur);
}

void Fenetre::changerValeurSpinBoxObjet(int valeur){
    if(valeur == -1)
        valeur = 359;
    else if(valeur == 361)
        valeur = 1;
    sceneVueHaut->setAngleObjetSelect(valeur);
    this->spinAngleObjet->setValue(valeur);
}

void Fenetre::changerValeurDoubleSpinBox(int valeur){
    if(valeur == -1)
        valeur = 359;
    else if(valeur == 361)
        valeur = 1;
    sceneVueHaut->setAngleEntreDeuxMurs(valeur);
    this->spinAngleDeuxMurs->setValue(valeur);
}


bool Fenetre::devraitEtreSauvegarde(){
    if (modifie) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Attention"),
                                   tr("La salle a été modifiée.\n"
                                      "Voulez vous enregistrer les modifications ?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool Fenetre::enregistrerSalle(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Impossible d'enregistrer la salle ' %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QApplication::setOverrideCursor(Qt::WaitCursor);
    Sauvegarde sa(sceneVueHaut);
    sa.Sauvegarder(fileName);
    QApplication::restoreOverrideCursor();
    this->setWindowTitle("Virtual Art Expo - " + nomFichier);
    statusBar()->showMessage(tr("Salle enregistrée"), 2000);
    return true;
}

void Fenetre::chargerSalle(const QString &fileName)
{

    QFile file(fileName);
    //qDebug() << "On crée le fichier...";
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Impossible de charger la salle %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }


    //qDebug() << "On met le curseur...";
    QApplication::setOverrideCursor(Qt::WaitCursor);

    //qDebug() << "On vide la salle...";
    sceneVueHaut->items().clear();

    //qDebug() << "On crée la sauvegarde...";
    Sauvegarde sav(sceneVueHaut);

    //qDebug() << "On lui demande de charger...";
    if(sav.Charger(fileName)){
        statusBar()->showMessage(tr("Salle chargée avec succès"), 2000);
        nomFichier = fileName;
    }
    else {
        statusBar()->showMessage(tr("Echec lors du chargement de la salle"), 2000);
        QApplication::quit();
    }
    QApplication::restoreOverrideCursor();

}

void Fenetre::closeEvent(QCloseEvent *event)
{
    if (this->devraitEtreSauvegarde()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Fenetre::nouvelleSalle()
{
    Fenetre *other = new Fenetre;
    other->move(x() + 40, y() + 40);
    other->show();
}

void Fenetre::open()
{
    if (sansTitre && !modifie) {
        QString nm = QFileDialog::getOpenFileName(this,tr("Open"),QDir::currentPath(),tr("ENSP file (*.ensp)"));
        if (!nm.isEmpty()) {

            //qDebug() << "on charge...";
            chargerSalle(nm);
        }
    }
    else if(devraitEtreSauvegarde()){
        QString nm = QFileDialog::getOpenFileName(this,tr("Open"),QDir::currentPath(),tr("ENSP file (*.ensp)"));
        if (!nm.isEmpty()) {
            sceneVueHaut->viderObjets();
            chargerSalle(nm);

        }
    }

}


bool Fenetre::save()
{
    if (sansTitre) {
        return saveAs();
    } else {
        return enregistrerSalle(nomFichier);
    }
}

bool Fenetre::saveAs()
{
    nomFichier = QFileDialog::getSaveFileName(this, tr("Save As"),
                                              nomFichier,tr("ENSP files (*.ensp)"));
    if (nomFichier.isEmpty())
        return false;

    sansTitre = false;
    this->setWindowTitle("Virtual Art Expo - " + nomFichier);
    return enregistrerSalle(nomFichier);
}

void Fenetre::about()
{
    QMessageBox::about(this, tr("A propos de Virtual Art Expo"),
                       tr("A completer"));
}

void Fenetre::documentEstModifie()
{
    modifie = true;
    setWindowTitle("Virtual Art Expo - " + nomFichier + " *");
}

void Fenetre::zoomer()
{
    vue->scale(1.2,1.2);
    echelle->majEchelle(echelle->getEchelle()*1.2);
    //qDebug() << "zoom avant";
}

void Fenetre::dezoomer()
{
    vue->scale(0.8,0.8);
    echelle->majEchelle(echelle->getEchelle()*0.8);
    //qDebug() << "zoom arrière";
}

void Fenetre::deplacementDe(qreal dx, qreal dy) {

    //qDebug() << "Scéne déplacée de [" << dx << "," << dy << "]";
}

bool Fenetre::suivant() {
    if(iterateur+1 <= listeActions.size()-1){
        iterateur++;
        return true;
    }
    return false;
}

bool Fenetre::precedant() {
    if(iterateur-1 >= 0){
        iterateur--;
        return true;
    }
    return false;
}

void Fenetre::supprimerSuivants() {
    while(iterateur<listeActions.size()-1){
        qDebug() << "####################### Suppr Suivant !";
        listeActions.pop_back();
    }
}

void Fenetre::annuler() {
    if(precedant()){
        sceneVueHaut=listeActions.at(iterateur);
        this->vue->setScene(listeActions.at(iterateur));
        initialiserConnexions();
        qDebug() << "####################### Annuler !";
        qDebug() << "iterateur = " << iterateur;
        qDebug() << "VueHaut a l'iterateur = "<< listeActions.at(iterateur);
        qDebug() << "VueHaut de la fenetre = "<< this->sceneVueHaut;
        qDebug() << "nombre d'elements = " << listeActions.size()-1;
    }



}

void Fenetre::retablir() {
    if(suivant()){
        sceneVueHaut=listeActions.at(iterateur);
        this->vue->setScene(listeActions.at(iterateur));
        initialiserConnexions();

        qDebug() << "####################### Retablir !";
        qDebug() << "iterateur = " << iterateur;
        qDebug() << "VueHaut a l'iterateur = "<< listeActions.at(iterateur);
        qDebug() << "VueHaut de la fenetre = "<< this->sceneVueHaut;
        qDebug() << "nombre d'elements = " << listeActions.size()-1;
    }

}

void Fenetre::addToList() {
    if(iterateur==0)
    {
        while(!listeActions.isEmpty())
            listeActions.pop_back();
        listeActions.append(new VueHaut(this,this));
        iterateur++;
    }
    supprimerSuivants();
    VueHaut *nouvelElement;
    nouvelElement = new VueHaut(*sceneVueHaut);
    nouvelElement->setMode(sceneVueHaut->getMode());
    listeActions.append(nouvelElement);
    suivant();
    sceneVueHaut=listeActions.at(iterateur);
    this->vue->setScene(listeActions.at(iterateur));
    initialiserConnexions();

    qDebug() << "####################### Element ajouté !";
    qDebug() << "iterateur = " << iterateur;
    qDebug() << "VueHaut a l'iterateur = "<< listeActions.at(iterateur);
    qDebug() << "VueHaut de la fenetre = "<< this->sceneVueHaut;
    qDebug() << "nombre d'elements = " << listeActions.size()-1;



}

// Initialiser la vue de face

void Fenetre::initialiserVueDeFace() {

    passerEnVueFaceAct = new QAction(QIcon(":/res/passerVueFace.png"), tr("Vue de face"), this);
    passerEnVueFaceAct->setStatusTip(tr("Passer en vue de face"));
    connect(passerEnVueFaceAct, SIGNAL(triggered()), this, SLOT(passerEnVueDeFace()));

    passerEnVueHautAct = new QAction(QIcon(":/res/passerVueHaut.png"), tr("Vue de haut"), this);
    passerEnVueHautAct->setStatusTip(tr("Passer en vue de haut"));
    connect(passerEnVueHautAct, SIGNAL(triggered()), this, SLOT(passerEnVueDeHaut()));


    // Explorateur de fichiers

    widgetExplorateur = new QWidget;
    layoutExplorateur = new QVBoxLayout;
    widgetExplorateur->setMaximumWidth(400);
    widgetExplorateur->setMouseTracking(true);
    widgetExplorateur->setLayout(layoutExplorateur);
    laterale->addWidget(widgetExplorateur);
    boutonImportation = new QPushButton(tr("Importer..."));

    vueExplorateur = new ListeImages;
    modeleExplorateur = new QFileSystemModel;

    modeleExplorateur->setRootPath(projetCourant->getRepertoireImages());
    vueExplorateur->setModel(modeleExplorateur);
    vueExplorateur->setRootIndex(modeleExplorateur->index(projetCourant->getRepertoireImages()));
    vueExplorateur->setDragEnabled(true);
    vueExplorateur->setViewMode(QListView::IconMode);
    vueExplorateur->setIconSize(QSize(64, 64));
    vueExplorateur->setGridSize(QSize(80, 80));
    vueExplorateur->setSpacing(16);
    vueExplorateur->setMaximumWidth(400);
    vueExplorateur->setMinimumWidth(380);
    vueExplorateur->setMovement(QListView::Snap);
    vueExplorateur->setAcceptDrops(true);
    vueExplorateur->setDropIndicatorShown(true);
    maMachina = new DaIconMachina;
    modeleExplorateur->setIconProvider(maMachina);

    layoutExplorateur->addWidget(boutonImportation);
    layoutExplorateur->addWidget(vueExplorateur);

    connect(boutonImportation, SIGNAL(clicked()), this, SLOT(chargerImages()));

    cacherExplorateur();

}

void Fenetre::afficherExplorateur() {
    widgetExplorateur->show();
}

void Fenetre::cacherExplorateur() {
    widgetExplorateur->hide();
}

void Fenetre::passerEnVueDeFace() {
    if(sceneVueHaut->murSelectionne() == NULL){
        QMessageBox box;
        box.setText("Vous devez sélectionner un mur à éditer");
        box.exec();
    }
    else {
        this->vue->setScene(sceneVueHaut->murSelectionne()->getVueFace());
        //        this->vueDeFace->setMurCourant(sceneVueHaut->murSelectionne());
        afficherExplorateur();
        removeToolBar(barreSuperieure);
        addToolBar(Qt::TopToolBarArea,barreVueFace);
        barreVueFace->show();
        barreVueFace->raise();
        removeToolBar(barreLaterale);
        this->cacherZoneMurSelect();
        this->cacherZoneMurSelectVerouille();
        afficherWidgetTableauSelect();
    }
}

void Fenetre::passerEnVueDeHaut() {
    this->vue->setScene(sceneVueHaut);
    removeToolBar(barreVueFace);
    barreSuperieure->show();
    cacherExplorateur();
    addToolBar(Qt::TopToolBarArea,barreSuperieure);
    addToolBar(Qt::LeftToolBarArea, barreLaterale);
    reactionAucuneSelection();
    cacherWidgetTableauSelect();
    foreach (Mur *mur, sceneVueHaut->listeDesMursDans(sceneVueHaut->objets)) {
        mur->getDeuxiemeVueFace()->tuerLaVariable();
        mur->getPremiereVueFace()->tuerLaVariable();
    }
}

void Fenetre::passerEnVue3D() {
    this->save();
    QProcess *myProcess = new QProcess;
    QStringList arguments;
    arguments << this->projetCourant->getCheminSave();
    myProcess->startDetached(QString("../Moteur/Moteur"),arguments,"./");
}

void Fenetre::paramSalle() {
    dialParam->exec();
}

double Fenetre::getHauteur(){
    return hauteur;
}

void Fenetre::changerHauteur(qreal h) {
    emit hauteurChangee(h);
}

void Fenetre::verouiller(){
    if(sceneVueHaut->listeDesMurs().count() > 0){
    barreLaterale->hide();
    reactionAucuneSelection();
    sceneVueHaut->verouillerSalle();
    disconnect(verouillerAct, SIGNAL(triggered()),0,0);
    connect(verouillerAct, SIGNAL(triggered()), this, SLOT(deverouiller()));
    verouillerAct->setIcon(QIcon(":res/deverouiller.png"));
    statusBar()->showMessage("La salle est désormais verouillée, les murs ne pourront plus etres modifiés",4000);
    }
    else {
        QMessageBox box;
        box.setText(tr("Votre salle doit comporter au moins un mur pour etre verouillée"));
        box.exec();
        statusBar()->showMessage("La salle doit compter au moins un mur pour etre verouillée",4000);
    }
}

void Fenetre::deverouiller() {
    sceneVueHaut->deverouillerSalle();
    if(!sceneVueHaut->isVerouille()){
        barreLaterale->show();
        reactionAucuneSelection();
        disconnect(verouillerAct, SIGNAL(triggered()),0,0);
        connect(verouillerAct, SIGNAL(triggered()), this, SLOT(verouiller()));
        verouillerAct->setIcon(QIcon(":res/cadenas.png"));
        statusBar()->showMessage("La salle n'est désormais plus verouillée et de nouveau éditable",4000);
    }
}

void Fenetre::pleinEcran() {
    this->showFullScreen();
    disconnect(fullScreenAct, SIGNAL(triggered()),0,0);
    connect(fullScreenAct, SIGNAL(triggered()), this, SLOT(fenetre()));
    fullScreenAct->setIcon(QIcon(":res/normalscreen.png"));
}

void Fenetre::fenetre() {
    this->showMaximized();
    disconnect(fullScreenAct, SIGNAL(triggered()),0,0);
    connect(fullScreenAct, SIGNAL(triggered()), this, SLOT(pleinEcran()));
    fullScreenAct->setIcon(QIcon(":res/fullscreen.png"));
}

void Fenetre::chargerImages(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    if(!repertoirePrepare())
        preparerRepertoire();
    foreach (QString url, fileNames) {
        QFile file(url);
        //qDebug() << "en cours : " << url << " --> " << projetCourant->getRepertoireImages()+QFileInfo(url).fileName();
        bool valid = file.copy(projetCourant->getRepertoireImages()+"/"+QFileInfo(url).fileName());

    }


}

void Fenetre::preparerRepertoire() {
    //    repertoireUtilisateur = new QDir;
    //    QDir home = QDir::homePath();
    //    //qDebug() << home;
    //    home.mkdir("Virtual Art Expo");
    //    home.cd("Virtual Art Expo");
    //    repertoireUtilisateur->setPath(home.absolutePath());
    //    //qDebug() << "Chemin absolu : " << repertoireUtilisateur->absolutePath();


}

bool Fenetre::repertoirePrepare() {
    if(projetCourant != NULL){
        if(projetCourant->isValide())
            return true;
        else
            return false;
    }
    else
        return false;
}

void Fenetre::nouveauProjet(Projet *proj){
    if(proj == NULL)
        throw "pointeur projet NULL ! ";

    projetCourant = proj;
    //qDebug() << "salle valide : " << proj->isValide();
    if(proj->isValide()){
        proj->sauvegarderSalle(sceneVueHaut);
        this->nomFichier = QString(proj->getCheminSave());
        //        repertoireUtilisateur = proj->getRepertoire().path();
    }
    else
        qDebug() << "Salle non valide dans Fenetre::nouveauProjet()";

}

void Fenetre::nouveauProjet(){

    projetCourant = new Projet();
    //qDebug() << "salle valide : " << projetCourant->isValide();
    if(projetCourant->isValide()){
        projetCourant->sauvegarderSalle(sceneVueHaut);
        this->nomFichier = QString(projetCourant->getCheminSave());
        //        repertoireUtilisateur = proj->getRepertoire().path();
    }
    else
        qDebug() << "Salle non valide dans Fenetre::nouveauProjet()";

}

void Fenetre::nouveauProjet(QString fichier){
    QFile file(fichier);
    if(file.exists()){
        this->chargerSalle(fichier);
    }
    if(projetCourant->isValide()){
        projetCourant->sauvegarderSalle(sceneVueHaut);
        this->nomFichier = QString(projetCourant->getCheminSave());
    }
    else
        qDebug() << "Salle non valide dans Fenetre::nouveauProjet()";

}

void Fenetre::setProjet(Projet *pro){
    projetCourant = pro;
}

void Fenetre::reactionVerrouillage() {
    if(sceneVueHaut->isVerouille()){
        this->passerEnVueFaceAct->setEnabled(true);
        this->reactionAucuneSelection();
        this->passerEnVue3DAct->setEnabled(true);
        barreLaterale->setDisabled(true);
    }
}

void Fenetre::reactionDeverrouillage() {
    if(!sceneVueHaut->isVerouille()){
        this->passerEnVueFaceAct->setDisabled(true);
        this->passerEnVue3DAct->setEnabled(false);
        this->reactionAucuneSelection();
        barreLaterale->setEnabled(true);
    }
}

Projet* Fenetre::getProjetCourant(){
    return projetCourant;
}


void Fenetre::ajouterObjet3D() {
    if(sceneVueHaut->getMode() != VueHaut::AjoutObjet){
        dessinerSurelevationAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        selectionnerAct->setChecked(false);
        ajouterObjet3DAct->setChecked(true);
        dessinerMurAct->setChecked(false);
        sceneVueHaut->setMode(VueHaut::AjoutObjet);
    }
    else {
        dessinerSurelevationAct->setChecked(false);
        dessinerCourbeAct->setChecked(false);
        dessinerMurAct->setChecked(false);
        selectionnerAct->setChecked(true);
        ajouterObjet3DAct->setChecked(false);
        sceneVueHaut->setMode(VueHaut::Select);
    }
}

VueHaut* Fenetre::getVueHaut(){

    qDebug()<<"listeAction   ###################";
    foreach (VueHaut *vue, listeActions) {
        qDebug()<<vue;
    }
    qDebug()<< "###############################";
    return sceneVueHaut;
}

void Fenetre::setSolProjet(Sol sol){
    projetCourant->setSol(sol);
}

void Fenetre::actualiserLesMiniatures(){
    timeCount = 0;
    dialParam->afficherBarre(true);
    connect(&monTimer, SIGNAL(timeout()), this, SLOT(incrementerImages()));
    monTimer.setInterval(1);
    monTimer.start(100);
}

void Fenetre::incrementerImages(){
    timeCount++;
    if(timeCount==100){
        monTimer.stop();
        dialParam->afficherBarre(false);
        vueExplorateur->update(modeleExplorateur->index(projetCourant->getRepertoireImages()));
    }
    else {
        dialParam->setValeurBarre(timeCount);
    }
}

void Fenetre::setUrlTextureProjet(QString texture){
    projetCourant->url_sol = texture;

}

void Fenetre::setTailleTextureProjet(double taille){
    projetCourant->size_sol = taille;
}
