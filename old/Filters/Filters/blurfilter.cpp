#include "blurfilter.h"

BlurFilter::BlurFilter()
{
    matrix = {0,1,0,
              1,2,1,
              0,1,0};

    normalizeMatrix();
    matrixSize = 3;
}
