#include "plotform2.h"

plotform2::plotform2(double x, double y):plotform1(x,y,0)
{
    item = new QGraphicsPixmapItem(QPixmap(":/res/plotform2.png").scaled(weight,height+10));
    item->setPos(x, y);

}

void plotform2::func()
{

    if(flag==0)        return;

    if((clk%2)==0)
        item->setVisible(false);
    else
        item->setVisible(true);

    clk++;

    if(clk==5)
        delete this;
}
