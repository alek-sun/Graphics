#ifndef GAMMAEFFECT_H
#define GAMMAEFFECT_H

#include "cwidget.h"
#include "effect.h"

class GammaEffect : public Effect
{
public:
    GammaEffect(CWidget::Settings *s);
    void run(QImage image, QImage *outImage);
private:
    CWidget::Settings *s;

    // Effect interface
public:
    void setNeedRedraw(bool value);
};

#endif // GAMMAEFFECT_H
