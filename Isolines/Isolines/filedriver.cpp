#include "filedriver.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

FileDriver::FileDriver(QUrl url)
{
    this->url = url;
}

vector<double> FileDriver::parseFunction()
{
    QFile file(url.toLocalFile());
    QString str;
    vector<double> grid;

    file.open(QIODevice::ReadOnly);

    if (!file.exists()){
        return grid;
    }

    str = file.readLine();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(str.toUtf8());
    QJsonArray lines = jsonResponse.object()["values"].toArray();
    foreach (const QJsonValue & line, lines) {
        foreach (const QJsonValue & value, line.toArray()) {
            grid.push_back(value.toDouble());
        }
    }
    return grid;
}

bool FileDriver::parseSettings(Settings *s)
{
    QString str, digits;
    QFile file(url.toLocalFile());
    QStringList list;
    vector<pair<int, int>> coords;

    file.open(QIODevice::ReadOnly);

    if (!file.exists()){
        return false;
    }

    int i = 0, countCells = 2;
    vector<QColor> colors;

    while (!file.atEnd() && i <= countCells){

        str = file.readLine();
        if (str == "\r\n")
            continue;
        list = str.split("//");
        digits = list[0];

        if (i == 0){
            QStringList km = digits.split(" ");
            if (km.size() < 2)
                return false;
            s->k = km[0].toInt();
            s->m = km[1].toInt();
            ++i;
        } else if (i == 1){
            ++i;
            QStringList n_val = digits.split(" ");
            if (n_val[0].toInt() > 24)
                return false;
            countCells = i+n_val[0].toInt();
        } else {
             QStringList rgb_val = digits.split(" ");
             if (rgb_val.size() < 3)
                 return false;
             if (i == countCells){
                 s->isolineColor = QColor(     rgb_val[0].toInt(),
                                               rgb_val[1].toInt(),
                                               rgb_val[2].toInt(), 255);
                ++i;
             } else {
                 colors.push_back(QColor(
                                                rgb_val[0].toInt(),
                                                rgb_val[1].toInt(),
                                                rgb_val[2].toInt(), 255));
                 ++i;
            }
        }
    }
    s->legendColors.clear();
    s->userIsolines.clear();
    s->legendColors.insert(s->legendColors.end(), colors.begin(), colors.end());
    s->fillColorMap();
    return true;
}
