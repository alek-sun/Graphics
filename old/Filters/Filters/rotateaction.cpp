#include "cwidget.h"
#include "imageresizer.h"
#include "rotateaction.h"

RotateAction::RotateAction(CWidget::Settings* s, int sizeX, int sizeY)
{
    this->s = s;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    needRedraw = false;
}

void RotateAction::run(QImage image, QImage *outImage)
{
    int i, j, x, y;
    int h = image.height();
    int w = image.width();
    QPoint res;
    int a = s->angle;

    *outImage = QImage(350, 350, QImage::Format_ARGB32);
    outImage->fill(QColor(255,255,255,255));

    double c;

    if (abs(a) <= 45){
        if (a > 0) {
            c = 1/cos(M_PI/4 - static_cast<double>(a)/180.0*M_PI)/sqrt(2);
        } else {
            c = 1/cos(M_PI/4 + static_cast<double>(a)/180.0*M_PI)/sqrt(2);
        }
    } else if (abs(a) >= 135){
        if (a > 0){
            c = 1/cos(M_PI/4 - static_cast<double>(180-a)/180.0*M_PI)/sqrt(2);
        } else {
            c = 1/cos(M_PI/4 - static_cast<double>(180+a)/180.0*M_PI)/sqrt(2);
        }
    } else if (abs(a) > 45 && abs(a) < 135){
        if (a > 0){
            c = 1/cos(M_PI/4 - static_cast<double>(abs(90-a))/180.0*M_PI)/sqrt(2);
        } else {
            c = 1/cos(M_PI/4 - static_cast<double>(abs(90+a))/180.0*M_PI)/sqrt(2);
        }
    }

    int shift_x = sizeX/2, shift_y = sizeY/2;
    QMatrix rotationMatrix;
    rotationMatrix.translate(shift_x, shift_y);
    rotationMatrix.rotate(a);

    if (a % 90 != 0) {
        rotationMatrix.scale(c,c);
    }

    //int kw = w*c;

    //qDebug() << c << " kw = " << kw;


    bool incr = true;

    for (j = 0; j < h; ++j){
        for (i = 0; i < w; ++i){
            incr = true;
            QPoint p(i-shift_x, j-shift_y);
            res = p*rotationMatrix;
            x = res.x();
            y = res.y();

           //qDebug() << (static_cast<int>(scaled_i)%kw)/c  << " " << scaled_i/kw/c << "     " << scaled_i;

            if (x < 0 || y < 0 || x >= 350 || y >= 350 ) continue;

            setPixelColor(x, y, pixelColor(i, j, image.bits(), image.width()), outImage->bits(), outImage->width());
            //setPixelColor(x, y, resizer.getBilinearColor((static_cast<int>(scaled_i)%kw)/c, scaled_i/kw/c), outImage->bits(), outImage->width());
        }
    }

}
