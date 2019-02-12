#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
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
    double firstImapact;
    double secondImpact;

    static const int XOR_MODE = 1;
    static const int REPLACE_MODE = 0;

    vector<Cell> curState;

    void step();
    void run();
    void stop();
    void clear();

private:

};

#endif // GAMELOGIC_H
