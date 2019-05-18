#ifndef ORDERDITHEREFFECT_H
#define ORDERDITHEREFFECT_H

#include "effect.h"

using std::vector;

class OrderDitherEffect : public Effect
{
public:
    OrderDitherEffect();

    void run(QImage image, QImage *outImage);
private:
    vector<int> nextMatrix(vector<int> m);
};

#endif // ORDERDITHEREFFECT_H
