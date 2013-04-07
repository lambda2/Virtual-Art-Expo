#include "listeimages.h"

ListeImages::ListeImages(QObject *parent) :
    QListView()
{
    setAcceptDrops(true);
}

void ListeImages::dragEnterEvent(QDragEnterEvent *event){
    event->accept();
    qDebug() << "ListeImages::dragEnterEvent -> MIME = " << event->mimeData()->urls().first().path();
}

void ListeImages::dragLeaveEvent(QDragLeaveEvent *e){
    e->accept();
}

void ListeImages::dragMoveEvent(QDragMoveEvent *e){
    e->accept();
}

void ListeImages::dropEvent(QDropEvent *e){
    e->accept();
}
