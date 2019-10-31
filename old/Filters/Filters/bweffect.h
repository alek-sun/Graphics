#ifndef BWEFFECT_H
#define BWEFFECT_H

#include "effect.h"

class BWEffect : public Effect
{
public:
    BWEffect();
    void run(QImage image, QImage* outImage);
};

#endif // BWEFFECT_H
