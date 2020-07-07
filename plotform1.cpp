
#include "plotform1.h"
#include "mainwindow.h"


#include <iostream>
using namespace std;



plotform1::plotform1(double x,double y,int p)
{

    item = new QGraphicsPixmapItem(QPixmap(":/res/plotform1.png").scaled(weight,height-20));
    item->setPos(x, y);
    if(p==1)//spring
    {
        tool= new QGraphicsPixmapItem(QPixmap(":/res/spring.png").scaled(60,30));
        tool->setPos(x+20, y+10);
        tool_f=1;

    }
    else if (p==2)//rocket
    {
        tool= new QGraphicsPixmapItem(QPixmap(":/res/rocket.png").scaled(30,60));
        tool->setPos(x+140, y-10);
        tool_f=2;
    }
    else
    {
        tool_f=0;
    }

}
plotform1::plotform1()
{
    tool_f=0;
}

plotform1::~plotform1()
{}

void plotform1::func()
{}

void plotform1::catch_player(double x, double y)
{

    double h=item->y() - (y+70);
    if(x<item->x()-20 || x>(item->x()+160))
        return;
    if(h>-2 && h<2)
    {
        emit catch_signal();
        flag=1;


        double xx=x - item->x();
        if(tool_f==1 && xx < 60)
            emit spring_signal();
        if(tool_f==2 && xx < 160  && xx > 100)
            emit rocket_signal();
    }
    return;
}

void plotform1::item_down(int h)
{
    double x=item->x();
    double y=item->y()+h;
    item->setPos(x, y);
    if(tool_f==1)
        tool->setPos(x+20, y+10);
    else if(tool_f==2)
        tool->setPos(x+140, y-10);

    if(y>640)
        delete this;

}
