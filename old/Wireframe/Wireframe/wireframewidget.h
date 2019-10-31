#ifndef WIREFRAMEWIDGET_H
#define WIREFRAMEWIDGET_H

#include "settings.h"

#include <QMatrix4x4>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <math.h>

class WireframeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WireframeWidget(QWidget *parent = nullptr);
    Settings* s;

    int angleX;
    int angleY;
    int angleZ;

private:
    QImage image;
    int w;
    int h;
    int d;

    int lastMouseX;
    int lastMouseY;
    bool moving;
    bool isAngleZ;

    void drawWireframe();
    void drawSplines(QPainter *);
    void mulMatrix();
    void drawCircles(QPainter *painter);
signals:

public slots:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *e);    
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
Q_SIGNALS:
    void angleChanged(int x, int y, int z);
};

#endif // WIREFRAMEWIDGET_H
