#ifndef GRILLE_H
#define GRILLE_H

#include <QtGui>
#include <QGraphicsItem>
#include <QDesktopWidget>

class Grille : public QGraphicsItem
{

    public:
        Grille();
        int getPas();
        bool getMagnetisme();
        int calculerRapport(double m);

    public slots:
        void setPas(double pas);
        void setMagnetisme(bool magn);

    signals:
        void pasModifie(int pas);
        void magnetiseModifie(bool magn);

    protected:
        virtual QRectF boundingRect() const;
        void paint ( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0 );

    private:
        int pas;
        bool magnetisme;
        QPen *penGrille;
};

#endif // GRILLE_H
