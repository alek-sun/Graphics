#include "wireframewidget.h"
#include <QtMath>


WireframeWidget::WireframeWidget(QWidget *parent) : QWidget(parent)
{    
    angleX = 30;
    angleY = 0;
    angleZ = 0;
    d = 1625;
    w = 700;
    h = 600;
    image = QImage(w, h, QImage::Format_ARGB32);
    image.fill(Qt::black);

    lastMouseX = -1;
    lastMouseY = -1;
    isAngleZ = false;
    moving = false;
    setFocusPolicy(Qt::StrongFocus);
}

void WireframeWidget::drawWireframe()
{
    if (s->allPoints.empty()) return;
    //d = abs(s->allPoints[s->allPoints.size()-1]->x() - s->allPoints[0]->x())*s->z/0.4;
    //qDebug() << "d = " << d;
    mulMatrix();
    QPainter* painter = new QPainter(&image);
    painter->setPen(s->bodyColor);
    drawSplines(painter);
    drawCircles(painter);
    delete painter;
}

void WireframeWidget::drawSplines(QPainter* painter)
{
    if (s->allPoints.empty()) return;
    double stepAngle = 360.0/s->splaneN, a = 0;
    int i, k;

    for (i = 0; i <= s->splaneN; ++i, a+=stepAngle){
        if (i % s->hidingAngle != 0) continue;
        k = 0;

        QVector4D last;
        for (auto p : s->allPoints){
            QVector4D v(p->y()*cos(qDegreesToRadians(a)), p->y()*sin(qDegreesToRadians(a)), p->x(), 1);

            v = (s->matrix)*v;

            if (k > 0){                
                painter->drawLine(last.x(), last.y(), v.x(), v.y());
            }
            last.setX(v.x());
            last.setY(v.y());
            k++;
        }
    }
}

void WireframeWidget::drawCircles(QPainter* painter)
{
    int i, index = -1;
    double a, stepAngle = 360.0/s->angleN;

    for (auto p : s->allPoints){
        index++;
        if (index % s->hidingSplane != 0) continue;

        QVector4D last;
        for (i = 0, a = 0; i <= s->angleN; i++, a+=stepAngle){
            QVector4D v(p->y()*cos(qDegreesToRadians(a)), p->y()*sin(qDegreesToRadians(a)), p->x(), 1);
            v = (s->matrix)*v;

            if (i > 0){
                painter->drawLine(last.x(), last.y(), v.x(), v.y());
            }
            last.setX(v.x());
            last.setY(v.y());
        }
    }
}

void WireframeWidget::mulMatrix()
{
    QMatrix4x4 rotateM;

    rotateM.translate(w/2, h/2);

    rotateM.scale(1/s->z, 1/s->z);

    rotateM.rotate(angleX, QVector3D(1,0,0));
    rotateM.rotate(angleY, QVector3D(0,1,0));
    rotateM.rotate(angleZ, QVector3D(0,0,1));

    s->matrix = rotateM;
}

void WireframeWidget::paintEvent(QPaintEvent *event)
{
    drawWireframe();
    QPainter p(this);
    p.drawImage(0,0,image);
    image = QImage(w, h, QImage::Format_ARGB32);
    image.fill(QColor(s->backgroudColor));
}

void WireframeWidget::wheelEvent(QWheelEvent *e)
{
    int numDegrees = e->delta()/8;
    s->z += numDegrees*0.003;
    s->z = s->z < 0 ? s->z = 0.001 : s->z;
    repaint();
}

void WireframeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    lastMouseX = -1;
    lastMouseY = -1;
    moving = false;
}

void WireframeWidget::mouseMoveEvent(QMouseEvent *event)
{
    moving = true;
    if (lastMouseX != -1 && lastMouseY != -1){
        angleX += 0.5*(event->y()-lastMouseY);
        if (isAngleZ){
            angleZ -= 0.5*(event->x()-lastMouseX);
        } else {
            angleY -= 0.5*(event->x()-lastMouseX);
        }
    }
    lastMouseX = event->x();
    lastMouseY = event->y();
    angleChanged(angleX, angleY, angleZ);
    repaint();
}

void WireframeWidget::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Alt){
        isAngleZ = true;
    }    
}

void WireframeWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt){
        isAngleZ = false;
    }
}




//rotateM.perspective(30, 1, 0.001f, 300);
//rotateM.scale(1, 1, 0.001f);

//rotateM.translate(0, 0, -s->z*100);
//qDebug() << rotateM;
