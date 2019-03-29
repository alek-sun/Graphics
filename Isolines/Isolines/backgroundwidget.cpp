#include "backgroundwidget.h"

#include <QPainter>
#include <QDebug>
#include <QString>


BackgroundWidget::BackgroundWidget(QWidget *parent) : QWidget(parent)
{
    background = QImage(580, 660, QImage::Format_ARGB32);
    background.fill(QColor(255,255,255,255));
    n_ab = 3;
    n_cd = 3;

    abX = 40;
    w = 530;
    abY = 92;

    cdX = 10;
    cdY = 110;
    h = 600;
}

void BackgroundWidget::setSettings(Settings *value)
{
    settings = value;
}

void BackgroundWidget::redrawGrid()
{
    QPainter p(&background);

    p.setPen(QColor(0,0,0,255));

    int i;
    int textSize = 6;
    double pos_step = (w - abX) / n_ab;
    double pos = abX, val = settings->a;
    double value_step = (settings->b - settings->a) / n_ab;
    QString str;
    int maxSize = QString::number(settings->b, 'd', 1).size() > QString::number(settings->d, 'd', 1).size() ?
                QString::number(settings->b, 'd', 1).size() : QString::number(settings->d, 'd', 1).size();

    maxSize = maxSize > QString::number(settings->a, 'd', 1).size() ?
                maxSize : QString::number(settings->a, 'd', 1).size();
    maxSize = maxSize > QString::number(settings->c, 'd', 1).size() ?
                maxSize : QString::number(settings->c, 'd', 1).size();

    p.setFont(QFont("Helvetica", textSize*5/maxSize, QFont::Bold));
    for (i = 0; i <= n_ab ; ++i){
        p.drawText(pos, abY, QString::number(val, 'd', 1));
        str = QString::number(val, 'd', 1);
        pos += pos_step;
        val += value_step;
    }

    pos_step = (h - cdY) / n_cd;
    pos = cdY, val = settings->c;
    value_step = (settings->d - settings->c) / n_ab;


    for (i = 0; i <= n_cd ; ++i){
        p.drawText(cdX, pos, QString::number(val, 'd', 1));
        pos += pos_step;
        val += value_step;
    }
    p.drawLine(39, 99, 540, 99);
    p.drawLine(39, 600, 540, 600);
    p.drawLine(39, 100, 39, 599);
    p.drawLine(540, 100, 540, 599);
}

void BackgroundWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    redrawGrid();
    p.drawImage(0, 0, background);
    background = QImage(580, 660, QImage::Format_ARGB32);
    background.fill(QColor(255,255,255,255));
}
