#ifndef GEOMHEXAGON_H
#define GEOMHEXAGON_H

#include <QColor>
#include <vector>


using std::vector;
using std::pair;

class Cell
    {
    public:
        Cell(int x0, int y0, int x, int y);
        Cell(const Cell& c);
        //center
        int x0;
        int y0;

        //vertices
        vector<pair<int,int>> vert;
        QColor lastColor;

        int x;
        int y;


        static const int DIE = 0;
        static const int RECENTLY_BIRTH = 1;
        static const int RECENTLY_DIE = 2;
        static const int LONG_BIRTH = 3;
        static const int LONG_DIE = 4;

        void setState(double liveBegin, double liveEnd, double birthBegin, double birthEnd);
        void setState(int state);

        bool getIsAlive() const;
        void setIsAlive(bool value);

        int getState() const;

        double getImpact() const;
        void setImpact(double value);

private:
        double impact;
        int state;
        bool isAlive;

};




#endif // GEOMHEXAGON_H
