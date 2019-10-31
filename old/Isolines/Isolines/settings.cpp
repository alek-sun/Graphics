#include "fcalculator.h"
#include "settings.h"

using std::pair;

Settings::Settings()
{
    this->k = 10;
    this->m = 10;
    this->a = 0;
    this->b = 5;
    this->c = 0;
    this->d = 5;
    pointsColor = QColor(150,0,0,255);
}

void Settings::fillColorMap()
{
    colorMap.clear();
    isolineLevels.clear();
    FCalculator f(this);
    double min, max;
    f.getFLimits(&min, &max);
    double step = (max - min) / legendColors.size();
    int count = 1;
    for (auto color : legendColors){
        colorMap.push_back(pair <double, QColor>(min + count*step, color));
        isolineLevels.push_back(min + count*step);
        count++;
    }
}

