#include "daiconmachina.h"

DaIconMachina::DaIconMachina()
{
}

QIcon DaIconMachina::icon(const QFileInfo &info) const {
    QIcon iconeRetour = QIcon(QPixmap(64,64));
    if(info.suffix() == "jpg" || info.suffix() == "bmp"
            || info.suffix() == "gif" || info.suffix() == "pgm" || info.suffix() == "xpm"
            || info.suffix() == "jpeg" || info.suffix() == "ppm" || info.suffix() == "svg"
            || info.suffix() == "mng" || info.suffix() == "tiff" || info.suffix() == "tga"
            || info.suffix() == "png" || info.suffix() == "xbm" || info.suffix() == "pbm"){
        iconeRetour = QIcon(info.absoluteFilePath());
    }
    return iconeRetour;
}
