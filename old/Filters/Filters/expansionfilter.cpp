#include "expansionfilter.h"

ExpansionFilter::ExpansionFilter(int index)
{
    this->index=index;
    matrix = {
        0,0,1,0,0,
        0,1,1,1,0,
        1,1,1,1,1,
        0,1,1,1,0,
        0,0,1,0,0
    };
}

void ExpansionFilter::run(QImage image, QImage *outImage)
{
    int h = image.height();
    w = image.width();

    bits = image.bits();
    bufBits = outImage->bits();

    vector <int> red_v;
    vector <int> green_v;
    vector <int> blue_v;

    int x, y, u, v, ix, iy, bi, ind;

    for (y = 0; y < h; ++y){
        for (x = 0; x < w; ++x){
            for (u = -2; u <= 2; ++u){
                for (v = -2; v <= 2; ++v){
                    ind = (u+2)*5+(v+2);
                    if (matrix[ind] == 0) continue;
                    if (x + v < 0){
                        ix = 0;
                    } else if (x + v >= w){
                        ix = w-1;
                    } else {
                        ix = x + v;
                    }

                    if (y + u < 0){
                        iy = 0;
                    } else if (y + u >= h){
                        iy = h-1;
                    } else {
                        iy = y + u;
                    }
                    bi = 4*(ix + iy*w);
                    red_v.push_back(bits[bi + 2]);
                    green_v.push_back(bits[bi + 1]);
                    blue_v.push_back(bits[bi]);
                }
            }
            sort(red_v.begin(), red_v.end());
            sort(green_v.begin(), green_v.end());
            sort(blue_v.begin(), blue_v.end());
            setPixelColor(x,y,QColor(red_v[index], green_v[index], blue_v[index]), bufBits, w);
            red_v.clear();
            green_v.clear();
            blue_v.clear();
        }
    }
}
