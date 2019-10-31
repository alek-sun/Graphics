#ifndef FCALCULATOR_H
#define FCALCULATOR_H

#include <vector>
#include "math.h"
#include "float.h"
#include <QDebug>
#include "settings.h"


using std::vector;

class FCalculator
{
public:
    FCalculator(Settings *s);
    void buildGrid();
    double f(double x, double y);
    void getFLimits(double* min, double* max);
    void eps(double* f, double z);
    vector<double> grid;
    Settings* s;
    //vector<double> getGrid() const;
};

#endif // FCALCULATOR_H
