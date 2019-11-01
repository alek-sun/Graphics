#ifndef IMAGERESIZER_H
#define IMAGERESIZER_H
#include <QImage>
#include <QDebug>
#include <cmath>

class ImageResizer
{
private:
    QImage image;
    int newSizeX, newSizeY;
    double k;
public:
    ImageResizer(QImage image);
    QImage resize(double sizeX, double sizeY);
    static void redrawImage(QImage origImage, QImage *image, int lTopX, int lTopY, int rBottomX, int rBottomY);
    void setImage(const QImage &value);
    int getNewSizeY() const;
    int getNewSizeX() const;
    double getK() const;
    QColor getBilinearColor(double mx, double my);
};

#endif // IMAGERESIZER_H
