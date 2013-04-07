#ifndef DAICONMACHINA_H
#define DAICONMACHINA_H

#include <QtGui>
#include <QFileIconProvider>

class DaIconMachina : public QFileIconProvider
{
public:
    DaIconMachina();
protected:
    QIcon icon(const QFileInfo &info) const;
};

#endif // DAICONMACHINA_H
