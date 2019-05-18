#include "gammaeffect.h"

GammaEffect::GammaEffect(CWidget::Settings *s)
{
    this->s = s;
}

void GammaEffect::run(QImage image, QImage *outImage)
{
    int i, j, r, g, b;
    int w = image.width();
    double gamma = 1.0/s->gamma;
    QColor color;
    for (j = 0; j < image.height(); j++){
        for (i = 0; i < w; i++){
            color = pixelColor(i,j,image.bits(), w);
            r = pow(color.red(), gamma);
            g = pow(color.green(), gamma);
            b = pow(color.blue(), gamma);
            setPixelColor(i,j,QColor(clampRGB(r),
                                     clampRGB(g),
                                     clampRGB(b),255), outImage->bits(), w);
        }
    }
}

void GammaEffect::setNeedRedraw(bool value)
{
    needRedraw = true;
}

