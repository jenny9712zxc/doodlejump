#include "monster.h"

#include <iostream>
using namespace std;


monster::monster(int x)
{
    item = new QGraphicsPixmapItem(QPixmap(":/res/monster.png").scaled(100,100));
    item->setPos(x, -100);//x: 0 ~ 200
    exist=1;
}

void monster::attacked(double x,double y)
{


    if(x>item ->x()-25  && x<item ->x()+45  &&  y<item ->y()+100)
    {
        exist=0;
        //cout<<"died"<<endl;
        emit died();
        //delete this;

    }

}

void monster::item_down(int h)
{
    if(exist==0)
        return;

    double x=item->x();
    double y=item->y()+h;
    item->setPos(x, y);

    if(y>640)
    {
        exist=0;
        emit died();
        delete this;
     }

}

void monster::collision(double x,double y)
{
    if(exist==0)
        return;

    if(x>item ->x()-40  && x<item ->x()+90  &&  y>item ->y()-80  &&  y<item ->y()+80)
    {
        //cout<<"collision  "<<item ->x()<<"  "<<item ->y()<<endl;
        //cout<<"player"<<x<<"  "<<y<<endl;
        emit collision_signal();

    }

}
