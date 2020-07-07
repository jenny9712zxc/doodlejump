#include "plotform3.h"

plotform3::plotform3(double x, double y):plotform1(x,y,0)
{
    item = new QGraphicsPixmapItem(QPixmap(":/res/plotform3.png").scaled(weight,height));
    item->setPos(x, y);

}

void plotform3::func()
{


    if(clk<100)
        item->setPos(item->x()+2, item->y());
    else
        item->setPos(item->x()-2, item->y());

    if(clk==199)
        clk=0;

    ++clk;

    return;

}
