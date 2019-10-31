#ifndef BWIDGET_H
#define BWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPainter>

class BWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BWidget(QWidget *parent = nullptr);

    QImage image;

    int sizeX = 0;
    int sizeY = 0;

private:


signals:

public slots:
    void paintEvent(QPaintEvent* event);
};

#endif // BWIDGET_H
