/********************************************************************************
** Form generated from reading UI file 'accueil.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCUEIL_H
#define UI_ACCUEIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Accueil
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *logo;
    QLabel *TexteAccueil;
    QFrame *line;
    QGridLayout *gridLayout;
    QPushButton *boutonCharger;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *boutonNouveau;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Accueil)
    {
        if (Accueil->objectName().isEmpty())
            Accueil->setObjectName(QStringLiteral("Accueil"));
        Accueil->setWindowModality(Qt::ApplicationModal);
        Accueil->resize(400, 303);
        Accueil->setMaximumSize(QSize(400, 16777215));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        Accueil->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/VAElogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Accueil->setWindowIcon(icon);
        Accueil->setAutoFillBackground(false);
        Accueil->setStyleSheet(QLatin1String("background-color: #BFBFBF;\n"
"color: rgb(56, 56, 56);"));
        verticalLayout = new QVBoxLayout(Accueil);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        logo = new QLabel(Accueil);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setMinimumSize(QSize(350, 75));
        logo->setMaximumSize(QSize(400, 200));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/res/logo.png")));
        logo->setScaledContents(false);

        verticalLayout->addWidget(logo);

        TexteAccueil = new QLabel(Accueil);
        TexteAccueil->setObjectName(QStringLiteral("TexteAccueil"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TexteAccueil->sizePolicy().hasHeightForWidth());
        TexteAccueil->setSizePolicy(sizePolicy);
        TexteAccueil->setMaximumSize(QSize(350, 16777215));
        TexteAccueil->setTextFormat(Qt::RichText);
        TexteAccueil->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(TexteAccueil);

        line = new QFrame(Accueil);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        boutonCharger = new QPushButton(Accueil);
        boutonCharger->setObjectName(QStringLiteral("boutonCharger"));
        boutonCharger->setMinimumSize(QSize(0, 50));
        boutonCharger->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(67, 67, 67);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        boutonCharger->setIcon(icon1);

        gridLayout->addWidget(boutonCharger, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        boutonNouveau = new QPushButton(Accueil);
        boutonNouveau->setObjectName(QStringLiteral("boutonNouveau"));
        boutonNouveau->setMinimumSize(QSize(0, 50));
        boutonNouveau->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(67, 67, 67);"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        boutonNouveau->setIcon(icon2);

        gridLayout->addWidget(boutonNouveau, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Accueil);

        QMetaObject::connectSlotsByName(Accueil);
    } // setupUi

    void retranslateUi(QWidget *Accueil)
    {
        Accueil->setWindowTitle(QApplication::translate("Accueil", "Bienvenue !", 0));
        logo->setText(QString());
        TexteAccueil->setText(QApplication::translate("Accueil", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Pour commencer, cr\303\251ez un nouveau projet, ou ouvrez un projet existant.</span></p></body></html>", 0));
        boutonCharger->setText(QApplication::translate("Accueil", "Charger un projet existant...", 0));
        boutonNouveau->setText(QApplication::translate("Accueil", "Cr\303\251er un nouveau projet...", 0));
    } // retranslateUi

};

namespace Ui {
    class Accueil: public Ui_Accueil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCUEIL_H
