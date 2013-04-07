#ifndef LISTEIMAGES_H
#define LISTEIMAGES_H

#include <QtGui>
#include <QListView>

class ListeImages : public QListView
{
    Q_OBJECT
public:
    explicit ListeImages(QObject *parent = 0);
    void dragMoveEvent(QDragMoveEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *e);
    
signals:
    
public slots:
    
};

#endif // LISTEIMAGES_H
