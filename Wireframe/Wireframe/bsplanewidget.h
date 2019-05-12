#ifndef BSPLANEWIDGET_H
#define BSPLANEWIDGET_H

#include "settings.h"

#include <QWidget>

class BSplaneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BSplaneWidget(QWidget *parent = nullptr);

    QImage image;
    Settings* settings;

    bool deleteMode;
    bool addPointMode;
    void setSettings(Settings *value);
    void drawSplane();
private:
    int w;
    int h;
    int movingIndex;
    bool mousePressed;
    QColor axesColor;
    QColor lineColor;
    QColor splaneColor;
    void drawAxes();
    void setPixelColor(int x, int y, QColor color, uchar *bits, int w);    
    void drawPoints();

    void deletePoint(int x, int y);
    int addPoint(double x, double y);
    void drawLine(int x0, int y0, int x1, int y1, QColor color);
    void drawPoint(int x, int y);
    void drawLines();
signals:

public slots:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
Q_SIGNALS:
    void pointCountChanged(int count);
};

#endif // BSPLANEWIDGET_H
