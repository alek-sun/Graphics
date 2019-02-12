#include "cell.h"

Cell::Cell(int x0, int y0, int x, int y)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x = x;
    this->y = y;
    isAlive = false;
    lastColor = QColor(255, 255, 255, 255);
    impact = 0.0;
    state = DIE;
}

Cell::Cell(const Cell &c)
{
    x0 = c.x0;
    y0 = c.y0;
    x = c.x;
    y = c.y;
    lastColor = c.lastColor;
    vert = c.vert;
    isAlive = c.isAlive;
    state = c.state;
    impact = c.impact;
}

void Cell::setState(double liveBegin, double liveEnd, double birthBegin, double birthEnd)
{
    if (impact >= birthBegin && impact <= birthEnd){
        if (isAlive){
            state = RECENTLY_BIRTH;
            return;
        } else {
            state = RECENTLY_DIE;
            return;
        }
    }
    if ((impact >= liveBegin && impact < birthBegin) ||
            (impact > birthEnd && impact <= liveEnd)){
        if (isAlive){
            state = LONG_BIRTH;
            return;
        } else {
            state = LONG_DIE;
            return;
        }
    }
    state = DIE;
}

//bool Cell::isDie()
//{
//    return state == Cell::DIE
//        || state == Cell::LONG_DIE
//        || state == Cell::RECENTLY_DIE;
//}





