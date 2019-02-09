#ifndef GEOMHEXAGON_H
#define GEOMHEXAGON_H

#include <vector>

using std::vector;
using std::pair;

//namespace Life {
    class GeomHexagon
    {
    public:
        GeomHexagon(int x0, int y0);
        int x0;
        int y0;
        vector<pair<int,int>> vert;
        bool colored;
    private:

    };
//}



#endif // GEOMHEXAGON_H
