#ifndef FILEDRIVER_H
#define FILEDRIVER_H

#include "settings.h"

#include <QUrl>

class FileDriver
{
public:
    FileDriver(QUrl url);
    void openModel(Settings* s);
    void saveModel(Settings s);
private:
    QUrl url;
};

#endif // FILEDRIVER_H
