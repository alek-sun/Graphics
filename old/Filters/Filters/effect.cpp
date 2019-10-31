#include "effect.h"


Effect::Effect()
{

}

Effect::Effect(const Effect &e)
{

}

Effect::~Effect()
{

}

void Effect::setPixelColor(int x, int y, QColor color, uchar *bits, int w)
{
    int i = 4*(x + y*w);
    bits[i] = color.blue();
    bits[i + 1] = color.green();
    bits[i + 2] = color.red();
    bits[i + 3] = color.alpha();
}

int Effect::clampRGB(int val)
{
    return val < 0 ? 0 : val > 255 ? 255 : val;
}

void Effect::setNeedRedraw(bool value)
{

}

QColor Effect::pixelColor(int x, int y, uchar *bits, int w)
{
    int i =4*(x + y*w);
    return QColor(bits[i + 2], bits[i + 1], bits[i], bits[i + 3]);
}
