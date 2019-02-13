#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <stack>
#include <vector>
#include <iostream>
#include <QTime>
#include <QDebug>

#include "cell.h"
#include "gamelogic.h"

using std::vector;
using std::stack;
using std::pair;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    void drawField();   
    GameLogic *getGameLogic() const;
    void setGameLogic(GameLogic *value);
    void drawText(QString text, int x, int y, int height, QColor color);

    bool displayImpact;


    void fillCell(Cell *cell);
    Cell *setHexagonColored(int mx, int my);
private:
    typedef struct {
        int left, right, y;
    } Span;

    QColor borderColor;
    QColor recentlyBirthColor;
    QColor recentlyDieColor;
    QColor longBirthColor;
    QColor longDieColor;
    QColor backgroundColor;
    QColor defaultWidgetColor = QColor(205,205,205,205);

    int h;
    int w;

    QImage* image;
    uchar* bits;
    GameLogic* gameLogic;
    bool mousePressed = false;

    double PI = 3.141592;

    void drawLine(int x0, int y0, int x1, int y1, QColor lineColor);
    Span getSpan(int x0, int y0, QColor lastColor);
    void createHexagonField(int m, int n);    
    void createHexagonVertices(Cell *h);
    void pushSurround(int leftX, int yLevel, stack<Span>, QColor last, QColor newColor);
    void drawHexagonLines(Cell* hexagon);
    void fillArea(int x0, int y0, QColor lastColor, QColor c);

    void setPixelColor(int x, int y, QColor color);
    QColor pixelColor(int x, int y);
    //Cell &setHexagonColored(int mx, int my);
signals:
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public slots:
};

#endif // IMAGEWIDGET_H
