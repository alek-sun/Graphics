#ifndef FILEDRIVER_H
#define FILEDRIVER_H
#include <QImage>

#include <QUrl>
#include <QFile>
#include <QPixmap>
class FileDriver
{

private:
    QUrl url;
public:
    FileDriver(QUrl url);
    QImage loadImage();
    bool saveImage(QUrl url, QImage image);
};

#endif // FILEDRIVER_H
