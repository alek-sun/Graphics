#include "imatrixfilter.h"

#include <QDebug>

IMatrixFilter::IMatrixFilter()
{

}

void IMatrixFilter::run(QImage image, QImage *outImage)
{
    int kern = (matrixSize % 2) != 0 ? matrixSize-1 : matrixSize;
    int h = image.height();
    w = image.width();

    bits = image.bits();
    bufBits = outImage->bits();

    int x, y, u, v, i, ix, iy, bi;
    int r = 0, g = 0, b = 0;

    for (y = 0; y < h; ++y){
        for (x = 0; x < w; ++x){
            i = 0;
            r = g = b = 0;

            for (u = -kern/2; u <= kern/2; ++u){
                if (u == 0 && (matrixSize % 2) == 0) continue;
                for (v = -kern/2; v <= kern/2; ++v){
                    if (v == 0 && (matrixSize % 2) == 0) continue;
                    if (x + v < 0){
                        ix = 0;
                    } else if (x + v >= w){
                        ix = w-1;
                    } else {
                        ix = x + v;
                    }

                    if (y + u < 0){
                        iy = 0;
                    } else if (y + u >= h){
                        iy = h-1;
                    } else {
                        iy = y + u;
                    }
                    bi = 4*(ix + iy*w);
                    r += matrix[i]*bits[bi + 2];
                    g += matrix[i]*bits[bi + 1];
                    b += matrix[i]*bits[bi];
                    ++i;
                }
            }
            //setPixelColor(x,y, QColor(clampRGB(r),clampRGB(g),clampRGB(b),clampRGB(a)), bufBits, w);
            threshold(x,y,r,g,b);            
        }
    }
}

void IMatrixFilter::threshold(int x, int y, int r, int g, int b)
{
    setPixelColor(x,y, QColor(clampRGB(r),clampRGB(g),clampRGB(b)), bufBits, w);
}


void IMatrixFilter::normalizeMatrix()
{
    int sum = 0;
    for (auto el : matrix){
        sum += el;
    }
    for (auto &el : matrix){
        el /= sum;
    }
}
