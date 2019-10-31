#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include <QWidget>
#include "isolinewidget.h"
#include <vector>

using std::vector;

class LegendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LegendWidget(QWidget *parent = nullptr);

    QImage image;
    Settings* settings;
    void redrawLegend();
    void setSettings(Settings *value);
    bool interpolation;

private:
    void fillInterpolationRect(int x, int y, int w, int h, QColor c1, QColor c2);
    double shift, y;
signals:

public slots:
    void paintEvent(QPaintEvent *event);
};

#endif // LEGENDWIDGET_H
