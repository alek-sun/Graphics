#ifndef ROBERTSEFFECT_H
#define ROBERTSEFFECT_H

#include "effect.h"
#include "cwidget.h"
#include "imatrixfilter.h"

class RobertsEffect : public IMatrixFilter
{
public:
    RobertsEffect(CWidget::Settings* s);

    void threshold(int x, int y, int r, int g, int b);    
    void run(QImage image, QImage *outImage);
private:
    CWidget::Settings* settings;
    vector<QColor> g1;
    vector<QColor> g2;
    int count = 1;

    // Effect interface
public:
    void setNeedRedraw(bool value);
};

#endif // ROBERTSEFFECT_H
