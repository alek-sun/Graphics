#include "gamelogic.h"

using std::cin;
using std::cout;
using std::endl;

GameLogic::GameLogic(int m, int n)
{
    this->m = m;
    this->n = n;
    this -> k = 20;
    this->liveBegin = 2.0;
    this->liveEnd = 3.3;
    this->birthBegin = 2.3;
    this->birthEnd = 2.9;
    this -> firstImpact = 1.0;
    this->secondImpact = 3.0;
}

void GameLogic::step()
{
    int x, y;

    vector<Cell> newState;
    for (int i = 0; i < curState.size(); ++i){

        Cell c (curState[i]);
        renewImpact(&c);

       cout << "imp = " << c.impact << endl;

        if (!c.isAlive && c.impact >= birthBegin && c.impact <= birthEnd){
            c.isAlive = true;
        } else if (c.isAlive && c.impact >= liveBegin && c.impact <= liveEnd){
                //hmmm..
        } else if (c.impact < liveBegin || c.impact > liveEnd) {
            c.isAlive = false;
        }
        c.setState(liveBegin, liveEnd, birthBegin, birthEnd);
        newState.push_back(c);
    }
    curState = newState;
}

void GameLogic::run()
{

}

void GameLogic::stop()
{

}

void GameLogic::clear()
{

}

void GameLogic::calculateAllImpact()
{
    vector<Cell> newState;
    for (auto cell : curState){
        renewImpact(&cell);     // uses curState
        newState.push_back(cell);
    }
    curState = newState;
}

double GameLogic::findCellImpact(int x, int y)
{
    for (auto cell : curState){
        if (cell.x == x && cell.y == y){
            //cout << x << " " << y << " " << cell.state << endl;
            if (cell.isAlive){
                return 1.0;
            } else {
                return 0.0;
            }
        }
    }
    return 0.0;
}

void GameLogic::renewImpact(Cell *cell)
{
    double newFirstImpact = 0.0, newSecondImpact = 0.0;

    newFirstImpact += findCellImpact(cell->x+1, cell->y);
    newFirstImpact += findCellImpact(cell->x-1, cell->y);
    newFirstImpact += findCellImpact(cell->x, cell->y-1);
    newFirstImpact += findCellImpact(cell->x-1, cell->y-1);
    newFirstImpact += findCellImpact(cell->x, cell->y+1);
    newFirstImpact += findCellImpact(cell->x-1, cell->y+1);
    newFirstImpact*=firstImpact;

   //cout << "first imp = " << newFirstImpact << endl;

    newSecondImpact += findCellImpact(cell->x+1, cell->y-1);
    newSecondImpact += findCellImpact(cell->x, cell->y-2);
    newSecondImpact += findCellImpact(cell->x-2, cell->y-1);
    newSecondImpact += findCellImpact(cell->x-2, cell->y+1);
    newSecondImpact += findCellImpact(cell->x, cell->y+2);
    newSecondImpact += findCellImpact(cell->x+1, cell->y+1);
    newSecondImpact*=secondImpact;

   //cout << "second imp = " << newSecondImpact << endl;

    cell->impact = newFirstImpact+newSecondImpact;
}
