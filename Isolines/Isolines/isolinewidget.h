#ifndef ISOLINEWIDGET_H
#define ISOLINEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <math.h>
#include <QDebug>
#include "fcalculator.h"
#include "settings.h"

using std::vector;
using std::pair;

class IsolineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IsolineWidget(QWidget *parent = nullptr);

    typedef struct {
        bool gridShow;
        bool interactive;
        bool interpolation;
        bool showIsolines;
        bool showIntersections;
    } Mods;

    typedef struct {
        double f;
        double x;
        double y;
    } Position;

    Settings* settings;
    Mods* mods;
    Position* curPosition;
    QImage image;
    QImage bufImage;
    FCalculator* fx;

    bool mousePressed = false;
    bool moving = false;


    void drawGrid();
    void drawColoredMap(bool needInterpolate);
    QColor pixelColor(int x, int y, uchar *bits, int w);
    static void setPixelColor(int x, int y, QColor color, uchar *bits, int w);
    void setFx(FCalculator *value);
    void interpolate(double vx_pix, double vy_pix, double *x, double *y);
    void drawLine(int x0, int y0, int x1, int y1, QColor color);

private:
    vector<pair<int,int>> points;    

    double intersectionPoint(double f1, double f2, double z, int d);
    void addIntersection(vector<pair<double, double> > *intersections, double f1, double f2, int sgnx, int sgny, double x, double y, double dx, double dy, double lvl);
    int clampW(int v);
    int clampH(int v);
    void drawIsolines(vector<double> isolineLevels);
    void drawIntersections();

public slots:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
Q_SIGNALS:
    void mouseMoved(Position*);

};

#endif // ISOLINEWIDGET_H
