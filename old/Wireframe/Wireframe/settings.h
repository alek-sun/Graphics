#ifndef SETTINGS_H
#define SETTINGS_H
#include <QColor>
#include <QMatrix4x4>
#include <QVector2D>
#include <vector>
using std::vector;
using std::pair;

class Settings
{
public:
    Settings();
    int hidingSplane;
    int hidingAngle;
    int splaneN;
    int angleN;
    double z;

    QMatrix4x4 matrix;
    double nCurveSplit;
    int pointR;
    QColor backgroudColor;
    QColor bodyColor;

    vector<QVector2D*> bearingPoints;
    vector<QVector2D*> allPoints;
};

#endif // SETTINGS_H
