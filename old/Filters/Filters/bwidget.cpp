#include "bwidget.h"

BWidget::BWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(350, 350, QImage::Format_ARGB32);
    image.fill(QColor(255,255,255,255));
}

void BWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
    image = QImage(image);    
}
