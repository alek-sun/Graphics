#include "negativeeffect.h"

NegativeEffect::NegativeEffect()
{

}

void NegativeEffect::run(QImage image, QImage *outImage)
{
    int i, j;
    QColor color;

    for (i = 0; i < image.height(); ++i){
        for (j = 0; j < image.width(); ++j){
            color = image.pixelColor(j, i);
            setPixelColor(j, i, QColor(255-color.red(), 255-color.green(), 255-color.blue(), color.alpha()),
                          outImage->bits(), outImage->width());
        }
    }
}
