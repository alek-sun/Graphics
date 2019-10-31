#include "fcalculator.h"



FCalculator::FCalculator(Settings* s)
{
    this->s = s;
}

double FCalculator::f(double x, double y)
{    
    return 1 / (1 + pow(x - 2.5, 4)) + 1 / (1 + pow(y - 2.5, 4)) + sin(x * y) * 0.3;
    //return 100 / (1 + pow(x - 2.5, 4)) + 100 / (1 + pow(y - 2.5, 4)) + 1000*cos(x * y) * 0.3;
}

void FCalculator::buildGrid()
{
    double stepX = (s->b - s->a) / s->k;
    double stepY = (s->d - s->c) / s->m;

    int nx, ny;
    grid.clear();

    for (ny = 0; ny <= s->m; ny++){
        for (nx = 0; nx <= s->k; nx++){
            grid.push_back(f(s->a + nx*stepX, s->c + ny*stepY));
        }
    }
}

void FCalculator::getFLimits(double *min, double *max)
{
    double i, j;
    double buf_max = -99999999999.9, buf_min = DBL_MAX, val;

    double dx = (s->b - s->a)/500;
    double dy = (s->d - s->c)/500;

    for (j = s->c; j <= s->d; j+=dy){
        for (i = s->a; i <= s->b; i+=dx){
            val = f(i, j);
            if (val > buf_max){
                buf_max = val;
            }
            if (val < buf_min){
                buf_min = val;
            }
        }
    }

    *min = buf_min;
    *max = buf_max;    
}

void FCalculator::eps(double *f, double z)
{
    if (*f == z){
        *f += 0.001;
    }
}

