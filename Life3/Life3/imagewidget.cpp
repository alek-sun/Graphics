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
    hexagonR = 50;
    m = 3;
    n = 4;
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    createHexagonField(m,n);
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

/*
void ImageWidget::drawHexagon(GeomHexagon* h)
{
    int i;
    double x, y, bufX, bufY;
    bufX = round(hexagonR * cos(PI/6));
    bufY = round(hexagonR * sin(PI/6));
    bool empty = h->vert.empty();

    for (i = 1; i <= 6; ++i){
        x = round(hexagonR * cos(PI * i/3 + PI/6));
        y = round(hexagonR * sin(PI * i/3 + PI/6));
        if (empty){
            h->vert.push_back(pair<int,int> (x, y));
        }
//        int globalX0 = static_cast<int>(x0 + bufX);
//        int globalY0 = static_cast<int>(y0 + bufY);
//        int globalX1 = static_cast<int>(x0 + x);
//        int globalY1 = static_cast<int>(y0 + y);
//        drawLine(globalX0, globalY0, globalX1, globalY1);
        drawLine(h->x0 + bufX, h->y0 + bufY, h->x0 + x, h->y0 + y, borderColor);
        bufX = x;
        bufY = y;
    }
}
        */

void ImageWidget::setHexagonColored(int mx, int my)
{
    bool draw;
    int i, j, next_index;
    for (j = 0; j < hexagons.size(); ++j){
        draw = true;

        double cx = mx - hexagons[j].x0;
        double cy = my - hexagons[j].y0;

        cout << "--------------------------------" << endl << "cx ( " << cx << " ; " << cy << " )" << endl;

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
            cout << "scalar = " << scalar << endl;

            if (abs(scalar) > 1) { // -1
                draw = false;
                break;
            }
        }

        if (draw){
            hexagons[j].colored = true;
            cout << hexagons[j].x0 << " " << hexagons[j].y0 << " --------------------------------------->>>>>>>>" << hexagons[j].colored << endl;
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

//Fill game coordinates here Map?
void ImageWidget::fillHexagon(int x0, int y0, QColor lastColor, QColor newColor)
{
    Span firstSpan = getSpan(x0, y0, lastColor);

    int lastLeft = firstSpan.left;
    cout << "left = " << lastLeft << endl;

    int lastRight = firstSpan.right;
    cout << "right = " << lastRight << endl;

    drawLine(lastLeft, y0, lastRight, y0, newColor);
    //Span sp = getSpan(lastLeft.)
}

void ImageWidget::drawField()
{
    for (auto h : hexagons){
        drawHexagon(&h);
        cout << h.x0 << " " << h.y0 << " ===================>>>>>>>>" << h.colored << endl;
        if (h.colored){
            fillHexagon(h.x0, h.y0, backgroundColor, cellColor);
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
            for (i = y0; i < y1; ++i){
                image->setPixelColor(curY, i, color);
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        } else {
            for (i = y0; i > y1; --i){
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
            for (i = x0; i < x1; ++i){
                image->setPixelColor(i, curY, color);
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        } else {
            for (i = x0; i > x1; --i){
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
    cout << lastColor.red() << " " << lastColor.green() << " " << lastColor.blue() << " || ";
    cout << image->pixelColor(x, y).red() << " " << image->pixelColor(x, y).green() << " " << image->pixelColor(x, y).blue() << " || ";
    while (image->pixelColor(x, y) == lastColor) {
        x++;
    }
    span.right = x;
    x = x0-1;
    cout << endl;
    while (image->pixelColor(x, y) == lastColor) {
        x--;
        cout <<".";
    }
    cout << endl;
    span.left = x;
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
    /*uchar *bits = im.bits();
    for (i = 0; i < w; i++){
        for (j = 0; j < h; j++){
            //for(k = 0; k < 4; k++){
                //bits[k + i*4 + j*w*4] = 200;
            //}
        }
    }
    */
    //dx > dy
    /*drawLine(200, 100, 300, 70); //up right
    drawLine(200, 100, 100, 70); //up leftt
    drawLine(200, 100, 300, 130); //down right
    drawLine(200, 100, 100, 130); //down left
    //dx < dy
    drawLine(200, 100, 220, 30); //up right
    drawLine(200, 100, 180, 30); //up leftt
    drawLine(200, 100, 220, 170); //down right
    drawLine(200, 100, 180, 170); //down left
    // dx = 0 || dy = 0
    drawLine(200, 100, 200, 50); //up
    drawLine(200, 100, 200, 150); //down
    drawLine(200, 100, 250, 100); //right
    drawLine(200, 100, 150, 100); //down
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



