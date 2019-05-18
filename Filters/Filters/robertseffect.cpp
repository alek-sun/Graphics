#include "robertseffect.h"

RobertsEffect::RobertsEffect(CWidget::Settings *s)
{
    settings = s;
    matrix = {
        1,0,
        0,-1
    };
    matrixSize = 2;
}

void RobertsEffect::threshold(int x, int y, int r, int g, int b)
{
    int newR, newG, newB;
    newR = abs(r);
    newG = abs(g);
    newB = abs(b);

    if (count == 1){
        g1.push_back(QColor(newR, newG, newB, 255));
    } else {
        g2.push_back(QColor(newR, newG, newB, 255));
    }
}

void RobertsEffect::run(QImage image, QImage *outImage)
{
    int x,y, newR, newG, newB,  i;
    IMatrixFilter::run(image, outImage);
    count++;

    matrix = {
        0,1,
        -1,0
    };

    IMatrixFilter::run(image, outImage);

    for (y = 0; y < image.height(); ++y){
        for (x = 0; x < image.width();++x){
            i = y*w+x;
            if (g1[i].red() + g2[i].red() > settings->roberts){
                newR = g1[i].red() + g2[i].red();
            } else {
                newR = 0;
            }

            if (g1[i].green() + g2[i].green() > settings->roberts){
                newG = g1[i].green() + g2[i].green();
            } else {
                newG = 0;
            }

            if (g1[i].blue() + g2[i].blue() > settings->roberts){
                newB = g1[i].blue() + g2[i].blue();
            } else {
                newB = 0;
            }

            setPixelColor(x, y, QColor(clampRGB(newR), clampRGB(newG), clampRGB(newB), 255), outImage->bits(), w);
        }
    }    
}

void RobertsEffect::setNeedRedraw(bool value)
{
    needRedraw = value;
}
