#include "sobel.h"

Sobel::Sobel(CWidget::Settings *s)
{
    settings = s;
    matrix = {-1,0,1,
              -2,0,2,
              -1,0,1};
    for (auto &el : matrix){
        el *= 0.25;
    }
    matrixSize = 3;
}

void Sobel::run(QImage image, QImage *outImage)
{
    int x, y, newR, newG, newB, i;
    IMatrixFilter::run(image, outImage);
    matrix = {-1,-2,-1,
              0,0,0,
              1,2,1};
    for (auto &el : matrix){
        el *= 0.25;
    }
    count++;
    IMatrixFilter::run(image, outImage);
    for (y = 0; y < image.height(); ++y){
        for (x = 0; x < image.width();++x){
            i = y*w+x;
            if (s1[i].red() + s2[i].red() > settings->sobel){
                newR = s1[i].red() + s2[i].red();
            } else {
                newR = 0;
            }

            if (s1[i].green() + s2[i].green() > settings->sobel){
                newG = s1[i].green() + s2[i].green();
            } else {
                newG = 0;
            }

            if (s1[i].blue() + s2[i].blue() > settings->sobel){
                newB = s1[i].blue() + s2[i].blue();
            } else {
                newB = 0;
            }
            setPixelColor(x, y, QColor(clampRGB(newR), clampRGB(newG), clampRGB(newB), 255), outImage->bits(), w);
        }

    }
}

void Sobel::threshold(int x, int y, int r, int g, int b)
{
    int newR, newG, newB;
    newR = abs(r);
    newG = abs(g);
    newB = abs(b);

    if (count == 1){
        s1.push_back(QColor(newR, newG, newB, 255));
    } else {
        s2.push_back(QColor(newR, newG, newB, 255));
    }
}

void Sobel::setNeedRedraw(bool value)
{
    needRedraw = value;
}
