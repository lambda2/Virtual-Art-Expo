#ifndef TABLEAU_H
#define TABLEAU_H

#include <QGraphicsPixmapItem>

class Tableau : public QGraphicsPixmapItem
{
public:

    Tableau(const Tableau &other);
    Tableau(const QString fichier);
    QString getFichier();
    explicit Tableau();
private:
    QString fichier;
    qreal x;
    qreal y;


signals:
    
public slots:
    
};

#endif // TABLEAU_H
