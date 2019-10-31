#include "legendwidget.h"
#include <QDebug>

LegendWidget::LegendWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(580, 70, QImage::Format_ARGB32);
    image.fill(QColor(255, 255, 255, 255));
}

void LegendWidget::setSettings(Settings *value)
{
    settings = value;
}

void LegendWidget::fillInterpolationRect(int x, int y, int w, int h, QColor c1, QColor c2)
{
    double i;
    int j, r, g, b;
    double df = 0.0;
    QColor color;
    for (j = 0; j < h; j++){
        for (i = 0.0; i < w; ++i) {
            df = i/w;
            r = c1.red()*(1.0 - df) + c2.red()*df;
            g = c1.green()*(1.0 - df) + c2.green()*df;
            b = c1.blue()*(1.0 - df) + c2.blue()*df;
            color = QColor(r, g, b, 255);

            IsolineWidget::setPixelColor(shift+i,y+j, color, image.bits(), image.width());
        }
    }
}

void LegendWidget::redrawLegend()
{
    QPainter p(&image);

    p.setPen(QColor(0,0,0,255));
    p.setFont(QFont("Helvetica", 7, QFont::Thin));

    int n = settings->colorMap.size();
    if (n != 0){
        double step;
        int h, legendStart = 40;
        if (n <= 12){
            step = ceil(500 / n);
            h = 20;
        } else {
            step = ceil(500 / 12);
            h = 10;
        }

        y = -20;
        int i, next;
        pair<double, QColor> el;
        for (i = 0; i < n; ++i){
            el = settings->colorMap[i];
            if (i % 12 == 0){
                y += 30;
                shift = legendStart;
            }
            if (!interpolation){
                p.fillRect(shift, y, step, h, el.second);
            } else {
                if (i+1 == n){
                    next = i;
                } else {
                    next = i+1;
                }
                fillInterpolationRect(shift, y, step, h, el.second, settings->colorMap[next].second);
            }

            p.drawRect(shift, y, step, h);
            p.drawText(QPoint(shift+step-(QString::number(el.first, 'd', 2).size()-1), y+2*h+3), QString::number(el.first, 'd', 2));
            shift = ceil(shift + step);

        }
    }
}

void LegendWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    image.fill(QColor(220, 220, 220, 150));
    redrawLegend();
    p.drawImage(0,0, image);
    image = QImage(580, 70, QImage::Format_ARGB32);
}

