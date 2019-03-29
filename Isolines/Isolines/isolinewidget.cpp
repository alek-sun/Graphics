#include "isolinewidget.h"

IsolineWidget::IsolineWidget(QWidget *parent) : QWidget(parent)
{
    settings = new Settings();
    mods = new Mods();
    curPosition = new Position();
    mods->gridShow = false;
    mods->interactive = false;
    mods->interpolation = false;
    image = QImage(500, 500, QImage::Format_ARGB32);
    bufImage = QImage(500, 500, QImage::Format_ARGB32);
    image.fill(QColor(175,95,215,155));
    setMouseTracking(true);
}

void IsolineWidget::setFx(FCalculator *value)
{
    fx = value;
}

void IsolineWidget::drawGrid()
{
    double stepX = image.width()/static_cast<double>(settings->k);
    double stepY = image.height()/static_cast<double>(settings->m);

    QColor black(0,0,0,255);
    double i, j;
    for (i = stepX; i < image.width(); i += stepX){
        for (j = 0; j < image.height(); ++j){
            setPixelColor(i, j, black, image.bits(), image.width());
        }
    }

    for (i = stepY; i < image.height(); i += stepY){
        for (j = 0; j < image.width(); ++j){
            setPixelColor(j, i, black, image.bits(), image.width());
        }
    }
}

void IsolineWidget::drawColoredMap(bool needInterpolate)
{
    if (settings->colorMap.empty()) return;

    int i, j;
    double x, y, k, val, v1, v2, df, n = settings->colorMap.size();
    QColor color, c1, c2;
    int r, g, b;
    double min, max;

    fx->getFLimits(&min, &max);

    int h = image.height(), w = image.width();

    for (i = 0; i < h; ++i){
        for (j = 0; j < w; ++j){
            interpolate(j, i, &x, &y);
            val = fx->f(x,y);
            k = (val - min) / (max - min) * n;

            v1 = trunc(k);
            v2 = ceil(k);
            df = k - v1;

            if (v2 == n){
                 c2 = settings->colorMap[n-1].second;
            } else {
                 c2 = settings->colorMap[v2].second;
            }

            if (v1 == n){
                 c1 = settings->colorMap[n-1].second;
            } else {
                 c1 = settings->colorMap[v1].second;
            }

            if (!needInterpolate){
                color = c1;
            } else {
                r = c1.red()*(1.0 - df) + c2.red()*df;
                g = c1.green()*(1.0 - df) + c2.green()*df;
                b = c1.blue()*(1.0 - df) + c2.blue()*df;
                color = QColor(r, g, b, 255);
            }
            setPixelColor(j, i, color, image.bits(), w);
        }
    }
}

void IsolineWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    fx->buildGrid();

    if (settings->changed){
        settings->fillColorMap();
        drawColoredMap(mods->interpolation);
        bufImage = image;
        settings->changed = false;
    } else {
        image = bufImage;
    }

    if (mods->gridShow){
        drawGrid();
    }
    drawIsolines(settings->userIsolines);

    if (mods->showIsolines){        
        drawIsolines(settings->isolineLevels);
    }

    if (mods->showIntersections){
        drawIntersections();
    }

    points.clear();

    p.drawImage(0,0, image);
    image = QImage(500, 500, QImage::Format_ARGB32);
    image.fill(QColor(175,95,215,155));

}

void IsolineWidget::mousePressEvent(QMouseEvent *event)
{
    double mx = event->x();
    double my = event->y();
    interpolate(mx, my, &mx, &my);
    settings->userIsolines.push_back(fx->f(mx, my));
    mousePressed = true;
    repaint();
}

void IsolineWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    if (mods->interactive && moving){
        settings->userIsolines.pop_back();
        moving = false;
        repaint();
    }
}

void IsolineWidget::mouseMoveEvent(QMouseEvent *event)
{
    double mx = event->x();
    double my = event->y();
    double val = fx->f(curPosition->x, curPosition->y);
    interpolate(mx, my, &mx, &my);

    curPosition->y = my;
    curPosition->x = mx;
    curPosition->f = val;

    mouseMoved(curPosition);

    if (mousePressed && mods->interactive){
        moving = true;
        settings->userIsolines.pop_back();
        settings->userIsolines.push_back(val);
        repaint();
    }
}

void IsolineWidget::setPixelColor(int x, int y, QColor color, uchar *bits, int w)
{
    int i = 4*(x + y*w);
    bits[i] = color.blue();
    bits[i + 1] = color.green();
    bits[i + 2] = color.red();
    bits[i + 3] = color.alpha();
}

void IsolineWidget::interpolate(double vx_pix, double vy_pix, double*x, double*y)
{
    double dy = vy_pix/image.height();
    double dx = vx_pix/image.width();

    *y = dy*(settings->d - settings->c) + settings->c;
    *x = dx*(settings->b - settings->a) + settings->a;
}

void IsolineWidget::drawIsolines(vector<double> isolineLevels)
{
    if (isolineLevels.empty())
        return;

    int i, j, ind, w = settings->k+1;
    double f1, f2, f3, f4, z, middleF, x, y;

    double stepX = image.width()/static_cast<double>(settings->k);
    double stepY = image.height()/static_cast<double>(settings->m);      

    for (j = 0; j < settings->m; ++j){
        for (i = 0; i < settings->k; ++i){
            ind = j*w + i;
            x = stepX*i;
            y = stepY*j;

            f1 = fx->grid[ind];
            f2 = fx->grid[ind+1];
            f3 = fx->grid[ind+w];
            f4 = fx->grid[ind+w+1];

            for (auto level : isolineLevels){
                vector<pair<double, double>> intersections;
                z = level;

                middleF = (f1+f2+f3+f4)/4;

                fx->eps(&f1, z);
                fx->eps(&f2, z);
                fx->eps(&f3, z);
                fx->eps(&f4, z);
                fx->eps(&middleF, z);

                if (!((z > f1 && z > f2) || (z < f1 && z < f2))){
                    intersections.push_back(pair<double, double>
                                            (clampW(x +
                                            intersectionPoint(f1, f2, level, stepX)),
                                            clampH(y)));
                }

                if (!((z > f2 && z > f4) || (z < f2 && z < f4))){
                    intersections.push_back(pair<double, double>
                                            (clampW(x+stepX),
                                             clampH(y +
                                             intersectionPoint(f2, f4, level, stepY))));
                }

                if (!((z > f3 && z > f4) || (z < f3 && z < f4))){
                    intersections.push_back(pair<double, double>
                                            (clampW(x +
                                            intersectionPoint(f3, f4, level, stepX)),
                                            clampH(y+stepY)));
                }

                if (!((z > f1 && z > f3) || (z < f1 && z < f3))){
                    intersections.push_back(pair<double, double>
                                            (clampW(x),
                                             clampH(y +
                                             intersectionPoint(f1, f3, level, stepY))));
                }


                switch (intersections.size()){
                case 2 : {                    
                    drawLine(intersections[0].first, intersections[0].second,
                            intersections[1].first, intersections[1].second,
                            settings->isolineColor);

                    break;
                }
                case 4 : {                   
                    vector<pair<double, double>> intersec2;
                    addIntersection(&intersec2, f1, middleF, 0, 0, stepX, stepY, i, j, z);
                    addIntersection(&intersec2, f2, middleF, 1, 0, stepX, stepY, i, j, z);

                    addIntersection(&intersec2, f2, middleF, 1, 0, stepX, stepY, i, j, z);
                    addIntersection(&intersec2, f4, middleF, 1, 1, stepX, stepY, i, j, z);

                    addIntersection(&intersec2, f3, middleF, 0, 1, stepX, stepY, i, j, z);
                    addIntersection(&intersec2, f4, middleF, 1, 1, stepX, stepY, i, j, z);

                    addIntersection(&intersec2, f1, middleF, 0, 0, stepX, stepY, i, j, z);
                    addIntersection(&intersec2, f3, middleF, 0, 1, stepX, stepY, i, j, z);

                    drawLine(intersec2[0].first, intersec2[0].second,
                            intersections[0].first, intersections[0].second,
                            settings->isolineColor);

                    drawLine(intersec2[1].first, intersec2[1].second,
                            intersections[1].first, intersections[1].second,
                            settings->isolineColor);

                    drawLine(intersec2[2].first, intersec2[2].second,
                            intersections[2].first, intersections[2].second,
                            settings->isolineColor);
                    drawLine(intersec2[3].first, intersec2[3].second,
                            intersections[3].first, intersections[3].second,
                            settings->isolineColor);
                    points.insert(points.end(), intersec2.begin(), intersec2.end());
                }
                }
                points.insert(points.end(), intersections.begin(), intersections.end());
            }
        }
    }
}

void IsolineWidget::drawIntersections()
{
    for (auto point : points){

        setPixelColor(clampW(point.first), clampH(point.second), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first + 1), clampH(point.second), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first - 1), clampH(point.second), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first - 1), clampH(point.second-1), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first + 1), clampH(point.second+1), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first + 1), clampH(point.second-1), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first - 1), clampH(point.second+1), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first), clampH(point.second+1), settings->pointsColor, image.bits(), image.width());
        setPixelColor(clampW(point.first), clampH(point.second-1), settings->pointsColor, image.bits(), image.width());

    }
}


double IsolineWidget::intersectionPoint(double f1, double f2, double z, int d)
{
    return round(d * abs(z-f1) / abs(f2-f1));
}

void IsolineWidget::addIntersection(vector<pair<double, double>>* intersections, double f1, double f2, int sgnx, int sgny, double stepX, double stepY, double i, double j, double lvl)
{
    if (!((lvl > f1 && lvl > f2) || (lvl < f1 && lvl < f2))){
        intersections->push_back(pair<double, double>(clampW(stepX*(i+sgnx) + pow(-1, sgnx)*intersectionPoint(f1, f2, lvl, stepX/2)),
                                                    clampH(stepY*(j+sgny) + pow(-1, sgny)*intersectionPoint(f1, f2, lvl, stepY/2))));
    }
}

QColor IsolineWidget::pixelColor(int x, int y, uchar *bits, int w)
{
    int i =4*(x + y*w);
    return QColor(bits[i + 2], bits[i + 1], bits[i], bits[i + 3]);
}

void IsolineWidget::drawLine(int x0, int y0, int x1, int y1, QColor color)
{
    int dx = abs(x0 - x1);
    int dy = abs(y0 - y1);

    if (dx < dy){
        int dirX = x0 < x1 ? 1 : -1;
        int curY = x0;
        int i, error = 0;
        if (y1 > y0){
            for (i = y0; i <= y1; ++i){
                setPixelColor(curY, i, color, image.bits(), image.width());
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        } else {
            for (i = y0; i >= y1; --i){
                setPixelColor(curY, i, color, image.bits(), image.width());
                error += 2*dx;
                if (error >= dy){
                    curY += dirX;
                    error -= 2*dy;
                }
            }
        }
    } else {
        int dirY = y0 < y1 ? 1 : -1;
        int curY = y0;
        int i, error = 0;
        if (x1 > x0){
            for (i = x0; i <= x1; ++i){
                setPixelColor(i, curY, color, image.bits(), image.width());
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        } else {
            for (i = x0; i >= x1; --i){
                setPixelColor(i, curY, color, image.bits(), image.width());
                error += 2*dy;
                if (error >= dx){
                    curY += dirY;
                    error -= 2*dx;
                }
            }
        }
    }
}

int IsolineWidget::clampH(int v)
{
    if (v >= image.height()) return image.height()-1;
    if (v < 0) return 0;
    return v;
}

int IsolineWidget::clampW(int v)
{
    if (v >= image.width()) return image.width()-1;
    if (v < 0) return 0;
    return v;
}




