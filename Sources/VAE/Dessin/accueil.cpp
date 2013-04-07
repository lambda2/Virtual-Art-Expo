#include "accueil.h"
#include "ui_accueil.h"

Accueil::Accueil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Accueil)
{
    ui->setupUi(this);
}

Accueil::~Accueil()
{
    delete ui;
}

void Accueil::on_boutonCharger_clicked() {
    QString nm = QFileDialog::getOpenFileName(this,tr("Open"),QDir::homePath(),tr("ENSP file (*.ensp)"));
    if (!nm.isEmpty()) {
        Fenetre *fen = new Fenetre(nm);
        fen->show();
        this->close();
    }
}

void Accueil::on_boutonNouveau_clicked() {
    NouveauProjet pro;
    this->close();
    pro.exec();
}
