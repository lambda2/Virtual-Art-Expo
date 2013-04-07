#include "paramsalledial.h"
#include "ui_paramsalledial.h"

ParamSalleDial::ParamSalleDial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamSalleDial)
{
    ui->setupUi(this);
    ui->progression->hide();
    ui->widgetTexture->hide();

    connect(ui->doubleSpinParamSalle,SIGNAL(valueChanged(double)),this,SLOT(spinboxChangee(double)));
    connect(ui->listeSol,SIGNAL(currentIndexChanged(int)),this,SLOT(listeChangee(int)));
    connect(ui->boutonReconfigurer,SIGNAL(clicked()),this,SLOT(reconfigurer()));
    connect(ui->boutonReconstruire, SIGNAL(clicked()), this, SLOT(actualiserMiniatures()));
    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(checkAffichageTabChange(bool)));
    connect(ui->boutonParcourir, SIGNAL(clicked()), this, SLOT(boutonParcourirPresse()));
    connect(ui->spinSize, SIGNAL(valueChanged(double)), this, SLOT(tailleTextureChangee(double)));

}

ParamSalleDial::~ParamSalleDial()
{
    delete ui;
}

void ParamSalleDial::spinboxChangee(double val) {
    emit hauteurChangee(qreal(val));
}

void ParamSalleDial::listeChangee(int index){
    Sol lo = Sol(index);
    ui->listeSol->setCurrentIndex(index);
    if(index == 3)
        ui->widgetTexture->show();
    else
        ui->widgetTexture->hide();
    emit sigListeChangee(lo);
}

void ParamSalleDial::reconfigurer(){
    QProcess *myProcess = new QProcess;
    QStringList arguments;
    arguments << "reconfigure";
    myProcess->startDetached(QString("../Moteur/Moteur"),arguments,"./");
}

void ParamSalleDial::actualiserMiniatures(){
    emit sigActualiserMiniatures();
}

void ParamSalleDial::afficherBarre(bool aff){
    if(aff){
        ui->progression->show();
    }
    else {
        ui->progression->hide();
    }
}

void ParamSalleDial::setValeurBarre(int valeur){
    ui->progression->setValue(valeur);
}

void ParamSalleDial::checkAffichageTabChange(bool check){
    emit sigCheckAffImgChange(check);
}

void ParamSalleDial::boutonParcourirPresse(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    ui->labelParcourir->setText(fileNames.first());
    emit cheminTextureImageChangee(fileNames.first());
}

void ParamSalleDial::tailleTextureChangee(double taille){
    emit tailleTextureImageChangee(taille);
}
