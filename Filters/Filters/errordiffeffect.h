#ifndef ERRORDIFFEFFECT_H
#define ERRORDIFFEFFECT_H

#include "effect.h"

class ErrorDiffEffect : public Effect
{
public:
    ErrorDiffEffect();
    void run(QImage image, QImage *outImage);
};

#endif // ERRORDIFFEFFECT_H
