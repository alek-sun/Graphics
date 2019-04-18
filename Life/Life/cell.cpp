#include "cell.h"

Cell::Cell(int x0, int y0, int x, int y)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x = x;
    this->y = y;
    isAlive = false;
    lastColor = QColor(205, 205, 205, 205);
    impact = 0.0;
    state = -1;
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

double Cell::getImpact() const
{
    return impact;
}

void Cell::setImpact(double value)
{
    impact = value;
}

int Cell::getState() const
{
    return state;
}

bool Cell::getIsAlive() const
{
    return isAlive;
}

void Cell::setIsAlive(bool value)
{
    isAlive = value;
}

void Cell::setState(double liveBegin, double liveEnd, double birthBegin, double birthEnd)
{
    if (impact >= birthBegin && impact <= birthEnd){
        if (isAlive){
            state = RECENTLY_BIRTH;
        } else {
            state = RECENTLY_DIE;

        }
    } else if ((impact >= liveBegin && impact < birthBegin) ||
            (impact > birthEnd && impact <= liveEnd)){
        if (isAlive){
            state = LONG_BIRTH;

        } else {
            state = LONG_DIE;
        }
    } else {
        state = DIE;
    }
}

void Cell::setState(int state)
{
     this->state = state;
}

//bool Cell::isDie()
//{
//    return state == Cell::DIE
//        || state == Cell::LONG_DIE
//        || state == Cell::RECENTLY_DIE;
//}





