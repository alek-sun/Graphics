#include "awidget.h"


AWidget::AWidget(QWidget *parent) : QWidget(parent)
{
    origImage = QImage(350, 350, QImage::Format_ARGB32);
    origImage.fill(QColor(255,255,255,255));
    paintImage = QImage(350, 350, QImage::Format_ARGB32);
    paintImage.fill(QColor(255,255,255,255));
    rectX1 = -1;
    rectY1 = -1;
    rectX2 = -1;
    rectY2 = -1;
    sizeX = 0;
    sizeY = 0;
}

void AWidget::setPixelColor(int x, int y, QColor color)
{
    int i = x + y*width();
    i *= 4;
    bits[i] = color.blue();
    bits[i + 1] = color.green();
    bits[i + 2] = color.red();
    bits[i + 3] = color.alpha();
}

QColor AWidget::pixelColor(int x, int y)
{
    int i = x + y*width();
    i *= 4;
    return QColor(bits[i + 2], bits[i + 1], bits[i], bits[i + 3]);
}

void AWidget::setImage(const QImage &value)
{    
    origImage = value;    
    paintImage = origImage;
}

void AWidget::setSizeX(int value)
{
    sizeX = value;
}

void AWidget::setSizeY(int value)
{
    sizeY = value;
}

void AWidget::setK(double value)
{
    k = value;
}

void AWidget::drawRect()
{
    int i, j;
    QColor curColor, newColor;
    if (rectX1 == 0 && rectX2 == sizeX) return;
    for ( i = 0 ; i < sizeY ; ++i){
        for ( j = 0 ; j < sizeX ; ++j){
            if ( i > rectY1 && i < rectY2 && j > rectX1 && j < rectX2 )
                continue;
            curColor = pixelColor(j, i);
            newColor = QColor(curColor.red()*0.4,
                             curColor.green()*0.4,
                             curColor.blue()*0.4,
                             curColor.alpha());

            setPixelColor(j, i, newColor);
        }
    }
}

void AWidget::clearRect()
{
    rectX1 = 0;
    rectY2 = -1;
    rectX2 = sizeX;
    rectY1 = -1;
    repaint();
}

int AWidget::getRectX1() const
{
    return rectX1;
}

void AWidget::setRectX1(int value)
{

    if (value < 0){
        rectX1 = 0;
        return;
    }
    if (value > sizeX){
        rectX1 = sizeX;
        return;
    }
    rectX1 = value;
}

int AWidget::getRectY1() const
{
    return rectY1;
}

void AWidget::setRectY1(int value)
{
    if (value < 0){
        rectY1 = 0;
        return;
    }
    if (value > sizeY){
        rectY1 = sizeY;
        return;
    }
    rectY1 = value;
}

int AWidget::getRectX2() const
{
    return rectX2;
}

void AWidget::setRectX2(int value)
{
    if (value < 0){
        rectX2 = 0;
        return;
    }
    if (value > sizeX){
        rectX2 = sizeX;
        return;
    }
    rectX2 = value;
}

int AWidget::getRectY2() const
{
    return rectY2;
}

void AWidget::setRectY2(int value)
{
    if (value < 0){
        rectY2 = 0;
        return;
    }
    if (value > sizeY){
        rectY2 = sizeY;
        return;
    }
    rectY2 = value;
}


/*void AWidget::findRectCoords()
{
    if (rectX2 > rectX1){
        if (rectY1 > rectY2){
            lTopX = rectX1;
            lTopY = rectY2;
            rBottomX = rectX2;
            rBottomY = rectY1;
        } else {
            lTopX = rectX1;
            lTopY = rectY1;
            rBottomX = rectX2;
            rBottomY = rectY2;
        }
    } else {
        if (rectY1 > rectY2){
            lTopX = rectX2;
            lTopY = rectY2;
            rBottomX = rectX1;
            rBottomY = rectY1;
        } else {
            lTopX = rectX2;
            lTopY = rectY1;
            rBottomX = rectX1;
            rBottomY = rectY2;
        }
    }
}*/

void AWidget::centerSquare(int x1, int x2, int y1, int y2)
{
    setRectX1(x1);
    setRectX2(x2);
    setRectY1(y1);
    setRectY2(y2);
    selected(rectX1, rectY1, rectX2, rectY2);
    repaint();
}

void AWidget::paintEvent(QPaintEvent *event)
{    
    QPainter painter(this);
    drawRect();
    painter.drawImage(0, 0, paintImage);
    paintImage = origImage;
    bits = paintImage.bits();
}

void AWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    mousePressed = true;

    if (selectOn){       
        int d = round(175/k);
        if (x+d > sizeX)
            x = sizeX - d;
        if (y+d > sizeY)
            y = sizeY - d;
        if (x-d < 0)
            x = d;
        if (y-d < 0)
            y = d;

        setRectX1(x-d);
        setRectX2(x+d);
        setRectY1(y-d);
        setRectY2(y+d);
        selected(rectX1, rectY1, rectX2, rectY2);
        repaint();

        if (y > rectY1 && y < rectY2 && x > rectX1 && x < rectX2 ){
            lastX = x;
            lastY = y;
        }
    }
}

void AWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
}

void AWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int dx, dy;

    if (mousePressed && selectOn){
        dx = x - lastX;
        dy = y - lastY;

        if (rectY2 >= sizeY && dy > 0) return;
        if (rectX2 >= sizeX && dx > 0) return;
        if (rectX1 <= 0 && dx < 0) return;
        if (rectY1 <= 0 && dy < 0) return;

        if (rectX2+dx > sizeX)
            dx = sizeX - rectX2;
        if (rectY2+dy > sizeY)
            dy = sizeY - rectY2;
        if (rectX1+dx < 0)
            dx = -rectX1;
        if (rectY1+dy < 0)
            dy = -rectY1;


        setRectX1(rectX1+dx);
        setRectX2(rectX2+dx);
        setRectY1(rectY1+dy);
        setRectY2(rectY2+dy);
        selected(rectX1, rectY1, rectX2, rectY2);

        repaint();
        lastX = x;
        lastY = y;
    }
}

