#include "orderdithereffect.h"

using std::vector;

OrderDitherEffect::OrderDitherEffect()
{

}

void OrderDitherEffect::run(QImage image, QImage *outImage)
{
    int n = 8;
    int count = n / 2;
    int i, j;
    int h = image.height();
    int w = image.width();
    vector<int> buf = {0, 2, 3, 1};
    vector<int> d;

    for (i = 0; i < log2(count); ++i){
        d = nextMatrix(buf);
        buf.clear();
        for (j = 0; j < d.size(); j++){
             buf.push_back(d[j]);
        }
    }

    QColor color;
    int k, l, r, g, b, ind;

    for (i = 0; i < h; ++i){
        for (j = 0; j < w; ++j){
            color = image.pixelColor(j,i);
            k = j % n;
            l = i % n;
            ind = n*l+k;

            r = color.red();
            g = color.green();
            b = color.blue();

            r &= 0xE0;
            g &= 0xE0;
            b &= 0xC0;

            r += d[ind];
            g += d[ind];
            b += d[ind];

            setPixelColor(j, i, QColor(clampRGB(r),clampRGB(g),clampRGB(b)), outImage->bits(), w);
        }
    }
}

vector<int> OrderDitherEffect::nextMatrix(vector<int> m)
{
    int n = sqrt(m.size());

    vector<int> d;

    int i, j, cur;

    for (i = 0; i < 2*n; ++i){
        for (j = 0; j < 2*n; ++j){
            int k = i*n+j;

            if ( i < n && j < n ){
                cur = 4*m[k];
            } else if (j >= n && i < n){
                cur = 4*m[i*n + j-n] + 2;
            } else if (j < n && i >= n) {
                cur = 4*m[(i-n)*n + j] + 3;
            } else if (i >= n && j >= n){
                cur = 4*m[(i-n)*n + j-n] + 1;
            }
            d.push_back(cur);
        }
    }
    return d;
}
