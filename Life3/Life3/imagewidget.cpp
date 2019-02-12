#include "imagewidget.h"

using std::stack;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    recentlyBirthColor.setRgb(100, 0, 200, 120);
    recentlyDieColor.setRgb(100, 0, 100, 100);
    longBirthColor.setRgb(200, 0, 100, 100);
    longDieColor.setRgb(100, 0, 100, 50);
    borderColor.setRgb(0, 0, 0, 255);
    backgroundColor.setRgb(255,255,255,255);
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    bits = image->bits();
}

void ImageWidget::drawHexagonLines(Cell* h)
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

GameLogic *ImageWidget::getGameLogic() const
{
    return gameLogic;
}

void ImageWidget::setGameLogic(GameLogic *value)
{
    gameLogic = value;
    createHexagonField(gameLogic->m, gameLogic->n);
    gameLogic->step();
}

void ImageWidget::drawText(QString text, int x, int y, int height, QColor color)
{
    QPainter painter;
    painter.begin(image);
    painter.setPen(color);
    painter.setFont(QFont("Times", height, QFont::Bold));
    painter.drawText(x-text.size()*height + 2, y-height, text.size()*2*height, height*2, Qt::AlignCenter | Qt::AlignHCenter, text);
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
    for (j = 0; j < gameLogic->curState.size(); ++j){
        draw = true;

        double cx = mx - gameLogic->curState[j].x0;
        double cy = my - gameLogic->curState[j].y0;

        //check gameLogic->curState

        for (i = 0; i < 6; ++i){
            if (i != 5){
                next_index = i+1;
            } else {
                next_index = 0;
            }
            double bx = round(gameLogic->curState[j].vert[i].first + gameLogic->curState[j].vert[next_index].first)/2.0;
            double by = round(gameLogic->curState[j].vert[i].second + gameLogic->curState[j].vert[next_index].second)/2.0;

            //proection
            double scalar = (cx*bx + cy*by) / (bx*bx + by*by);

            if (abs(scalar) >= 1) {
                draw = false;
                break;
            }
        }
        //TODO add renew impact
        if (draw){
            gameLogic->curState[j].isAlive = true;
            gameLogic->curState[j].state = Cell::RECENTLY_BIRTH;
            gameLogic->calculateAllImpact();
        }
    }
}

void ImageWidget::createHexagonVertices(Cell* h)
{
    int i;
    double x, y;
    for (i = 0; i < 6; ++i){
        x = round(gameLogic->k * cos(PI * i/3 + PI/6));
        y = round(gameLogic->k * sin(PI * i/3 + PI/6));
        h->vert.push_back(pair<int,int> (x, y));
    }
}


void ImageWidget::setPixelColor(int x, int y, QColor color)
{
    int i = x + y*width();
    i *= 4;
    bits[i] = color.blue();
    bits[i + 1] = color.green();
    bits[i + 2] = color.red();
    bits[i + 3] = color.alpha();
}

QColor ImageWidget::pixelColor(int x, int y)
{
    int i = x + y*width();
    i *= 4;
    return QColor(bits[i + 2], bits[i + 1], bits[i], bits[i + 3]);
}

void ImageWidget::fillArea(int x0, int y0, QColor lastColor, QColor newColor)
{
    if (newColor == lastColor){
        return;
    }
    int seedY, i;
    stack<Span> stack;
    Span curSpan, sp;
    Span firstSpan = getSpan(x0, y0, lastColor);
    stack.push(firstSpan);
    while (!stack.empty()){
        curSpan = stack.top();
        stack.pop();
        seedY = curSpan.y;

        drawLine(curSpan.left, seedY, curSpan.right, seedY, newColor);

        for (i = curSpan.left; i <= curSpan.right; ++i){
            QColor c = pixelColor(i, seedY+1);
            if (pixelColor(i, seedY+1) == lastColor){
                sp = getSpan(i, seedY+1, lastColor);                
                stack.push(sp);
                i = sp.right;
            }

        }
        for (i = curSpan.left; i <= curSpan.right; ++i){
            QColor c = pixelColor(i, seedY-1);
            if (seedY > 0){
                if (pixelColor(i, seedY-1) == lastColor){
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

    for (auto h : gameLogic->curState){

        drawHexagonLines(&h);
        switch (h.state){
            case h.RECENTLY_BIRTH :
                fillArea(h.x0, h.y0, h.lastColor, recentlyBirthColor);
                h.lastColor = recentlyBirthColor;
                break;
            case h.LONG_BIRTH :
                fillArea(h.x0, h.y0, h.lastColor, longBirthColor);
                h.lastColor = longBirthColor;
                break;
            case h.LONG_DIE :
                fillArea(h.x0, h.y0, h.lastColor, longDieColor);
                h.lastColor = longDieColor;
                break;
            case h.RECENTLY_DIE :
                fillArea(h.x0, h.y0, h.lastColor, recentlyDieColor);
                h.lastColor = recentlyDieColor;
                break;
            case h.DIE :
                fillArea(h.x0, h.y0, h.lastColor, backgroundColor);
                h.lastColor = backgroundColor;
                break;
            default:
                fillArea(h.x0, h.y0, h.lastColor, backgroundColor);
                h.lastColor = backgroundColor;
            }
        if (displayImpact){            
            //drawText(QString::number(h.x), h.x0 - gameLogic->k/2, h.y0, gameLogic->k/4, borderColor);
            // drawText(QString::number(h.y), h.x0 + gameLogic->k/2, h.y0, gameLogic->k/4, borderColor);
            drawText(QString::number(h.impact), h.x0, h.y0, gameLogic->k/2, borderColor);
        }
    }
}

void ImageWidget::createHexagonField(int m, int n)
{
    gameLogic->curState.clear();
    int curX = static_cast<int>(round(sqrt(3)/2*gameLogic->k));
    int r = curX;
    int stepX = 2*r;
    int startX = curX;
    int curY = gameLogic->k;
    int i, j, lim = m;
    for (i = 0; i < n; ++i){
        curX = startX + r * (i % 2);
        lim = m - i % 2;
        for (j = 0; j < lim; ++j){
            Cell hexagon(curX, curY, j, i);
            createHexagonVertices(&hexagon);
            gameLogic->curState.push_back(hexagon);
            curX += stepX;
        }
        curY += 1.5 * gameLogic->k;
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
                setPixelColor(curY, i, color);
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        } else {
            for (i = y0; i >= y1; --i){
                setPixelColor(curY, i, color);
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
                setPixelColor(i, curY, color);
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        } else {
            for (i = x0; i >= x1; --i){
                setPixelColor(i, curY, color);
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

    while (x >= 0 && pixelColor(x, y) == lastColor) {
        x++;
    }
    span.right = x-1;
    x = x0;

    while (x >= 0 && pixelColor(x, y) == lastColor) {
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
    //resize(static_cast<int>(gameLogic->m*round(sqrt(3)/2*gameLogic->k)), 2*gameLogic->n*gameLogic->k);
    bits = image->bits();

    QTime t = QTime::currentTime();
    for (i = 0; i < 2*gameLogic->m*round(sqrt(3)/2*gameLogic->k); ++i){
        for (j = 0; j < 1.61*gameLogic->n*gameLogic->k; ++j){
            setPixelColor(i, j, backgroundColor);
        }
    }

    drawField();

    qDebug() << QTime::currentTime().msecsTo(t);

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



