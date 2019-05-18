#include "filedriver.h"

FileDriver::FileDriver(QUrl url)
{
    this->url = url;
}

QImage FileDriver::loadImage()
{
    QFile file(url.toLocalFile());
    QPixmap pixmap;
    file.open(QIODevice::ReadOnly);
    pixmap.loadFromData(file.readAll());
    return QImage(pixmap.toImage().convertToFormat(QImage::Format_ARGB32));
}



