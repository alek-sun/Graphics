#include "stampfilter.h"

StampFilter::StampFilter()
{
    matrix = {0,1,0,
              -1,0,1,
              0,-1,0};
    matrixSize = 3;
}

void StampFilter::threshold(int x, int y, int r, int g, int b)
{
    r+=128;
    g+=128;
    b+=128;
    setPixelColor(x,y, QColor(clampRGB(r),clampRGB(g),clampRGB(b)), bufBits, w);
}
