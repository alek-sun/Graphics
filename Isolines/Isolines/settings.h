#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <map>
#include <QColor>

using std::vector;
using std::map;
using std::pair;

class Settings
{
public:
    Settings();
    int k, m;
    double a, b, c, d;
    vector<QColor> legendColors;
    vector<pair<double, QColor>> colorMap;

    vector<double> isolineLevels;

    QColor isolineColor;
    QColor pointsColor;
    vector<double> userIsolines;
    bool changed = true;

    void fillColorMap();

};

#endif // SETTINGS_H
