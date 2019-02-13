#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
#include <iostream>
#include "cell.h"

class GameLogic
{
public:
    GameLogic(int m, int n);
    int m;
    int n;
    int k;
    int mode;

    double liveBegin;
    double liveEnd;
    double birthBegin;
    double birthEnd;
    double firstImpact;
    double secondImpact;

    static const int XOR_MODE = 1;
    static const int REPLACE_MODE = 0;

    vector<Cell> curState;

    void step();
    void clear();
    void changeColors();
    void calculateImpacts();

private:
    double findCellImpact(int x, int y);
    void renewImpact(Cell* cell);
};

#endif // GAMELOGIC_H
