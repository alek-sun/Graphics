#ifndef AWIDGET_H
#define AWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include "imageresizer.h"

class AWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AWidget(QWidget *parent = nullptr);

    QImage origImage;
    QImage paintImage;

    bool mousePressed = false;
    bool selectOn = false;

    void drawRect();
    void clearRect();

    int getRectX1() const;
    void setRectX1(int value);

    int getRectY1() const;
    void setRectY1(int value);

    int getRectX2() const;
    void setRectX2(int value);

    int getRectY2() const;
    void setRectY2(int value);

    void centerSquare(int x1, int x2, int y1, int y2);

    void setImage(const QImage &value);
    void setSizeX(int value);
    void setSizeY(int value);

    void setK(double value);


private:
    int rectX1;
    int rectY1;
    int rectX2;
    int rectY2;
    double k;
    uchar* bits;

    int lastX, lastY;
    int sizeX, sizeY;

    void findRectCoords();
    void setPixelColor(int x, int y, QColor color);
    QColor pixelColor(int x, int y);


Q_SIGNALS:
    void selected(int,int,int,int);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public slots:
};

#endif // AWIDGET_H
