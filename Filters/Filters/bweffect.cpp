#include "bweffect.h"

BWEffect::BWEffect()
{

}

void BWEffect::run(QImage image, QImage *outImage)
{
    int i, j;
    double middle;
    QColor color;
    int h = image.height(), w = image.width();

    for (i = 0; i < h; ++i){
        for (j = 0; j < w; ++j){
            color = image.pixelColor(j, i);
            middle = 0.299*color.red()+0.587*color.green()+0.114*color.blue();
            setPixelColor(j, i,  QColor(middle, middle, middle, color.alpha()), outImage->bits(), w);
        }
    }
}
