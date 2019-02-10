#include "imagewidget.h"
using std::stack;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    cellColor.setRgb(100, 0, 200, 120);
    borderColor.setRgb(0, 0, 0, 255);
    backgroundColor.setRgb(255,255,255,255);
    hexagonR = 40;
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    createHexagonField(5,8);
}

void ImageWidget::drawHexagon(GeomHexagon* h)
{
    int i;
    if (h->vert.size() != 6){
        cout << "ERR" << endl;
        return;
    }
    for (i = 0; i < 6; ++i){
        if (i != 5){
            drawLine(h->x0 + h->vert[i].first,
                     h->y0 + h->vert[i].second,
                     h->x0 + h->vert[i+1].first,
                    h->y0 + h->vert[i+1].second,
                    borderColor);
        } else {
            drawLine(h->x0 + h->vert[i].first,
                     h->y0 + h->vert[i].second,
                     h->x0 + h->vert[0].first,
                    h->y0 + h->vert[0].second,
                    borderColor);
        }
    }
}


//        int globalX0 = static_cast<int>(x0 + bufX);
//        int globalY0 = static_cast<int>(y0 + bufY);
//        int globalX1 = static_cast<int>(x0 + x);
//        int globalY1 = static_cast<int>(y0 + y);
//        drawLine(globalX0, globalY0, globalX1, globalY1);


void ImageWidget::setHexagonColored(int mx, int my)
{
    bool draw;
    int i, j, next_index;
    for (j = 0; j < hexagons.size(); ++j){
        draw = true;

        double cx = mx - hexagons[j].x0;
        double cy = my - hexagons[j].y0;

        //cout << "--------------------------------" << endl << "cx ( " << cx << " ; " << cy << " )" << endl;
        //check hexagons

        for (i = 0; i < 6; ++i){
            if (i != 5){
                next_index = i+1;
            } else {
                next_index = 0;
            }
            double bx = round(hexagons[j].vert[i].first + hexagons[j].vert[next_index].first)/2.0;
            double by = round(hexagons[j].vert[i].second + hexagons[j].vert[next_index].second)/2.0;

            //proection
            double scalar = (cx*bx + cy*by) / (bx*bx + by*by);
            //cout << "scalar = " << scalar << endl;
            if (abs(scalar) >= 1) { // -1
                draw = false;
                break;
            }
        }

        if (draw){
            hexagons[j].colored = true;
            //cout << hexagons[j].x0 << " " << hexagons[j].y0 << " --------------------------------------->>>>>>>>" << hexagons[j].colored << endl;
        }
    }
}

void ImageWidget::createHexagonVertices(GeomHexagon* h)
{
    int i;
    double x, y;
    for (i = 0; i < 6; ++i){
        x = round(hexagonR * cos(PI * i/3 + PI/6));
        y = round(hexagonR * sin(PI * i/3 + PI/6));
        h->vert.push_back(pair<int,int> (x, y));
    }
}

void ImageWidget::pushSurround(int leftX, int yLevel, stack<ImageWidget::Span>, QColor last, QColor newColor)
{

}

//Fill game coordinates here Map?
void ImageWidget::fillArea(int x0, int y0, QColor lastColor, QColor newColor)
{
    int seedY, i;
    stack<Span> stack;

    Span curSpan, sp;
    Span firstSpan = getSpan(x0, y0, lastColor);
    stack.push(firstSpan);

    while (!stack.empty()){
        curSpan = stack.top();
        stack.pop();
        seedY = curSpan.y;
        int Left = curSpan.left;
        //cout << "====================================> Y = " << curSpan.y << endl;

        int Right = curSpan.right;
        //cout << "left = " << Left << endl;

        //cout << "right = " << Right << endl;

        drawLine(curSpan.left, seedY, curSpan.right, seedY, newColor);

        for (i = curSpan.left; i <= curSpan.right; ++i){
            if (image->pixelColor(i, seedY+1) == lastColor){
                //cout << "FOUNDED SPAN START " << i << " ; " << seedY+1 << endl;
                sp = getSpan(i, seedY+1, lastColor);
                stack.push(sp);
                i = sp.right;
            }

        }
        for (i = curSpan.left; i <= curSpan.right; ++i){
            if (seedY > 0){
                if (image->pixelColor(i, seedY-1) == lastColor){
                    //cout << "FOUNDED SPAN START " << i << " ; " << seedY-1 << endl;
                    sp = getSpan(i, seedY-1, lastColor);
                    stack.push(sp);
                    i = sp.right;
                }
            }
        }
    }
}

void ImageWidget::drawField()
{        
    for (auto h : hexagons){
        drawHexagon(&h);
        if (h.colored){
            fillArea(h.x0, h.y0, backgroundColor, cellColor);
        }
    }
}

void ImageWidget::createHexagonField(int m, int n)
{
    int curX = static_cast<int>(round(sqrt(3)/2*hexagonR));
    int r = curX;
    int stepX = 2*r;
    int startX = curX;
    int curY = hexagonR;
    int i, j, lim = m;
    for (i = 0; i < n; ++i){
        curX = startX + r * (i % 2);
        lim = m - i % 2;
        for (j = 0; j < lim; ++j){
            GeomHexagon hexagon(curX, curY);
            createHexagonVertices(&hexagon);
            hexagons.push_back(hexagon);
            curX += stepX;
        }
        curY += 1.5 * hexagonR;
    }
}

void ImageWidget::drawLine(int x0, int y0, int x1, int y1, QColor color)
{
    int dx = abs(x0 - x1);
    int dy = abs(y0 - y1);

    if (dx < dy){
        int dirX = x0 < x1 ? 1 : -1;
        int curY = x0;
        int i, error = 0;
        if (y1 > y0){
            for (i = y0; i <= y1; ++i){
                image->setPixelColor(curY, i, color);
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        } else {
            for (i = y0; i >= y1; --i){
                image->setPixelColor(curY, i, color);
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        }
    } else {
        int dirY = y0 < y1 ? 1 : -1;
        int curY = y0;
        int i, error = 0;
        if (x1 > x0){
            for (i = x0; i <= x1; ++i){
                image->setPixelColor(i, curY, color);
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        } else {
            for (i = x0; i >= x1; --i){
                image->setPixelColor(i, curY, color);
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        }
    }
}

ImageWidget::Span ImageWidget::getSpan(int x0, int y0, QColor lastColor)
{
    int x = x0;
    int y = y0;
    Span span;
    span.y = y0;

    while (x >= 0 && image->pixelColor(x, y) == lastColor) {
        x++;
    }
    span.right = x-1;
    x = x0;

    while (x >= 0 && image->pixelColor(x, y) == lastColor) {
        x--;
    }
    span.left = x+1;
    return span;
}

void ImageWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    int i, j;
    image = new QImage(width(), height(), QImage::Format_ARGB32);

    for (i = 0; i < width(); ++i){
        for (j = 0; j < height(); ++j){
            image->setPixelColor(i, j, backgroundColor);
        }
    }

    drawField();
    p.drawImage(0, 0, *image);

    //dx > dy
    /*  drawLine(200, 100, 300, 70, borderColor); //up right
        drawLine(200, 100, 100, 70, borderColor); //up leftt
        drawLine(200, 100, 300, 130, borderColor); //down right
        drawLine(200, 100, 100, 130, borderColor); //down left
        //dx < dy
        drawLine(200, 100, 220, 30, borderColor); //up right
        drawLine(200, 100, 180, 30, borderColor); //up leftt
        drawLine(200, 100, 220, 170, borderColor); //down right
        drawLine(200, 100, 180, 170, borderColor); //down left
        // dx = 0 || dy = 0
        drawLine(200, 100, 200, 50, borderColor); //up
        drawLine(200, 100, 200, 150, borderColor); //down
        drawLine(200, 100, 250, 100, borderColor); //right
        drawLine(200, 100, 150, 100, borderColor); //down
        fillArea(10, 10, backgroundColor, cellColor);
*/
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    //mouse position
    int mx = event->x();
    int my = event->y();
    setHexagonColored(mx ,my);
    repaint();
}



