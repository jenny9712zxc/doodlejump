#ifndef PLATFORM2_H
#define PLATFORM2_H

#include "plotform1.h"

class plotform2: public plotform1
{
public:
    plotform2(double, double);


public slots:
    void catch_player(double,double);
    virtual void func();


};

#endif // PLATFORM2_H
