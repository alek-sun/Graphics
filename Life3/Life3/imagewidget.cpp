#include "imagewidget.h"

using std::stack;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    recentlyBirthColor.setRgb(100, 0, 200, 250);
    recentlyDieColor.setRgb(200, 0, 50, 250);
    longBirthColor.setRgb(100, 0, 200, 100);
    longDieColor.setRgb(200, 0, 50, 100);
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
    gameLogic->changeColors();

    //w = gameLogic->m*round(sqrt(3)/2*gameLogic->k);
    //h = 2*gameLogic->n*gameLogic->k;
}

void ImageWidget::drawText(QString text, int x, int y, int height, QColor color)
{
    QPainter painter;
    painter.begin(image);
    painter.setPen(color);
    painter.setFont(QFont("Times", height, QFont::Bold));
    painter.drawText(x-text.size()*height + 2, y-height, text.size()*2*height, height*2, Qt::AlignCenter | Qt::AlignHCenter, text);
}

void ImageWidget::fillCell(Cell* cell)
{
    switch (cell->getState()){
        case Cell::RECENTLY_BIRTH :
            fillArea(cell->x0, cell->y0, cell->lastColor, recentlyBirthColor);
            cell->lastColor = recentlyBirthColor;
            break;
        case Cell::LONG_BIRTH :
            fillArea(cell->x0, cell->y0, cell->lastColor, longBirthColor);
            cell->lastColor = longBirthColor;
            break;
        case Cell::LONG_DIE :
            fillArea(cell->x0, cell->y0, cell->lastColor, longDieColor);
            cell->lastColor = longDieColor;
            break;
        case Cell::RECENTLY_DIE :
            fillArea(cell->x0, cell->y0, cell->lastColor, recentlyDieColor);
            cell->lastColor = recentlyDieColor;
            break;
        case Cell::DIE :
            fillArea(cell->x0, cell->y0, cell->lastColor, backgroundColor);
            cell->lastColor = backgroundColor;
            break;
        default:
            fillArea(cell->x0, cell->y0, defaultWidgetColor, backgroundColor);
            cell->lastColor = backgroundColor;
        }
    if (displayImpact){
        //drawText(QString::number(cell->x), cell->x0 - gameLogic->k/2, cell->y0, gameLogic->k/3, borderColor);
        //drawText(QString::number(cell->y), cell->x0 + gameLogic->k/2, cell->y0, gameLogic->k/3, borderColor);
        drawText(QString::number(cell->getImpact()), cell->x0, cell->y0, gameLogic->k/2, borderColor);
    }
}

//        int globalX0 = static_cast<int>(x0 + bufX);
//        int globalY0 = static_cast<int>(y0 + bufY);
//        int globalX1 = static_cast<int>(x0 + x);
//        int globalY1 = static_cast<int>(y0 + y);
//        drawLine(globalX0, globalY0, globalX1, globalY1);


Cell *ImageWidget::setHexagonColored(int mx, int my)
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

        if (draw){
            if (gameLogic->mode == GameLogic::XOR_MODE){
                if (gameLogic->curState[j].getIsAlive()){
                    gameLogic->curState[j].setIsAlive(false);
                    gameLogic->calculateImpacts();
                    gameLogic->curState[j].setState(Cell::DIE);
                    return &gameLogic->curState[j];
                }
            }
            gameLogic->curState[j].setIsAlive(true);
            gameLogic->calculateImpacts();
            gameLogic->curState[j].setState(Cell::RECENTLY_BIRTH);
            return &gameLogic->curState[j];
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

            if (pixelColor(i, seedY+1) == lastColor){
                sp = getSpan(i, seedY+1, lastColor);                
                stack.push(sp);
                i = sp.right;
            }

        }
        for (i = curSpan.left; i <= curSpan.right; ++i){

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
    for (auto cell : gameLogic->curState){
        drawHexagonLines(&cell);
        fillCell(&cell);
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
            Cell hexagon(curX, curY, i, j);
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
    image = new QImage(width(), height(), QImage::Format_ARGB32);
    //resize(static_cast<int>(gameLogic->m*round(sqrt(3)/2*gameLogic->k)), 2*gameLogic->n*gameLogic->k);
    bits = image->bits();



    QTime t = QTime::currentTime();

    drawField();

    qDebug() << -QTime::currentTime().msecsTo(t);

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

    mousePressed = true;
    int mx = event->x();
    int my = event->y();
    setHexagonColored(mx ,my);
    repaint();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mousePressed) return;
    int mx = event->x();
    int my = event->y();
    setHexagonColored(mx ,my);
    repaint();
}



