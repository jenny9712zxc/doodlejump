#ifndef PLOTFORM3_H
#define PLOTFORM3_H

#include "plotform1.h"

class plotform3: public plotform1
{
public:
    plotform3(double, double);

public slots:
    void catch_player(double,double);
    virtual void func();
};

#endif // PLOTFORM3_H
