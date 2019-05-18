#ifndef CWIDGET_H
#define CWIDGET_H

#include "effect.h"

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <iostream>

using std::vector;

class CWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CWidget(QWidget *parent = nullptr);

    QImage image;
    QImage changedImage;
    QImage curImage;

    int sizeX = 0;
    int sizeY = 0;
    bool moving = false;

    void bwFilter();
    void negativeFilter();
    void orderedDither(int n);
    void rotation(int angle);
    void blurFilter();
    void sharpnessFilter();   
    void roberts();
    void sobel();
    void stamping();
    void errDifDither();
    void watercolor();
    void duplicate();
    void gamma();
    void erozyFilter();
    void constrictionFilter();

    typedef struct {
        int angle;
        int roberts;
        int sobel;
        double gamma;
        bool changed;
    } Settings;

    Settings* settings;


    void rotate();
private:
    uchar* bits;
    vector<int> nextMatrix(vector<int> m);
    QColor getNearestColor(QColor c, int n);

    Effect* curFilter = nullptr;
    vector<Effect> curActions;

signals:

public slots:
    void paintEvent(QPaintEvent *event);
};

#endif // CWIDGET_H
