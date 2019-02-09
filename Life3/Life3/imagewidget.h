#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <stack>
#include <vector>
#include <iostream>
#include "geomhexagon.h"

using std::vector;
using std::pair;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    void fillHexagon(int x0, int y0, QColor lastColor, QColor c);
    void drawField();
    void drawHexagon(GeomHexagon* hexagon);

private:
    typedef struct {
        int left, right, y;
    } Span;

    QColor borderColor;
    QColor cellColor;
    QColor backgroundColor;
    QPainter* painter;

    QImage* image;

    int hexagonR;
    int m, n;
    double PI = 3.141592;
    vector<GeomHexagon> hexagons;

    void drawLine(int x0, int y0, int x1, int y1, QColor lineColor);
    Span getSpan(int x0, int y0, QColor lastColor);
    void createHexagonField(int m, int n);
    void setHexagonColored(int mx, int my);
    void createHexagonVertices(GeomHexagon *h);
signals:
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent * event);
public slots:
};

#endif // IMAGEWIDGET_H
