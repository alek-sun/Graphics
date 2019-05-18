#ifndef WATERCOLORFILTER_H
#define WATERCOLORFILTER_H

#include "imatrixfilter.h"

class WatercolorFilter : public IMatrixFilter
{
public:
    WatercolorFilter();

    // Effect interface
public:
    void run(QImage image, QImage *outImage);

};

#endif // WATERCOLORFILTER_H
