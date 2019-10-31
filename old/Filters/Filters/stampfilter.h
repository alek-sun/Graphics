#ifndef STAMPFILTER_H
#define STAMPFILTER_H

#include "imatrixfilter.h"

class StampFilter : public IMatrixFilter
{
public:
    StampFilter();

    // IMatrixFilter interface
public:
    void threshold(int x, int y, int r, int g, int b);
};

#endif // STAMPFILTER_H
