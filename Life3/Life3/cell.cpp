#include "cell.h"

Cell::Cell(int x0, int y0, int x, int y)
{
    this->x0 = x0;
    this->y0 = y0;
    this->x = x;
    this->y = y;
    state = DIE;
    lastColor = QColor(255, 255, 255, 255);
}



