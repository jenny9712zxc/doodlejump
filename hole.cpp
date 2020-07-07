#include "hole.h"

hole::hole()
{
    item = new QGraphicsPixmapItem(QPixmap(":/res/hole.png").scaled(200,200));
    item->setPos(300, -200);
    exist=1;
}
void hole::item_down(int h)
{
    if(exist==0)
        return;

    double x=item->x();
    double y=item->y()+h;
    item->setPos(x, y);

    if(y>640)
    {
        exist=0;
        //delete this;
     }

}

void hole::collision(double x,double y)
{
    if(exist==0)
        return;

    if(x>item ->x()-30   &&  y>item ->y()-70  &&  y<item ->y()+180)
    {
        //cout<<"collision  "<<item ->x()<<"  "<<item ->y()<<endl;
        //cout<<"player"<<x<<"  "<<y<<endl;
        emit collision_signal();

    }

}
