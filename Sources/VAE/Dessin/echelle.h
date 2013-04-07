#ifndef ECHELLE_H
#define ECHELLE_H

#include <QtGui>
#include <QWidget>

class Echelle : public QWidget
{
    Q_OBJECT
public:
    explicit Echelle(QWidget *parent = 0);
    
signals:
    void onRepeint();
    
public slots:
    void majEchelle(qreal coef);
    qreal getEchelle();

protected:
    void paintEvent(QPaintEvent *);

private:
    qreal ech;
    QPen *penRouge;
    QPen *penNoir;
    QPen *penPolice;
    QFont *fontPolice;

    
};

#endif // ECHELLE_H
