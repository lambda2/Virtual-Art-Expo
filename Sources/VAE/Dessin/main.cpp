#include <QtGui>
#include "accueil.h"
#include "qnotification.h"



void chargerStyle(){

    QFile file(":/style.qcss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
    QString style;
        QTextStream in(&file);
        while (!in.atEnd()) {
            style += in.readLine();
        }

    qApp->setStyleSheet(style);
    }
}

void simulerChargement() {
        for(int i=0;i<1000000;i++){
            if(i*i*i*i*i/(i+1)!=0)
            {
                // ...
            }
        }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));*/
    QPixmap pixmap(":/res/logo.png");
    QSplashScreen splash(pixmap);
    chargerStyle();

    splash.show();
    simulerChargement();
    Accueil w;
//    Fenetre w;
//    Fenetre3D w;
    w.show();

    splash.finish(&w);
    return a.exec();
}
