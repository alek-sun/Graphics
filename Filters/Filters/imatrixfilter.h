#ifndef IMATRIXFILTER_H
#define IMATRIXFILTER_H

#include "effect.h"

#include <QImage>

using std::vector;

class IMatrixFilter : public Effect
{
public:
    IMatrixFilter();
    virtual ~IMatrixFilter() {}

    void run(QImage image, QImage *outImage);
    virtual void threshold(int x, int y, int r, int g, int b);

protected:
    int matrixSize;
    vector<double> matrix;
    uchar* bits;
    uchar* bufBits;
    int w;

    void normalizeMatrix();   

public:

};

#endif // IMATRIXFILTER_H
