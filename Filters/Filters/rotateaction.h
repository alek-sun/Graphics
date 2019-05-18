#ifndef ROTATEACTION_H
#define ROTATEACTION_H

#include "cwidget.h"
#include "effect.h"

class RotateAction : public Effect
{
public:
    RotateAction(CWidget::Settings *s, int sizeX, int sizeY);

    void run(QImage image, QImage *outImage);
    CWidget::Settings* s;
private:
    int sizeX;
    int sizeY;
    const double M_PI = 3.14;
};

#endif // ROTATEACTION_H
