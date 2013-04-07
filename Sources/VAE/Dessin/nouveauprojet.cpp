#include "nouveauprojet.h"

NouveauProjet::NouveauProjet(QWidget *parent)
    : QWizard(parent)
{
    ConclusionPage *k = new ConclusionPage;
    setPage(Page_Intro, new IntroPage);
    setPage(Page_Conclusion, k);

    setStartId(Page_Intro);
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/res/VAElogo.png"));
    setMaximumWidth(700);
    setMaximumHeight(500);


    setWindowTitle(tr("Assistant de création de nouveau projet"));

//    connect(this, SIGNAL(accepted()), k, SLOT(presse()));

}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Nouveau projet"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/res/logo_haut.png"));

    label = new QLabel(tr("Bienvenue dans l'assistant de création de projet "
                          "de Virtual Art Expo. "
                          "Laissez vous guider et créez votre projet "
                          "en toute simplicitée. "));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}


int IntroPage::nextId() const
{
        return NouveauProjet::Page_Conclusion;
}


ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{

    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/res/logo_haut.png"));
    setTitle(tr("Configuration du projet"));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/res/VAElogo.png"));

    nomLabel = new QLabel(tr("&Nom du projet:"));
    nomLineEdit = new QLineEdit;
    nomLabel->setBuddy(nomLineEdit);
    nomLineEdit->setText("Projet sans titre");

    repertoireLabel = new QLabel(tr("&Repertoire du projet :"));
    repertoireLineEdit = new QLineEdit;
    repertoireLabel->setBuddy(repertoireLineEdit);
    repertoireLineEdit->setText(QDir::homePath() + "/Virtual Art Expo");

    boutonParcourir = new QPushButton(tr("..."));

    descriptionLabel = new QLabel(tr("&Description:"));
    descriptionLineEdit = new QTextEdit;
    descriptionLabel->setBuddy(descriptionLineEdit);
    descriptionLineEdit->setMaximumHeight(100);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nomLabel, 0, 0);
    layout->addWidget(nomLineEdit, 0, 1,1,2);
    layout->addWidget(repertoireLabel, 1, 0);
    layout->addWidget(repertoireLineEdit, 1, 1,1,1);
    layout->addWidget(boutonParcourir, 1,2,1,1);
    layout->addWidget(descriptionLabel, 2, 0);
    layout->addWidget(descriptionLineEdit, 2, 1,1,2);
    setLayout(layout);

    connect(boutonParcourir, SIGNAL(clicked()), this, SLOT(parcourir()));
}

int ConclusionPage::nextId()
{
    qDebug() << "hello !";
    return -1;
}

void ConclusionPage::initializePage()
{

}

void ConclusionPage::parcourir(){
    repertoireLineEdit->setText(QFileDialog::getExistingDirectory(this, tr("Répertoire du projet"),
                                                                  QDir::homePath()));
}

void ConclusionPage::presse() {
    QMessageBox box;
    box.setWindowTitle(tr("Erreur lors de la création du projet !"));
    if(!repertoireLineEdit->text().isEmpty()){
        if(!nomLineEdit->text().isEmpty()){

            if(QFile(repertoireLineEdit->text()+"/"+nomLineEdit->text()).exists()){
                box.setText(tr("Le projet existe déja"));
                box.exec();
            }
            else {
                Fenetre *fen = new Fenetre;
                fen->show();
//                this->close();
            }


        }
        else {
            box.setText(tr("Vous devez donner un nom Ã  votre projet"));
            box.exec();
        }
    }
    else {
        box.setText(tr("Vous devez sélectionner un répertoire"));
        box.exec();
    }
    qDebug() << "hohoooZAZA KIROUU !";
}

bool ConclusionPage::validatePage(){
    QMessageBox box;
    box.setWindowTitle(tr("Erreur lors de la création du projet !"));
    if(!repertoireLineEdit->text().isEmpty()){
        if(!nomLineEdit->text().isEmpty()){

            if(QFile(repertoireLineEdit->text()+"/"+nomLineEdit->text()).exists()){
                box.setText(tr("Le projet existe déja"));
                box.exec();
            }
            else {
                Projet *projet = new Projet(
                            nomLineEdit->text(),
                            repertoireLineEdit->text(),
                            descriptionLineEdit->toPlainText());
                Fenetre *fen = new Fenetre(projet);
                fen->show();
//                this->close();
                return true;
            }


        }
        else {
            box.setText(tr("Vous devez donner un nom Ã  votre projet"));
            box.exec();
        }
    }
    else {
        box.setText(tr("Vous devez sélectionner un répertoire"));
        box.exec();
    }
    qDebug() << "hohoooZAZA KIROUU !";
    return false;
}
