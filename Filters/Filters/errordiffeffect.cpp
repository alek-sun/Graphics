#include "errordiffeffect.h"
#include <QDebug>

ErrorDiffEffect::ErrorDiffEffect()
{

}

void ErrorDiffEffect::run(QImage image, QImage *outImage)
{
    int h = image.height();
    int w = image.width();

    int x, y, r, g, b, dr, dg, db;
    double k;
    QColor color, c, newColor;
    double  k1 = 7.0/16.0,
            k2 = 3.0/16.0,
            k3 = 5.0/16.0,
            k4 = 1.0/16.0;

    for (y = 0; y < h; ++y){
        for (x = 0; x < w; ++x){
            color = image.pixelColor(x,y);

            r = color.red() & 0xE0;
            g = color.green() & 0xE0;
            b = color.blue() & 0xC0;

            setPixelColor(x, y, QColor(r,g,b), image.bits(), w);

            dr = color.red()-r;
            dg = color.green()-g;
            db = color.blue()-b;

            if (x+1 < w){
                k = k1;
                c = pixelColor(x+1, y, image.bits(), w);

                newColor = QColor(  clampRGB(k*dr + c.red()),
                                    clampRGB(k*dg + c.green()),
                                    clampRGB(k*db + c.blue()));
                setPixelColor(x+1, y, newColor, image.bits(), w);

            }

            if (x-1 > 0 && y+1 < h){
                k = k2;
                c = pixelColor(x-1, y+1, image.bits(), w);

                newColor = QColor(  clampRGB(k*dr + c.red()),
                                    clampRGB(k*dg + c.green()),
                                    clampRGB(k*db + c.blue()));
                setPixelColor(x-1, y+1, newColor, image.bits(), w);

            }

            if (y+1 < h){
                k = k3;
                c = pixelColor(x, y+1, image.bits(), w);
                newColor = QColor(  clampRGB(k*dr + c.red()),
                                    clampRGB(k*dg + c.green()),
                                    clampRGB(k*db + c.blue()));
                setPixelColor(x, y+1, newColor, image.bits(), w);

            }

            if (x+1 < w && y+1 < h){
                k = k4;
                c = pixelColor(x+1, y+1, image.bits(), w);
                newColor = QColor(clampRGB(k*dr + c.red()),
                                  clampRGB(k*dg + c.green()),
                                  clampRGB(k*db + c.blue()));
                setPixelColor(x+1, y+1, newColor, image.bits(), w);

            }
        }
    }
    *outImage = image;
}
