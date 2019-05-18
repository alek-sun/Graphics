#ifndef NEGATIVEEFFECT_H
#define NEGATIVEEFFECT_H

#include "effect.h"

class NegativeEffect : public Effect
{
public:
    NegativeEffect();

    void run(QImage image, QImage *outImage);
};

#endif // NEGATIVEEFFECT_H
