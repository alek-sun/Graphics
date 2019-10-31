#include "sharpfilter.h"

SharpFilter::SharpFilter()
{
    matrix = {0,-1,0,
              -1,5,-1,
              0,-1,0};
    normalizeMatrix();
    matrixSize = 3;
}
