#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QImage im(width(), height(), QImage::Format_ARGB32);

    uchar *bits = im.bits();
    int w = width();
    int h = height();
    int i, j, k;
    for (i = 0; i < w; i++){
        for (j = 0; j < h; j++){
            for(k = 0; k < 4; k++){
                bits[k + i*4 + j*w*4] = 0;
            }
        }
    }
}
