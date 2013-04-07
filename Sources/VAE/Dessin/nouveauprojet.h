#ifndef NouveauProjet_H
#define NouveauProjet_H

#include <QtGui>
#include <projet.h>
#include <fenetre.h>

class NouveauProjet : public QWizard
{
    Q_OBJECT

public:
    enum { Page_Intro, Page_Conclusion };


    NouveauProjet(QWidget *parent = 0);
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *label;
};


class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    void initializePage();
    int nextId();
    bool validatePage();


public slots:
    void parcourir();
    void presse();


private:
    QLabel *repertoireLabel;
    QLabel *nomLabel;
    QLabel *descriptionLabel;
    QLineEdit *repertoireLineEdit;
    QPushButton *boutonParcourir;
    QLineEdit *nomLineEdit;
    QTextEdit *descriptionLineEdit;
};

#endif
