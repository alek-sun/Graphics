#ifndef SOBEL_H
#define SOBEL_H

#include "imatrixfilter.h"
#include "cwidget.h"

using std::vector;

class Sobel : public IMatrixFilter
{
public:
    Sobel(CWidget::Settings* s);
    void run(QImage image, QImage *outImage);
private:
    void threshold(int x, int y, int r, int g, int b);
    int count = 1;
    vector<QColor> s1;
    vector<QColor> s2;
    CWidget::Settings* settings;

    // Effect interface
public:
    void setNeedRedraw(bool value);
};

#endif // SOBEL_H
