#ifndef EFFECT_H
#define EFFECT_H

#include <QImage>

class Effect
{
public:
    Effect();
    Effect(const Effect & e);
    virtual void run(QImage image, QImage* outImage) = 0;
    virtual ~Effect();

    QColor pixelColor(int x, int y, uchar* bits, int w);
    void setPixelColor(int x, int y, QColor color, uchar *bits, int w);
    int clampRGB(int v);
    bool needRedraw = true;

    virtual void setNeedRedraw(bool value);
};

#endif // EFFECT_H
