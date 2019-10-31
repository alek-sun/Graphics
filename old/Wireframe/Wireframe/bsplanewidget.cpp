#include "bsplanewidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QVector4D>
#include <QMatrix4x4>
#include <math.h>

BSplaneWidget::BSplaneWidget(QWidget *parent) : QWidget(parent)
{
    w = 650;
    h = 400;
    axesColor = QColor(0, 150, 255);
    lineColor = QColor(0, 70, 160);
    splaneColor = QColor(255, 180, 0);

    image = QImage(w, h, QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,255));

    movingIndex = -1;
    deleteMode = false;
    addPointMode = false;
}


void BSplaneWidget::setSettings(Settings *value)
{
    settings = value;
}

void BSplaneWidget::setPixelColor(int x, int y, QColor color, uchar *bits, int w)
{
    int i = 4*(x + y*w);
    bits[i] = color.blue();
    bits[i + 1] = color.green();
    bits[i + 2] = color.red();
    bits[i + 3] = color.alpha();
}

int BSplaneWidget::addPoint(double x, double y)
{
    if (settings->bearingPoints.empty()){
        settings->bearingPoints.push_back(new QVector2D(x,y));
        return 0;
    }
    int i = 0;
    vector<QVector2D*>::iterator it = settings->bearingPoints.begin();
    for (; it != settings->bearingPoints.end(); ++it,++i){
        if (sqrt(pow(x - (*it)->x(), 2) + pow(y - (*it)->y(), 2)) <= settings->pointR){
            setCursor(Qt::ClosedHandCursor);
            return i;
        }
        if ((*it)->x() >= x){
            settings->bearingPoints.insert(it, new QVector2D(x,y));
            return i;
        }
    }
    settings->bearingPoints.push_back(new QVector2D(x,y));
    return i;
}

void BSplaneWidget::drawAxes()
{
    int i, lvl = h/2;
    for (i = 0; i < w; ++i){
        setPixelColor(i, lvl, axesColor, image.bits(), w);
    }
    lvl = w/2;
    for (i = 0; i < h; ++i){
        setPixelColor(lvl, i, axesColor, image.bits(), w);
    }
}

void BSplaneWidget::paintEvent(QPaintEvent *event)
{
    image = QImage(w, h, QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,255));
    drawPoints();
    drawLines();
    drawSplane();
    drawAxes();
    QPainter p(this);
    p.drawImage(0,0,image);
}

void BSplaneWidget::drawPoints()
{
    int i = 0;
    QPainter p(&image);
    p.setBrush(QColor(155,105,255,255));
    for (auto it : settings->bearingPoints){
        p.drawEllipse(it->x(), it->y(), settings->pointR, settings->pointR);
        //p.drawText(QPoint(it->x(), it->y()), QString::number(i));
        ++i;
    }
}

void BSplaneWidget::drawSplane()
{
    int i = 0, j;
    vector<QVector2D*> points = settings->bearingPoints;
    if (points.size() < 4 || points.empty()) return;
    settings->allPoints.clear();
    QMatrix4x4 m(-1,3,-3,1,
                 3,-6,3,0,
                 -3,0,3,0,
                 1,4,1,0);
    m /= 6.0;

    double t;
    double incr = 1.0 / settings->nCurveSplit;
    QVector2D last;

    for (i = 1; i < points.size()-2; ++i){
        for (t = 0.0, j = 0; j <= settings->nCurveSplit; j++, t+=incr){
            QMatrix4x4 p(
                    points[i-1]->x(), points[i-1]->y(), 0, 0,
                    points[i]->x(), points[i]->y(), 0, 0,
                    points[i+1]->x(), points[i+1]->y(), 0, 0,
                    points[i+2]->x(), points[i+2]->y(), 0, 0);
            QVector4D tvect(t*t*t, t*t, t, 1.0);
            QVector4D res = tvect*m*p;            

            if (t != 0.0 || i == 1){
                settings->allPoints.push_back(new QVector2D(res.x()-w/2, h/2 - res.y()));
                if (t != 0.0)
                    drawLine(last.x(),last.y(), res.x(), res.y(), splaneColor);
            }            
            last.setX(res.x());
            last.setY(res.y());
        }
    }

}

void BSplaneWidget::deletePoint(int x, int y)
{
    int ind = -1, i = 0;
    for (auto p : settings->bearingPoints){
        if (sqrt(pow(x - p->x(), 2) + pow(y - p->y(), 2)) <= settings->pointR) {
            ind = i;
            break;
        }
        ++i;
    }
    if (ind != -1){        
        settings->bearingPoints.erase(settings->bearingPoints.begin()+ind);
    }
}

void BSplaneWidget::mousePressEvent(QMouseEvent *event)
{
    double x = event->x();
    double y = event->y();

    if (deleteMode){
        deletePoint(x,y);
        pointCountChanged(settings->bearingPoints.size());
        repaint();
    } else if (addPointMode){
        movingIndex = addPoint(x,y);
        pointCountChanged(settings->bearingPoints.size());
        repaint();
    } else if (!settings->bearingPoints.empty()) {
        int i;
        for (i = 0; i < settings->bearingPoints.size(); ++i){
            if (sqrt(pow(x - settings->bearingPoints[i]->x(), 2) + pow(y - settings->bearingPoints[i]->y(), 2)) <= settings->pointR){
                movingIndex = i;
                setCursor(Qt::ClosedHandCursor);
                break;
            }
        }
    }
}

void BSplaneWidget::mouseReleaseEvent(QMouseEvent *event)
{
    movingIndex = -1;
    setCursor(Qt::PointingHandCursor);
}

void BSplaneWidget::mouseMoveEvent(QMouseEvent *event)
{
    double x = event->x();
    double y = event->y();

    if (x < 0 || x >= w || y < 0 || y >= h) return;

    if (movingIndex != -1){
        if (movingIndex != 0 && x <= settings->bearingPoints[movingIndex - 1]->x()){
            x = settings->bearingPoints[movingIndex - 1]->x()+1;
        }
        if (movingIndex != settings->bearingPoints.size()-1 && x >= settings->bearingPoints[movingIndex + 1]->x()){
            x = settings->bearingPoints[movingIndex + 1]->x()-1;
        }

        vector<QVector2D*>::iterator it = settings->bearingPoints.begin()+movingIndex;
        settings->bearingPoints.erase(it);
        settings->bearingPoints.insert(it, new QVector2D(x,y));
        repaint();
    }
}

void BSplaneWidget::drawLine(int x0, int y0, int x1, int y1, QColor color)
{
    int dx = abs(x0 - x1);
    int dy = abs(y0 - y1);

    if (dx < dy){
        int dirX = x0 < x1 ? 1 : -1;
        int curY = x0;
        int i, error = 0;
        if (y1 > y0){
            for (i = y0; i <= y1; ++i){
                setPixelColor(curY, i, color, image.bits(), image.width());
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        } else {
            for (i = y0; i >= y1; --i){
                setPixelColor(curY, i, color, image.bits(), image.width());
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        }
    } else {
        int dirY = y0 < y1 ? 1 : -1;
        int curY = y0;
        int i, error = 0;
        if (x1 > x0){
            for (i = x0; i <= x1; ++i){
                setPixelColor(i, curY, color, image.bits(), image.width());
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        } else {
            for (i = x0; i >= x1; --i){
                setPixelColor(i, curY, color, image.bits(), image.width());
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        }
    }
}

void BSplaneWidget::drawLines()
{
    int i;
    if (settings->bearingPoints.empty()) return;
    for (i = 0; i < settings->bearingPoints.size()-1; ++i){
        drawLine(settings->bearingPoints[i]->x(), settings->bearingPoints[i]->y(),
                 settings->bearingPoints[i+1]->x(), settings->bearingPoints[i+1]->y(),
                    lineColor);
    }
}

