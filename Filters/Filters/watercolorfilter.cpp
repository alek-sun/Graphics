#include "expansionfilter.h"
#include "sharpfilter.h"
#include "watercolorfilter.h"

WatercolorFilter::WatercolorFilter()
{

}

void WatercolorFilter::run(QImage image, QImage *outImage)
{
    ExpansionFilter expFilter(6);
    expFilter.run(image, outImage);
    SharpFilter f;
    f.run(*outImage, outImage);
}
