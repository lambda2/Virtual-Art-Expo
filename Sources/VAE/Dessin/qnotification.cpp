/*
#include "qnotification.h"

QNotification::QNotification(QWidget *parent) :
    QWidget(parent)
{
    this->message = "msg";
    this->delai = 4000;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: url(':/res/fondnotif.png'); color: #FFFFFF; background-position: top left; background-origin: content;");

    labelMessage = new QLabel(message, this);
    labelMessage->setFont(QFont("Helvetica",30));
    labelMessage->setAlignment(Qt::AlignCenter);
    layout = new QHBoxLayout(this);
    layout->addWidget(labelMessage);
    this->setLayout(layout);
    QDesktopWidget w;

    qDebug() << "Geometry : " << w.screenGeometry();
    setGeometry(w.screenGeometry().center().x()-300,
                w.screenGeometry().height()*0.9-200,
                640,
                240);
    this->setMaximumHeight(240);
    this->setMaximumWidth(640);
    monTimer = new QTimer;
    connect(monTimer, SIGNAL(timeout()), this, SLOT(afficher()));
}

QNotification::QNotification(QString msg, int delay, QWidget *parent){
    this->message = msg;
    this->delai = delay;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background: url(':/res/fondnotif.png'); color: #FFFFFF; background-position: top left; background-origin: content;");

    labelMessage = new QLabel(message, this);
    labelMessage->setFont(QFont("Helvetica",30));
    labelMessage->setAlignment(Qt::AlignCenter);
    layout = new QHBoxLayout(this);
    layout->addWidget(labelMessage);
    this->setLayout(layout);
    QDesktopWidget w;

    qDebug() << "Geometry : " << w.screenGeometry();
    setGeometry(w.screenGeometry().center().x()-300,
                w.screenGeometry().height()*0.9-200,
                640,
                240);

    this->setMaximumHeight(240);
    this->setMaximumWidth(640);

}

void QNotification::reduireOpacite() {

    double opacite = this->windowOpacity();
    if(opacite <= 0.0){
        this->close();
    }
    else {
        this->setWindowOpacity(opacite-0.01);
    }
}

void QNotification::afficher() {
    monTimer->stop();
    disconnect(monTimer, SIGNAL(timeout()), this, SLOT(afficher()));
    connect(monTimer, SIGNAL(timeout()), this, SLOT(reduireOpacite()));
    monTimer->start(25);
}

void QNotification::setMessage(QString message) {
    this->message = message;
    labelMessage->setText(this->message);
}

void QNotification::setDelai(qreal delay) {
    this->delai = delay;
}

void QNotification::setFont(QFont font) {
    labelMessage->setFont(font);
}

void QNotification::lancer() {
    this->show();

    connect(monTimer, SIGNAL(timeout()), this, SLOT(afficher()));
    this->setWindowOpacity(1);
    this->setWindowModality(Qt::ApplicationModal);
    monTimer->start(delai);
}
*/
