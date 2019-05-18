#ifndef EXPANSIONFILTER_H
#define EXPANSIONFILTER_H

#include "imatrixfilter.h"



class ExpansionFilter: public IMatrixFilter
{
public:    
    ExpansionFilter(int index);
    void run(QImage image, QImage *outImage);

private:
    int index;
};

#endif // EXPANSIONFILTER_H
