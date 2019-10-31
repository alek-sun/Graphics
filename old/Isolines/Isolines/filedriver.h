#ifndef FILEDRIVER_H
#define FILEDRIVER_H

#include <QUrl>
#include <vector>
#include "isolinewidget.h"

using std::vector;

class FileDriver
{
public:
    FileDriver(QUrl url);
    vector<double> parseFunction();
    bool parseSettings(Settings *s);
private:
    QUrl url;

};

#endif // FILEDRIVER_H
