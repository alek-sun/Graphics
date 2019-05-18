#include "imageresizer.h"


void ImageResizer::setImage(const QImage &value)
{
    image = value;
    newSizeX = 0;
    newSizeY = 0;
    k = 1;
}

int ImageResizer::getNewSizeY() const
{
    return newSizeY;
}

int ImageResizer::getNewSizeX() const
{
    return newSizeX;
}

double ImageResizer::getK() const
{
    return k;
}

QColor ImageResizer::getBilinearColor(double mx, double my)
{
    double x1, x2, y1, y2, dx, dy;
    int r, g, b;
    double c1, c2;
    QColor color1, color2, color3, color4;

    dx = mx - trunc(mx);
    dy = my - trunc(my);

    x1 = floor(mx);
    x2 = ceil(mx);
    y1 = floor(my);
    y2 = ceil(my);

    color1 = image.pixelColor(x1, y1);
    color2 = image.pixelColor(x2, y1);
    color3 = image.pixelColor(x1, y2);
    color4 = image.pixelColor(x2, y2);

    c1 = color1.red()*(1-dx)+color2.red()*dx;
    c2 = color3.red()*(1-dx)+color4.red()*dx;
    r = round(c1*(1-dy) + c2*dy);

    c1 = color1.green()*(1-dx)+color2.green()*dx;
    c2 = color3.green()*(1-dx)+color4.green()*dx;
    g = round(c1*(1-dy) + c2*dy);

    c1 = color1.blue()*(1-dx)+color2.blue()*dx;
    c2 = color3.blue()*(1-dx)+color4.blue()*dx;
    b = round(c1*(1-dy) + c2*dy);
    return QColor(r,g,b,255);
}

ImageResizer::ImageResizer(QImage image)
{
    this->image = image;
}

QImage ImageResizer::resize(double sizeX, double sizeY)
{
    double ky = image.height()/sizeY;
    double kx = image.width()/sizeX;
    k = ky > kx ? ky : kx;

    double mx = 0, my = 0;  //  source image position

    QImage newImg(350, 350, QImage::Format_ARGB32);
    newImg.fill(QColor(255,255,255,255));
    int i, j;

    for (j = 0; j < sizeY; ++j, my+=k){
        if (ceil(my) >= image.height()){
            break;
        }
        for (i = 0; i < sizeX; ++i, mx+=k){
            if (ceil(mx) >= image.width()){
                break;
            }
            newImg.setPixelColor(i, j, getBilinearColor(mx, my));
        }
        mx = 0;
    }
    newSizeX = i;
    newSizeY = j;
    return newImg;
}

void ImageResizer::redrawImage(QImage origImage, QImage *image, int lTopX, int lTopY, int rBottomX, int rBottomY)
{
    int i, j;
    int startY = -1, startX = -1;

    QColor curColor;
    image->fill(QColor(255,255,255,255));

    for ( i = 0 ; i < origImage.height() ; ++i){
        for ( j = 0 ; j < origImage.width() ; ++j){
            if ( i >= lTopY && i <= rBottomY && j >= lTopX && j <= rBottomX ){
                if (startY == -1){
                    startY = i;
                }
                if (startX == -1){
                    startX = j;
                }
                if (j-startX >= image->width() || i-startY >= image->height()) continue;
                curColor = origImage.pixelColor(j, i);
                image->setPixelColor(j-startX, i-startY, curColor);
            }
        }
    }
}
