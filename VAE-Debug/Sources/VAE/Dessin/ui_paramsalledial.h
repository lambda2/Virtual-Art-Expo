/********************************************************************************
** Form generated from reading UI file 'paramsalledial.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMSALLEDIAL_H
#define UI_PARAMSALLEDIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamSalleDial
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLabel *labelParamSalle;
    QDoubleSpinBox *doubleSpinParamSalle;
    QWidget *widgetTexture;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelParcourir;
    QPushButton *boutonParcourir;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *spinSize;
    QLabel *label_4;
    QComboBox *listeSol;
    QCheckBox *checkBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *boutonReconfigurer;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *boutonReconstruire;
    QProgressBar *progression;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ParamSalleDial)
    {
        if (ParamSalleDial->objectName().isEmpty())
            ParamSalleDial->setObjectName(QStringLiteral("ParamSalleDial"));
        ParamSalleDial->resize(556, 560);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/param.png"), QSize(), QIcon::Normal, QIcon::Off);
        ParamSalleDial->setWindowIcon(icon);
        ParamSalleDial->setStyleSheet(QStringLiteral("background-color: #737373;"));
        verticalLayout_5 = new QVBoxLayout(ParamSalleDial);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label = new QLabel(ParamSalleDial);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(50, 70));
        label->setMaximumSize(QSize(50, 70));
        label->setStyleSheet(QStringLiteral("background-image :none;"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/engrenage_big.png")));
        label->setScaledContents(true);

        horizontalLayout_7->addWidget(label);

        label_2 = new QLabel(ParamSalleDial);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 70));
        label_2->setMaximumSize(QSize(16777215, 70));
        QFont font;
        font.setPointSize(35);
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("background-image :none;"));

        horizontalLayout_7->addWidget(label_2);


        verticalLayout_5->addLayout(horizontalLayout_7);

        groupBox = new QGroupBox(ParamSalleDial);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral("background-image :none;"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelParamSalle = new QLabel(groupBox);
        labelParamSalle->setObjectName(QStringLiteral("labelParamSalle"));
        labelParamSalle->setStyleSheet(QStringLiteral("background-image :none;"));

        gridLayout->addWidget(labelParamSalle, 0, 0, 1, 1);

        doubleSpinParamSalle = new QDoubleSpinBox(groupBox);
        doubleSpinParamSalle->setObjectName(QStringLiteral("doubleSpinParamSalle"));
        doubleSpinParamSalle->setStyleSheet(QStringLiteral("background-image :none;"));
        doubleSpinParamSalle->setMinimum(1);
        doubleSpinParamSalle->setMaximum(30);
        doubleSpinParamSalle->setSingleStep(0.5);
        doubleSpinParamSalle->setValue(2);

        gridLayout->addWidget(doubleSpinParamSalle, 0, 1, 1, 1);

        widgetTexture = new QWidget(groupBox);
        widgetTexture->setObjectName(QStringLiteral("widgetTexture"));
        verticalLayout_2 = new QVBoxLayout(widgetTexture);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelParcourir = new QLabel(widgetTexture);
        labelParcourir->setObjectName(QStringLiteral("labelParcourir"));

        horizontalLayout->addWidget(labelParcourir);

        boutonParcourir = new QPushButton(widgetTexture);
        boutonParcourir->setObjectName(QStringLiteral("boutonParcourir"));

        horizontalLayout->addWidget(boutonParcourir);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(widgetTexture);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        spinSize = new QDoubleSpinBox(widgetTexture);
        spinSize->setObjectName(QStringLiteral("spinSize"));

        horizontalLayout_6->addWidget(spinSize);


        verticalLayout_2->addLayout(horizontalLayout_6);


        gridLayout->addWidget(widgetTexture, 3, 0, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QStringLiteral("background-image :none;"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        listeSol = new QComboBox(groupBox);
        listeSol->setObjectName(QStringLiteral("listeSol"));
        listeSol->setStyleSheet(QStringLiteral("background-image :none;"));

        gridLayout->addWidget(listeSol, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setEnabled(true);
        checkBox->setChecked(true);
        checkBox->setTristate(false);

        verticalLayout_3->addWidget(checkBox);


        verticalLayout_5->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ParamSalleDial);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QStringLiteral("background-image :none;"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("background-image :none;"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        boutonReconfigurer = new QPushButton(groupBox_2);
        boutonReconfigurer->setObjectName(QStringLiteral("boutonReconfigurer"));
        boutonReconfigurer->setMinimumSize(QSize(140, 0));
        boutonReconfigurer->setStyleSheet(QStringLiteral("background-image :none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        boutonReconfigurer->setIcon(icon1);

        horizontalLayout_3->addWidget(boutonReconfigurer);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(ParamSalleDial);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setStyleSheet(QStringLiteral("background-image :none;"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QStringLiteral("background-image :none;"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        boutonReconstruire = new QPushButton(groupBox_3);
        boutonReconstruire->setObjectName(QStringLiteral("boutonReconstruire"));
        boutonReconstruire->setMinimumSize(QSize(140, 0));
        boutonReconstruire->setStyleSheet(QStringLiteral("background-image :none;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/passerVueFace.png"), QSize(), QIcon::Normal, QIcon::Off);
        boutonReconstruire->setIcon(icon2);

        horizontalLayout_5->addWidget(boutonReconstruire);


        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout_5->addWidget(groupBox_3);

        progression = new QProgressBar(ParamSalleDial);
        progression->setObjectName(QStringLiteral("progression"));
        progression->setEnabled(true);
        progression->setStyleSheet(QStringLiteral("background-image :none;"));
        progression->setValue(0);

        verticalLayout_5->addWidget(progression);

        horizontalSpacer = new QSpacerItem(535, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_5->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(ParamSalleDial);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStyleSheet(QStringLiteral("background-image :none;"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_5->addWidget(buttonBox);


        retranslateUi(ParamSalleDial);
        QObject::connect(buttonBox, SIGNAL(accepted()), ParamSalleDial, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ParamSalleDial, SLOT(reject()));

        QMetaObject::connectSlotsByName(ParamSalleDial);
    } // setupUi

    void retranslateUi(QDialog *ParamSalleDial)
    {
        ParamSalleDial->setWindowTitle(QApplication::translate("ParamSalleDial", "Param\303\250tres", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("ParamSalleDial", "Param\303\250tres", 0));
        groupBox->setTitle(QApplication::translate("ParamSalleDial", "Salle et murs", 0));
        labelParamSalle->setText(QApplication::translate("ParamSalleDial", "Hauteur des murs", 0));
        doubleSpinParamSalle->setSuffix(QApplication::translate("ParamSalleDial", " m", 0));
        labelParcourir->setText(QApplication::translate("ParamSalleDial", "emplacement de l'image...", 0));
        boutonParcourir->setText(QApplication::translate("ParamSalleDial", "Parcourir", 0));
        label_6->setText(QApplication::translate("ParamSalleDial", "Hauteur de l'image r\303\251elle : ", 0));
        spinSize->setSuffix(QApplication::translate("ParamSalleDial", " m", 0));
        label_4->setText(QApplication::translate("ParamSalleDial", "Texture du sol", 0));
        listeSol->clear();
        listeSol->insertItems(0, QStringList()
         << QApplication::translate("ParamSalleDial", "Aucun", 0)
         << QApplication::translate("ParamSalleDial", "Moquette", 0)
         << QApplication::translate("ParamSalleDial", "Parquet", 0)
         << QApplication::translate("ParamSalleDial", "Importer une texture", 0)
        );
        checkBox->setText(QApplication::translate("ParamSalleDial", "Activer l'apercu des tableaux affich\303\251s au survol du mur", 0));
        groupBox_2->setTitle(QApplication::translate("ParamSalleDial", "Moteur 3D", 0));
        label_3->setText(QApplication::translate("ParamSalleDial", "Reconfigurer les param\303\250tres de rendu", 0));
        boutonReconfigurer->setText(QApplication::translate("ParamSalleDial", "Reconfigurer", 0));
        groupBox_3->setTitle(QApplication::translate("ParamSalleDial", "Projet", 0));
        label_5->setText(QApplication::translate("ParamSalleDial", "Reconstruire les miniatures des images", 0));
        boutonReconstruire->setText(QApplication::translate("ParamSalleDial", "Reconstruire", 0));
        progression->setFormat(QApplication::translate("ParamSalleDial", "%p% effectu\303\251", 0));
    } // retranslateUi

};

namespace Ui {
    class ParamSalleDial: public Ui_ParamSalleDial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMSALLEDIAL_H
